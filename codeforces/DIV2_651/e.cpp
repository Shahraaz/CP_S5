#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
using ll = long long;
const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    vector<set<int>> poses(2);
    for (size_t i = 0; i < n; i++)
        if (s[i] != t[i])
            poses[s[i] - '0'].insert(i);
    int ans = 0;
    int zero = 0, one = 1;
    if (poses[0].size() != poses[1].size())
        ans = -1;
    else
        while (poses[zero].size() && poses[one].size())
        {
            if (*poses[0].begin() > *poses[1].begin())
            {
                zero = 1, one = 0;
                int l = -1;
                while (true)
                {
                    auto it = upper_bound(all(poses[zero]), l);
                    if (it == poses[zero].end())
                        break;
                    l = *it;
                    auto it2 = upper_bound(all(poses[one]), *it);
                    if (it2 == poses[one].end())
                        break;
                    l = *it2;
                    poses[zero].erase(it);
                    poses[one].erase(it2);
                }
            }
            else
            {
                zero = 0, one = 1;
                int l = -1;
                while (true)
                {
                    auto it = upper_bound(all(poses[zero]), l);
                    if (it == poses[zero].end())
                        break;
                    l = *it;
                    auto it2 = upper_bound(all(poses[one]), *it);
                    if (it2 == poses[one].end())
                        break;
                    l = *it2;
                    poses[zero].erase(it);
                    poses[one].erase(it2);
                }
            }
            ans++;
        }
    cout << ans << '\n';
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
#ifdef TIMER
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}