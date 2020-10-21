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
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    vector<vector<int>> myPoints(n);
    deque<int> unMatchedOnes;
    deque<int> unMatchedTwos;
    int elev = n - 1;
    vector<vector<int>> two;
    vector<vector<int>> three;
    for (int i = n - 1; i >= 0; i--)
    {
        if (a[i] == 1)
            unMatchedOnes.pb(i);
        else if (a[i] == 2)
        {
            if (unMatchedOnes.size())
            {
                int idx = unMatchedOnes.front();
                unMatchedOnes.pop_front();
                myPoints[i].pb(elev);
                myPoints[idx].pb(elev);
                two.pb({elev, i});
                // two.pb({idx, elev});
                db(i, elev);
                db(idx, elev);
                elev--;
                if (elev < 0)
                {
                    cout << -1 << '\n';
                    return;
                }
            }
            else
            {
                cout << -1 << '\n';
                return;
            }
        }
        else if (a[i] == 3)
        {
            if (three.size())
            {
                auto tt = three.back();
                int row = tt[0];
                int col = tt[1];
                three.pop_back();
                myPoints[i].pb(elev);
                myPoints[col].pb(elev);
                three.pb({elev, i});
                db(i, elev);
                db(col, elev);
                elev--;
                continue;
            }
            if (two.size())
            {
                auto bb = two.back();
                int row = bb[0];
                int col = bb[1];
                two.pop_back();
                myPoints[i].pb(elev);
                myPoints[col].pb(elev);
                three.pb({elev, i});
                db(i, elev);
                db(col, elev);
                elev--;
                continue;
            }
            if (unMatchedOnes.empty())
            {
                cout << -1 << '\n';
                return;
            }
            int idx = unMatchedOnes.front();
            unMatchedOnes.pop_front();

            myPoints[i].pb(elev - 1);
            myPoints[idx].pb(elev - 1);
            myPoints[idx].pb(elev);
            three.pb({elev - 1, i});
            db(i, elev - 1);
            db(idx, elev);
            db(idx, elev - 1);
            elev -= 2;
        }
    }
    while (unMatchedOnes.size())
    {
        auto top = unMatchedOnes.front();
        unMatchedOnes.pop_front();
        myPoints[top].pb(elev);
        db(top, elev);
        elev--;
    }
    vector<int> col(n);
    for (size_t i = 0; i < n; i++)
    {
        for (auto &x : myPoints[i])
        {
            if (x < 0)
            {
                cout << -1 << '\n';
                return;
            }
            col[x]++;
            if (col[x] > 2)
            {
                cout << -1 << '\n';
                return;
            }
        }
        if (myPoints[i].size() > 2)
        {
            cout << -1 << '\n';
            return;
        }
    }
    int cnt = accumulate(all(col), 0LL);
    if (cnt > 2 * n)
    {
        cout << -1 << '\n';
        return;
    }
    cout << cnt << '\n';
    for (size_t i = 0; i < n; i++)
        for (auto &x : myPoints[i])
            cout << x + 1 << ' ' << i + 1 << '\n';
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
