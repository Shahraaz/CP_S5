#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
using ll = long long;
const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    int n, m;
    cin >> n >> m;
    vector<int> best(1 << 8, MOD);
    best[0] = 0;
    for (size_t i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        vector<int> best_next = best;
        for (int j = 0; j < m; j++)
        {
            int dist = min(j, m - j), now = 0;

            if ('a' <= str[j] && str[j] <= 'z')
                now = 1;
            else if ('0' <= str[j] && str[j] <= '9')
                now = 2;
            else
                now = 4;
            for (size_t k = 0; k < 8; k++)
                best_next[k | now] = min(best_next[k | now], best[k] + dist);
        }
        best = best_next;
    }
    cout << best[7] << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}