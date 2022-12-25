#include "milf.h"
struct client_info
{
    socklen_t address_length;
    struct sockaddr_storage address;
    SOCKET socket;
    char request[MAX_REQUEST_SIZE + 1];
    int received;
    struct client_info *next;
};
static struct client_info *clients = 0;
// this part handle the multiple clients seprately
struct client_info *get_client(SOCKET s)
{
    struct client_info *ci = clients;
    while (ci)
    {
        if (ci->socket == s)
            break;
        ci = ci->next;
    }
    if (ci)
        return ci;

    struct client_info *n = (struct client_info *)calloc(1, sizeof(struct client_info));
    if (!n)
    {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    n->address_length = sizeof(n->address);
    n->next = clients;
    clients = n;
    return n;
}
// Drop  the clients if it is not connected and delayed
void drop_client(struct client_info *client)
{
    closesocket(client->socket);
    struct client_info **p = &clients;
    while (*p)
    {
        if (*p == client)
        {
            *p = client->next;
            free(client);
            return;
        }
        p = &(*p)->next;
    }
    fprintf(stderr, "drop_client not found\n");
    exit(1);
}
const char *get_client_address(struct client_info *cl)
{
    static char address_buffer[100];
    getnameinfo((struct sockaddr *)&cl->address,
                cl->address_length, address_buffer,
                sizeof(address_buffer), 0, 0, NI_NUMERICHOST);
    return address_buffer;
}
fd_set wait_on_clients(SOCKET server)
{
    fd_set reads;
    FD_ZERO(&reads);
    FD_SET(server, &reads); // The FD_SET macro is used to add a file descriptor to an fd_set set,
    // and the FD_ISSET macro is used to test whether a file descriptor is a member of an fd_set set.
    SOCKET max_socket = server;
    struct client_info *ci = clients;
    while (ci)
    {
        FD_SET(ci->socket, &reads);
        if (ci->socket > max_socket)
            max_socket = ci->socket;
        ci = ci->next;
    }
    if (select(max_socket + 1, &reads, 0, 0, 0) < 0)
    {
        fprintf(stderr, "select() failed.(%d)\n ", GETSOCKETERRORNO());
        exit(1);
    }
    return reads;
}
void send_400(struct client_info *client)
{
    const char *c400 = "HTTP /1.1 400 Bad Request\r\n Connection : close\r\nContent-Length : 11\r\n\r\nBad Request ";
    send(client->socket, c400, strlen(c400), 0);
    drop_client(client);
}
void send_404(struct client_info *client)
{
    const char *c404 = "HTTP /1.1 400 Not Found\r\n Connection : close\r\nContent-Length : 11\r\n\r\nNot Found ";
    send(client->socket, c404, strlen(c404), 0);
    drop_client(client);
}
void serve_resource(struct client_info *client, const char *path)
{
    printf("serve_resource %s %s\n", get_client_address(client), path);
    if (strcmp(path, "/") == 0)
        path = "/index.html";
    if (strlen(path) > 100)
    {
        send_400(client);
        return;
    }
    if (strstr(path, ".."))
    {
        send_404(client);
        return;
    }
    char full_path[128];
    sprintf(full_path, "public%s", path);
#if defined(_WIN32)
    char *p = full_path;
    while (*p)
    {
        if (*p == '/')
            *p == '\\';
        ++p;
    }
#endif
    FILE *fp = fopen(full_path, "rb");
    if (!fp)
    {
        send_404(client);
        return;
    }
    fseek(fp, 0L, SEEK_END);
    size_t cl = ftell(fp);
    rewind(fp);
    char buffer[BSIZE];
    sprintf(buffer, "HTTP/1.1 200 OK\r\n");
    send(client->socket, buffer, strlen(buffer), 0);

    sprintf(buffer, "Connection : Close\r\n");
    send(client->socket, buffer, strlen(buffer), 0);

    sprintf(buffer, "Content-Type: %s\r\n", cl);
    send(client->socket, buffer, strlen(buffer), 0);

    sprintf(buffer, "\r\n");
    send(client->socket, buffer, strlen(buffer), 0);
    int r = fread(buffer, 1, BSIZE, fp);
    while (r)
    {
        send(client->socket, buffer, r, 0);
        r = fread(buffer, 1, BSIZE, fp);
    }
    fclose(fp);
    drop_client(client);
}
const char *get_content_type(const char *path)
{
    const char *last_dot = strrchr(path, '.');
    if (last_dot)
    {
        if (strcmp(last_dot, ".css") == 0)
            return "text/css";
        if (strcmp(last_dot, ".csv") == 0)
            return "text/csv";
        if (strcmp(last_dot, ".gif") == 0)
            return "image/gif";
        if (strcmp(last_dot, ".htm") == 0)
            return "text/htm";
        if (strcmp(last_dot, ".html") == 0)
            return "text/html";
        if (strcmp(last_dot, ".ico") == 0)
            return "image/x-icon";
        if (strcmp(last_dot, ".jpeg") == 0)
            return "image/jpeg";
        if (strcmp(last_dot, ".jpg") == 0)
            return "image/jpg";
        if (strcmp(last_dot, ".js") == 0)
            return "application/javascript";
        if (strcmp(last_dot, ".json") == 0)
            return "application/json";
        if (strcmp(last_dot, ".png") == 0)
            return "image/png";
        if (strcmp(last_dot, ".pdf") == 0)
            return "application/pdf";
        if (strcmp(last_dot, ".svg") == 0)
            return "image.svg+xml";
        if (strcmp(last_dot, ".txt") == 0)
            return "text/plain";
    }
    return "application/octet-stream";
}
// this part creates the socket
SOCKET create_socket(const char *host, const char *port)
{
    printf("Configuring local Address....\n");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    struct addrinfo *bind_address;
    getaddrinfo(host, port, &hints, &bind_address);
    printf("Creating Socket .......\n");
    SOCKET socket_listen;
    socket_listen = socket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);
    if (!ISVALIDSOCKET(socket_listen))
    {
        fprintf(stderr, "socket() failed .(%d)\n", GETSOCKETERRORNO());
        exit(1);
    }
    printf("Binding the socket to the local address......\n");
    if (bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen))
    {
        fprintf(stderr, "bind() failed . (%d)\n", GETSOCKETERRORNO());
        exit(1);
    }
    printf("Listenning.......\n");
    if (listen(socket_listen, 10) < 0)
    {
        fprintf(stderr, "listen() . (%d)\n", GETSOCKETERRORNO());
        exit(1);
    }
    return socket_listen;
}
int main()
{
#if defined(_WIN32)
    WSADATA ds;
    if (WSAStartup(MAKEWORD(2, 2), &ds))
    {
        fprintf(stderr, "Failed to initialzed......\n");
        return 1;
    }
#endif
    SOCKET sever = create_socket("127.0.0.1", "8080");
}
