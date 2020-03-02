#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ld long double
#define fi first
#define se second
#define pb push_back
#define pii pair<int, int>
#define all(x) (x).begin(), (x).end()
const int MOD = 1e9 + 7;
int mpow(int a, int b, int p = MOD)
{
    a = a % p;
    int res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = (res * a) % p;
        a = (a * a) % p;
        b = b >> 1;
    }
    return res % p;
}
const int N = 1e2 + 2;

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
// freopen("output.txt","w",stdout);
#endif
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        map<int, int> dp;
        function<bool(int, int)> solve = [&solve, &dp](int n, int m) -> bool {
            // cout << n << ' ' << m << '\n';
            if (dp.find(n) != dp.end())
                return dp[n];
            if (n <= m)
                return true;
            for (int j = 1; j <= m; j++)
                if (solve(n - j, m) == 0)
                    return dp[n] = true;
            return dp[n] = false;
        };
        if (solve(n, m))
            // cout << "A\n";
            ;
        else
        {
            // cout << "B\n";
            cout << n << ' ' << m << '\n';
        }
    }
}
