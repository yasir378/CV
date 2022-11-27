// https://practice.geeksforgeeks.org/explore?page=2&category[]=Dynamic%20Programming&sortBy=difficulty
#include <bits/stdc++.h>
using namespace std;
int memo[100][100] = {-1};
// memset(memo, -1, sizeof(memo));
typedef long long LL;
typedef pair<int, int> pii;
typedef vector<int> vi;
// typedef vector<int> &vii;
typedef pair<int, int> pi;
typedef pair<LL, LL> pll;
typedef pair<string, string> pss;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vii;
typedef vector<LL> vl;
typedef vector<vl> vvl;

double EPS = 1e-9;
int INF = 1000000005;
long long INFF = 1000000000000000005LL;
double PI = acos(-1);
int dirx[8] = {-1, 0, 0, 1, -1, -1, 1, 1};
int diry[8] = {0, 1, -1, 0, -1, 1, -1, 1};

#ifdef TESTING
#define DEBUG fprintf(stderr, "====TESTING====\n")
#define VALUE(x) cerr << "The value of " << #x << " is " << x << endl
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define DEBUG
#define VALUE(x)
#define debug(...)
#endif

#define FOR(a, b, c) for (int(a) = (b); (a) < (c); ++(a))
#define FORN(a, b, c) for (int(a) = (b); (a) <= (c); ++(a))
#define FORD(a, b, c) for (int(a) = (b); (a) >= (c); --(a))
#define FORSQ(a, b, c) for (int(a) = (b); (a) * (a) <= (c); ++(a))
#define FORC(a, b, c) for (char(a) = (b); (a) <= (c); ++(a))
#define FOREACH(a, b) for (auto &(a) : (b))
#define REP(i, n) FOR(i, 0, n)
#define REPN(i, n) FORN(i, 1, n)
// #define MAX(a, b) a = max(a, b)
#define MIN(a, b) a = min(a, b)
#define SQR(x) ((LL)(x) * (x))
#define RESET(a, b) memset(a, b, sizeof(a))
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define ALL(v) v.begin(), v.end()
#define ALLA(arr, sz) arr, arr + sz
#define SIZE(v) (int)v.size()
#define SORT(v) sort(ALL(v))
#define REVERSE(v) reverse(ALL(v))
#define SORTA(arr, sz) sort(ALLA(arr, sz))
#define REVERSEA(arr, sz) reverse(ALLA(arr, sz))
#define PERMUTE next_permutation
#define TC(t) while (t--)
int maxCut(int n, int a, int b, int c)
{
    if (n == 0)
        return 0;
    if (n < 0)
        return -1;

    if (n % 2 != 0)
    {
        if (b % 2 == 0)
        {
            if (b % 2 == 0)
            {
                if (c % 2 == 0)
                {
                    return -1;
                }
            }
        }
    }
    int res = max(maxCut(n - a, a, b, c), max(maxCut(n - b, a, b, c), maxCut(n - c, a, b, c)));
    // if (res == -1)
    //     return -1;
    return res + 1;
}
int maxCutDp(int n, int a, int b, int c)
{
    int dp[n + 1];
    dp[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        dp[i] = -1;
        if (i - a >= 0)
            dp[i] = max(dp[i], dp[i - a]);
        if (i - b >= 0)
            dp[i] = max(dp[i], dp[i - b]);
        if (i - c >= 0)
            dp[i] = max(dp[i], dp[i - c]);
        if (dp[i] != -1)
            dp[i]++;
    }
    return dp[n];
}
int nomaxdivide(int n, int m)
{
    while (n % m == 0)
        n = n / m;
    return n;
}

int isUgly(int num)
{
    num = nomaxdivide(num, 2);
    num = nomaxdivide(num, 3);
    num = nomaxdivide(num, 5);

    return (num == 1) ? 1 : 0;
}
int nthuglyNum(int n)
{
    int i = 1;
    int count = 1;
    while (n > count)
    {
        i++;
        if (isUgly(i))
            count++;
    }
    return i;
}
int optimalApp(int n)
{
    int dp[n + 1];
    dp[1] = 1;
    int p1 = 1;
    int p2 = 1;
    int p3 = 1;
    for (int i = 2; i <= n; i++)
    {
        int f1 = 2 * dp[p1];
        int f2 = 3 * dp[p2];
        int f3 = 5 * dp[p3];
        int mini = std::min(f1, std::min(f2, f3));
        dp[i] = mini;
        if (mini == f1)
            p1++;
        if (mini == f2)
            p2++;
        if (mini == f3)
            p3++;
    }
    return dp[n];
}
int minCoins(int arr[], int n, int val)
{
    if (val == 0)
        return 0;
    int res = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] <= val)
        {
            int newVar = minCoins(arr, n, val - arr[i]);
            if (newVar != INT_MAX)
                res = min(res, newVar + 1);
        }
    }
    return res;
}
int numberOfWays(int coins[], int numberOfCoins, int value)
{
    if (numberOfCoins == 0)
        return 0;

    if (value == 0)
        return 1;
    int result = numberOfWays(coins, numberOfCoins - 1, value); // either i will include that shit or i will not include that shit

    if (coins[numberOfCoins - 1] <= value)
        result = result + numberOfWays(coins, numberOfCoins, value - coins[numberOfCoins - 1]);

    return result;
}
int minDpCoins(int arr[], int n, int val)
{
    int dp[val + 1];
    for (int i = 0; i < val + 1; i++)
        dp[i] = INT_MAX;
    dp[0] = 0;
    for (int i = 1; i < val + 1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (arr[j] <= i)
            {
                int res = dp[i - arr[j]];
                if (res != INT_MAX)
                    dp[i] = min(dp[i], res + 1);
            }
        }
    }
    return dp[val];
}
void SieveTheorem(int n)
{
    std::vector<bool> nums(n + 1, true);
    for (int i = 2; i * i <= n; i++)
    {
        if (nums[i])
        {
            for (int j = 2 * i; j <= n; j + i)
            {
                nums[j] = false;
            }
        }
    }
    for (int i = 2; i <= n; i++)
    {
        if (nums[i])
            std::cout << i << " ";
    }
}
int maxProfit(std::vector<int> &nums)
{
    int mini = INT_MAX;
    int profit = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        mini = std::min(mini, nums.at(i));
        int cost = nums.at(i) - mini;
        profit = std::max(profit, cost);
    }
    return profit;
}
void SubsetProblrm(int indx, std::vector<char> &nums, std::string &str, int n)
{
    if (indx == n)
    {
        for (char i : nums)
        {
            std::cout << i;
        }
        if (nums.size() == 0)
            std::cout << "{}";
        std::cout << "\n";
        return;
    }
    nums.push_back(str[indx]); // basically i am includeing the shit
    SubsetProblrm(indx + 1, nums, str, n);
    nums.pop_back(); // this part i am not including shit
    SubsetProblrm(indx + 1, nums, str, n);
}

int KnapSack(int w, int wt[], int val[], int n)
{
    int dp[n + 1][w + 1];
    for (int i = 0; i <= n; i++)
    {
        dp[0][i] = 0;
    }
    for (int i = 1; i <= w; i++)
    {
        dp[i][0] = 0;
    }
    // if (n == 0 || w == 0)
    //     return 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= w; j++)
        {
        }
    }
    if (wt[n - 1] > w)
    {
        return KnapSack(w, wt, val, n - 1);
    } // not including that shit
    else
    {
        return std::max(KnapSack(w, wt, val, n - 1), val[n - 1] + KnapSack(w - wt[n - 1], wt, val, n - 1));
    } // not including that shit
}
void reverse_string(std::string &str)
{
    std::stack<char> myStack;
    for (int i = 0; i < str.size(); i++)
    {
        myStack.push(str[i]);
    }
    while (myStack.empty() == false)
    {
        std::cout << myStack.top() << " ";
        myStack.pop();
    }
}
bool matching(const char &x, const char &y)
{
    return (x == '(' && y == ')') || (x == '{' && y == '}') || (x == '[' && y == ']');
}
bool check_parenthesis(std::string &str)
{
    std::stack<char> myStack;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{')
            myStack.push(str[i]);
        else
        {
            if (myStack.empty() == true)
                return false;
            else if (matching(myStack.top(), str[i]) == false)
                return false;
            else
                myStack.pop();
        }
    }

    return (myStack.empty() == true);
}

int NcatalanNum(int n, int memo[])
{
    if (n < 1)
        return 1;
    int res = 0;
    if (memo[n] != -1)
    {
        return memo[n];
    }
    for (int i = 0; i < n; i++)
    {
        res += NcatalanNum(i, memo) * NcatalanNum(n - i - 1, memo);
        memo[n] = res;
        std::cout << res << "\n";
    }
    return memo[n];
}
int maxiMizeKnap(int W, int val[], int wt[], int n)
{
    // if (memo[n] != -1)
    //     return memo[n];
    int dp[n + 1][W + 1];
    for (int i = 0; i <= W; i++)
    {
        dp[0][i] = 0;
    }
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            if (wt[i - 1] > j)
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = std::max(dp[i - 1][j], val[i - 1] + dp[i - 1][j - wt[i - 1]]);
            // dp[i-1][j] means i am not considering the item
        }
    }
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= W; j++)
            std::cout << dp[i][j] << " ";
        std::cout << "\n";
    }
    return dp[n][W];
    // if (n == 0 || W == 0)
    //     return 0;
    // if (wt[n - 1] > W)
    //     return maxiMizeKnap(W, val, wt, n - 1, memo); // i will not include that shit
    // else
    // {
    //     std::cout << val[n - 1] << " " << wt[n - 1] << "\n";
    //     memo[n] = std::max(maxiMizeKnap(W, val, wt, n - 1, memo), val[n - 1] + maxiMizeKnap(W - wt[n - 1], val, wt, n - 1, memo));
    // }
    // return memo[n];
}
int minJump(int arr[], int n)
{
    if (n == 1)
        return 0;
    int res = INT_MAX;
    for (int i = 0; i <= n - 2; i++)
    {
        if (i + arr[i] >= n - 1)
        {
            int newRes = minJump(arr, i + 1);
            if (newRes != INT_MAX)
                res = std::min(res, newRes + 1);
        }
    }
    return res;
}
int maxjumsp(int arr[], int n)
{
    int dp[n];
    dp[0] = 0;
    for (int i = 1; i < n; i++)
        dp[i] = INT_MAX;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (j + arr[j] >= i)
            {
                if (dp[j] != INT_MAX)
                    dp[i] = std::min(dp[i], dp[j] + 1);
            }
        }
    }

    return dp[n - 1];
}
int SubSum(std::string &str, std::string &str1, int n, int m)
{
    if (memo[n][m] != -1)
        return memo[n][m];
    if (n == 0 || m == 0)
        return memo[n][m] = 0;
    else
    {
        if (str[n - 1] == str1[m - 1])
            memo[n][m] = 1 + SubSum(str, str1, n - 1, m - 1);
        else
            memo[n][m] = std::max(SubSum(str, str1, n - 1, m), SubSum(str, str1, n, m - 1));
    }
    return memo[n][m];
}
int minimuJumps(std::vector<int> &nums, int n)
{
    if (n == 1)
        return 0;
    int res1 = INT_MAX;
    for (int i = 0; i <= n - 2; i++)
    {
        if (i + nums[i] >= n - 1)
        {
            int res = minimuJumps(nums, i + 1);
            if (res != INT_MAX)
                res1 = std::min(res1, res + 1);
        }
    }
    return res1;
}
int coinChanges(std::vector<int> &nums, int n, int sum)
{
    int dp[sum + 1][n + 1];
    for (int i = 0; i <= n; i++)
        dp[0][i] = 1;
    for (int i = 1; i <= sum; i++)
        dp[i][0] = 0;
    for (int i = 0; i <= sum; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            dp[i][j] = dp[i][j - 1];
            if (nums[j - 1] <= i)
                dp[i][j] += dp[i - nums[j - 1]][j];
        }
    }
    return dp[sum][n];
}
// int knapSack(std::vector<int> &nums, std::vector<int> &num1, int num, int W)
// {
//     int dp[num + 1][W + 1];
//     for (int i = 0; i <= num; i++)
//         dp[i][0] = 0;
//     for (int i = 0; i <= W; i++)
//         dp[0][i] = 0;
//     for(int i=1;i<=W ; i++){
//         for(int j=1 ;j<=num;j++)
//            if()
//     }
// }
void hashmapImplement()
{
    unordered_map<std::string, int> mp;
    mp.insert({"Yasir", 123});
    mp["mip"] = 123;
    for (auto x : mp)
    {
        std::cout << x.first << " " << x.second << "\n";
    }
}
void setImplementation()
{
    set<int> st;
    int arr[] = {12, 3, 23, 2, 2, 2, 4, 5};
    for (int i = 0; i < 8; i++)
        st.insert(arr[i]);
    for (auto sx : st)
        std::cout << sx << " ";
}
void removeDup(int arr[], int n)
{
    int temp[n];
    int j = 0;
    for (int i = 0; i < n - 1; i++)
        if (arr[i] != arr[i + 1])
            temp[j++] = arr[i];
    temp[j++] = arr[n - 1];
    for (int i = 0; i < j; i++)
        arr[i] = temp[i];
}
int lcs2(std::vector<int> &nums, int n)
{
    int dp[n];
    dp[0] = 1;
    for (int i = 1; i < n; i++)
    {
        dp[i] = 1;
        for (int j = 0; j < i; j++) // trvarse the elements on the left of the given array
        {
            if (nums[j] < nums[i])
                dp[i] = std::max(dp[i], dp[j] + 1);
        }
    }
    int max1 = 0;
    for (int i = 0; i < n; i++)
        max1 = std::max(max1, dp[i]);
    return max1;
}
// int binLis(std::vector<int> &nums, int n)
// {
//     std::vector<int> num1;
//     num1[0] = nums[0];
//     int count = 1;
//     for (int i = 1; i < n; i++)
//     {
//         if ()
//     }
// }
void optimalStrategy(std::vector<int> &nums, int n)
{
}

int fib(int n, int dp[1000])
{
    if (n == 0 || n == 1)
        return dp[n] = n;
    if (dp[n] != -1)
        return dp[n];
    // std::cout << n << " ";
    else
    {
        dp[n] = fib(n - 1, dp) + fib(n - 2, dp);
        return dp[n];
    }
}
void lis1(std::vector<int> &nums, int n)
{
    int dp[n];
    dp[0] = 1;
    for (int i = 1; i < n; i++)
    {
        dp[i] = 1;
        for (int j = 0; j < i; j++)
            if (nums[i] > nums[j])
                dp[i] = std::max(dp[i], dp[j] + 1);
    }
    for (int i = 0; i < n; i++)
    {
        std::cout << dp[i] << " ";
    }
}
// int memo[1000][1000];
// memset(memo, -1, sizeof(memo));
// int lsc1Dp(std::string str, std::string str1, int n, int m)
// {
//     if (memo[n][m] != -1)
//         return memo[n][m];
//     if (n == 0 || m == 0) // base case
//         memo[n][m] = 0;
//     else
//     {
//         if (str[n - 1] == str1[m - 1])
//             memo[n][m] = 1 + lsc1Dp(str, str1, n - 1, m - 1);
//         else
//             memo[n][m] = max(lsc1Dp(str, str1, n - 1, m), lsc1Dp(str, str1, n, m - 1));
//     }
//     return memo[n][m];
// }
int lsc2(std::string str, std::string str1, int n, int m)
{
    if (n == 0 || m == 0)
        return 0;
    if (str[n - 1] == str1[m - 1])
        return 1 + lsc2(str, str1, n - 1, m - 1);
    else
    {
        return std::max(lsc2(str, str1, n - 1, m), lsc2(str, str1, n, m - 1));
    }
}
int tablsc(std::string str, std::string str1, int n, int m)
{
    int dp[n + 1][m + 1];
    for (int i = 0; i <= n; i++)
        dp[i][0] = 0;
    for (int i = 0; i <= m; i++)
        dp[0][i] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (str[i - 1] == str1[j - 1])
                dp[i][j] = 1 + dp[i][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[n][m];
}
// int minCoins1(std::vector<int> &nums, int n, int sum)
// {
//     int dp[sum + 1][n + 1];
//     for (int i = 0; i <= n; i++)
//         dp[0][i] = 1;
//     for (int i = 1; i <= sum; i++)
//         dp[i][0] = 0;
//     for (int i = 1; <= sum; i++)
//     {
//         for (int j = 1; j <= n; j++)
//             dp[i][j] = dp[i][j - 1];
//     }
//     if (sum == 0)
//         return 1;
//     if (n == 0)
//         return 0;
//     int res = minCoins1(nums, n - 1, sum);
//     if (nums[n - 1] <= sum)
//         res = res + minCoins1(nums, n, sum - nums[n - 1]);
//     return res;
// }
void square(std::vector<int> &nums)
{
    for (auto &i : nums)
        i = i * i;
    std::sort(nums.begin(), nums.end());
    for (auto it : nums)
    {
        std::cout << it << " ";
    }
}
void genericCode() // this code converts the adjmatrix to adj list
{
    int V = 2;
    std::vector<int> adj1[V];
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (adj[i][j] == 1 && i != j)
            {
                adj1[i].push_back(j);
                adj1[j].push_back(i);
            }
        }
    }
}
int main(int argc, char *argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    // std::string str = "ABCDGH";
    // std::string str1 = "AEDFHR";
    std::vector<int> nums{2, 5, 3, 6};
    square(nums);
    // std::cout << minCoins1(nums, nums.size(), 10);
    // std::cout<<str1.size();
    std::cout << tablsc(str, str1, str.size(), str1.size());
    // std::cout << lsc2(str, str1, str.size(), str1.size());
    // int n = 6;
    // int dp[1000];
    // memset(dp, -1, sizeof(dp));
    // std::vector<int> nums{3, 4, 2, 8, 10};
    // lis1(nums, nums.size());
    // std::cout << fib(n, dp);
    // std::vector<int> nums{3, 4, 2, 8, 10};
    // std::cout << lcs2(nums, nums.size());
    // std::string str = "ABCDGH";
    // std::string str1 = "AEDFHR";
    // std::vector<int> nums{4, 1, 5, 3, 1, 3, 2, 1, 8};
    // std::cout << minimuJumps(nums, nums.size());
    // hashmapImplement();
    // int arr[] = {12, 2, 2, 1, 5, 6};
    // removeDup(arr, 7);
    // for (int i = 0; i < 7; i++)
    //     std::cout << arr[i] << " ";
    // int p = 9%1;
    // std::cout << p << " ";
    // std::cout << SubSum(str, str1, str.size(), str1.size());
    // int arr[] = {2, 5, 3, 1, 2, 1};
    // std::cout << maxjumsp(arr, 6);
    // std::cout << "\n";
    // // std::cout << minJump(arr, 6);
    // int n = 8;
    // std::string p = std::to_string(p);
    // std::cout << p << " ";
    // subarraySum(arr, 5, 12);
    // int memo[100];
    // memset(memo, -1, sizeof(memo));
    // int wt[] = {5, 4, 6, 3};
    // int val[] = {10, 40, 30, 50};
    // std::cout << maxiMizeKnap(10, val, wt, 4);

    // std::string str = "((())";
    // std::cout << NcatalanNum(4, memo);
    // std::cout << check_parenthesis(str);
    // unsigned int num = nthuglyNum(150);
    // std::cout << num << " ";
    // unsigned int num2 = optimalApp(11);
    // std::cout << num2 << " ";
    // SieveTheorem(10);
    // int wt[] = {5, 4, 6, 3};
    // int val[] = {10, 40, 30, 50};
    // std::cout << KnapSack(10, wt, val, 4);
    // std::vector<char> nums;
    // std::string str = "abcabcbb";
    // SubsetProblrm(0, nums, str, str.size());
    // std::vector<int> nums{2, 4, 1};
    // std::cout << maxProfit(nums);
    // int arr[] = {2, 3, 5};
    // std::cout << numberOfWays(arr, 3, 7);
    // std::cout << minCoins(arr, 3, 4);
    // std::cout << "\n";
    // std::cout << minDpCoins(arr, 3, 4);
    // int n = 5;
    // int a = 4;
    // int b = 3;
    // int c = 2;
    // std::cout << maxCut(n, a, b, c);
    // std::cout << "\n";
    // DEBUG;
    // std::cout << maxCutDp(n, a, b, c);
}