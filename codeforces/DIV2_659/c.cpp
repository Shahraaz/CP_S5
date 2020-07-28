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

const int NAX = 20 + 5, MOD = 1000000007;

int isMandatory[NAX][NAX];
int isTaken[NAX][NAX];
struct Solution
{
    Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        string a, b;
        cin >> a >> b;
        vector<vector<int>> rev(21);
        for (size_t i = 0; i < n; i++)
            rev[a[i] - 'a'].pb(i);
        memset(isMandatory, 0, sizeof isMandatory);
        memset(isTaken, 0, sizeof isTaken);
        for (char c = 't'; c >= 'a'; c--)
        {
            vector<char> dest;
            for (auto &x : rev[c - 'a'])
            {
                if (b[x] < c)
                {
                    cout << -1 << '\n';
                    return;
                }
                if (b[x] == c)
                    continue;
                dest.pb(b[x]);
                isMandatory[c - 'a'][b[x] - 'a'] = true;
            }
        }
        int res = 0;
        for (char c = 'a'; c <= 't'; c++)
            for (char next = c + 1; next <= 't'; next++)
                if (isMandatory[c - 'a'][next - 'a'])
                {
                    res++;
                    for (char nnext = next + 1; nnext <= 't'; nnext++)
                        if (isMandatory[c - 'a'][nnext - 'a'])
                            isMandatory[next - 'a'][nnext - 'a'] = 1;
                    break;
                }
        cout << res << '\n';
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}