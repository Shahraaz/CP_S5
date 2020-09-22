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

const int NAX = 2e5 + 5, MOD = 1000000007;

int cnt[2][2];
void solveCase()
{
    int n;
    cin >> n;
    memset(cnt, 0, sizeof cnt);
    string str;
    cin >> str;
    for (int i = 0; i < n; i++)
        cnt[i & 1][(str[i] - '0') & 1]++;
    for (int i = 0; i + 1 < n; i++)
    {
        // cout << i << '\n';
        // cout << cnt[0][0] << ' ' << cnt[0][1] << '\n';
        // cout << cnt[1][0] << ' ' << cnt[1][1] << '\n';
        if (i & 1)
        {
            //Breach
            if (cnt[1][1])
                cnt[1][1]--;
            else if (cnt[1][0])
                cnt[1][0]--;
            else
                break;
        }
        else
        {
            //Reza
            if (cnt[0][0])
                cnt[0][0]--;
            else if (cnt[0][1])
                cnt[0][1]--;
            else
                break;
        }
    }
    // cout << cnt[0][0] << ' ' << cnt[0][1] << '\n';
    // cout << cnt[1][0] << ' ' << cnt[1][1] << '\n';
    if (cnt[0][1] || cnt[1][1])
        cout << 1 << '\n';
    else
        cout << 2 << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
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
