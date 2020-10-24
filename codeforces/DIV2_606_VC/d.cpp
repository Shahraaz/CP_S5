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
    vector<string> vecc;
    vector<int> zerozero, oneone;
    set<int> zeroone, onezero;
    map<string, vector<int>> cnt;
    bool ok = false;
    for (size_t i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        vecc.pb(str);
        if (str.front() == '0' && str.back() == '0')
            zerozero.pb(i);
        else if (str.front() == '0' && str.back() == '1')
        {
            zeroone.insert(i);
            if (cnt[str].size() > 1)
            {
                cout << -1 << '\n';
                return;
            }
            else if (cnt[str].size() == 1)
            {
                for (auto &x : cnt[str])
                    if (onezero.count(x))
                        onezero.erase(x);
                    else
                        assert(false);
                zeroone.erase(i);
                cnt[str].pb(i);
                ok = true;
            }
            else
                cnt[str].pb(i);
        }
        else if (str.front() == '1' && str.back() == '1')
            oneone.pb(i);
        else
        {
            onezero.insert(i);
            reverse(all(str));
            if (cnt[str].size() > 1)
            {
                cout << -1 << '\n';
                return;
            }
            else if (cnt[str].size() == 1)
            {
                for (auto &x : cnt[str])
                    if (zeroone.count(x))
                        zeroone.erase(x);
                    else
                        assert(false);
                onezero.erase(i);
                cnt[str].pb(i);
                ok = true;
            }
            else
                cnt[str].pb(i);
        }
    }
    db(onezero);
    db(oneone);
    db(zerozero);
    db(zeroone);
    db(vecc);
    if (oneone.size() && zerozero.size() && (zeroone.size() + onezero.size()) == 0 && !ok)
    {
        cout << "-1" << '\n';
        return;
    }
    set<int> res;
    while (abs((int)zeroone.size() - (int)onezero.size()) > 1)
    {
        if (zeroone.size() > onezero.size())
        {
            if (res.count(*zeroone.begin()))
            {
                cout << -1 << '\n';
                return;
            }
            res.insert(*zeroone.begin());
            onezero.insert(*zeroone.begin());
            zeroone.erase(*zeroone.begin());
        }
        else
        {
            if (res.count(*onezero.begin()))
            {
                cout << -1 << '\n';
                return;
            }
            res.insert(*onezero.begin());
            zeroone.insert(*onezero.begin());
            onezero.erase(*onezero.begin());
        }
    }
    cout << res.size() << '\n';
    for (auto &x : res)
    {
        cout << x + 1 << ' ';
    }
    cout << '\n';
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
