// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 1e6 + 5, MOD = 1000000007;
const int LOG = __lg(NAX);

int next_node[LOG][NAX];

// int Len[NAX];

void solveCase()
{
    int n, r, c;
    cin >> n >> r >> c;
    vector<string> vecc(n + 1);
    for (size_t i = 1; i <= n; i++)
        cin >> vecc[i];
    // vector<int> maxConsec(n + 1, 0);
    vector<int> dp(n + 2, 0);
    int len = 0, rptr = n - 1;
    for (int i = n; i >= 1; i--)
    {
        if (rptr < i)
        {
            rptr = i;
            len = vecc[i].size();
        }
        else
            len += vecc[i].size();
        while ((len + rptr - i) > c && rptr >= i)
        {
            len -= vecc[rptr].size();
            rptr--;
        }
        next_node[0][i] = rptr + 1;
    }
    for (size_t i = 0; i < LOG; i++)
        next_node[i][n + 1] = n + 1;
    for (int i = 1; i < LOG; i++)
        for (size_t j = 1; j <= n; j++)
            next_node[i][j] = next_node[i - 1][next_node[i - 1][j]];
    int maxLen = 0, maxIdx = 0;
    for (size_t i = 1; i <= n; i++)
    {
        int now = i;
        for (size_t j = 0; j < LOG; j++)
            if (r & (1 << j))
                now = next_node[j][now];
        db(i, now);
        if (maxLen < now - i)
        {
            maxLen = now - i;
            maxIdx = i;
        }
    }
    for (size_t i = 0; i < r; i++)
    {
        if (next_node[0][maxIdx] == maxIdx)
            break;
        for (size_t j = maxIdx; j < next_node[0][maxIdx]; j++)
        {
            cout << vecc[j];
            if (j + 1 < next_node[0][maxIdx])
                cout
                    << ' ';
        }
        cout << '\n';
        maxIdx = next_node[0][maxIdx];
    }
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
