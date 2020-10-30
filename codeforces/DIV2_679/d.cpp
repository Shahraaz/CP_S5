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

void solveCase()
{
    int n;
    cin >> n;
    set<int> one;
    set<int> two;
    vector<int> sell(n + 1, -1);
    vector<pair<char, int>> vecc;
    for (size_t i = 0; i < 2 * n; i++)
    {
        char ch;
        cin >> ch;
        if (ch == '-')
        {
            int x;
            cin >> x;
            vecc.pb({'-', x});
            sell[x] = i;
            one.insert(i);
        }
        else
        {
            vecc.pb({'+', 0});
            two.insert(i);
        }
    }
    vector<pair<int, int>> res;
    for (size_t i = 1; i <= n; i++)
    {
        if (sell[i] == -1)
        {
            cout << "NO\n";
            return;
        }
        auto it = one.lower_bound(sell[i]);
        auto it2 = two.lower_bound(sell[i]);
        if (it2 != two.begin())
        {
            --it2;
            if (it == one.begin() || *(--it) < *it2)
            {
                res.pb({*it2, i});
            }
            else
            {
                cout << "NO\n";
                return;
            }
            one.erase(sell[i]);
            two.erase(it2);
        }
        else
        {
            cout << "NO\n";
            return;
        }
    }
    sort(all(res));
    cout << "YES\n";
    for (auto &x : res)
        cout << x.s << ' ';
    cout << '\n';
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
