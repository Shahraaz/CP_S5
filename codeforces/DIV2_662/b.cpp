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

int cnt[NAX];
set<pair<int, int>> Q;
struct Solution
{
    void add(int x)
    {
        auto it = Q.find({cnt[x], x});
        if (cnt[x] > 0)
            Q.erase(it);
        cnt[x]++;
        Q.insert({cnt[x], x});
    }
    void del(int x)
    {
        auto it = Q.find({cnt[x], x});
        Q.erase(it);
        cnt[x]--;
        if (cnt[x] > 0)
            Q.insert({cnt[x], x});
    }

    void report()
    {
        if (Q.size() == 0)
        {
            cout << "NO\n";
            return;
        }
        if (Q.size() == 1)
        {
            auto it = Q.begin();
            if (it->f >= 8)
                cout << "YES\n";
            else
                cout << "NO\n";
            return;
        }
        auto it = Q.end();
        --it;
        ll a = 0, b = 0;
        a = it->f;
        --it;
        b = it->f;
        db(a, b);
        if (a < 4)
            cout << "NO\n";
        else
        {
            a -= 4;
            db(a, b);
            if (b >= 4 || (a >= 4) || (a >= 2 && b >= 2))
            {
                cout << "YES\n";
            }
            else
            {
                ll c = 0;
                if (it != Q.begin())
                {
                    --it;
                    c = it->f;
                    db(a, b, c);
                    a = b;
                    b = c;
                    if (b >= 4 || (a >= 4) || (a >= 2 && b >= 2))
                    {
                        cout << "YES\n";
                    }
                    else
                        cout << "NO\n";
                }
                else
                    cout << "NO\n";
            }
        }
    }
    Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        for (size_t i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            add(x);
        }
        int m;
        cin >> m;
        while (m--)
        {
            char c;
            int x;
            cin >> c >> x;
            if (c == '-')
                del(x);
            else
                add(x);
            db(Q);
            report();
        }
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
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
