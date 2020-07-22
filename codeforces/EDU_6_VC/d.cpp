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

struct Solution
{
    Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        vector<ll> a(n);
        for (size_t i = 0; i < n; i++)
            cin >> a[i];
        int m;
        cin >> m;
        vector<ll> b(m);
        for (size_t i = 0; i < m; i++)
            cin >> b[i];
        ll suma = accumulate(all(a), 0LL);
        ll sumb = accumulate(all(b), 0LL);
        auto get_closest = [](ll x, vector<ll> &b) {
            pair<ll, ll> ret;
            ret.f = 1e15;
            ret.s = 1e15;
            auto it = lower_bound(all(b), x);
            if (it != b.end())
                ret.f = *it;
            if (it != b.begin())
            {
                --it;
                ret.s = *it;
            }
            db(x, b, ret);
            return ret;
        };
        vector<vector<ll>> res;
        res.pb({abs(suma - sumb)});
        db(a);
        vector<ll> b1;
        for (auto &x : b)
            b1.pb(2 * x);
        sort(all(b1));
        auto try_one = [&]() {
            for (int i = 0; i < n; i++)
            {
                ll x = suma - sumb - 2 * a[i];
                auto temp = get_closest(-x, b1);
                db(x, temp);
                vector<vector<ll>> curr;
                curr.pb({min(abs(x + temp.f), abs(x + temp.s))});
                curr.pb({0LL + i});
                res = min(res, curr);
                db(i, res, curr);
            }
        };
        vector<ll> aux;
        auto try_two = [&]() {
            for (size_t i = 0; i < m; i++)
                for (size_t j = i + 1; j < m; j++)
                    aux.pb(2 * b[i] + 2 * b[j]);
            sort(all(aux));
            for (int i = 0; i < n; i++)
                for (int j = i + 1; j < n; j++)
                {
                    ll x = suma - sumb - 2 * a[i] - 2 * a[j];
                    auto temp = get_closest(-x, aux);
                    vector<vector<ll>> curr;
                    curr.pb({min(abs(x + temp.f), abs(x + temp.s))});
                    curr.pb({0LL + i});
                    curr.pb({0LL + j});
                    res = min(res, curr);
                    db(i, j, res, curr);
                }
        };
        db(suma, sumb);
        db(res);
        try_one();
        try_two();
        // cout << res << '\n';
        cout << res[0][0] << '\n';
        cout << res.size() - 1 << '\n';
        if (res.size() == 2)
        {
            int i = res[1][0];
            ll x = suma - sumb - 2 * a[i];
            auto temp = get_closest(-x, b1);
            db(temp);
            bool ch = abs(x + temp.f) < abs(x + temp.s);
            for (size_t j = 0; j < m; j++)
            {
                if (ch)
                {
                    if (2 * b[j] == temp.f)
                    {
                        cout << i + 1 << ' ' << j + 1 << '\n';
                        return;
                    }
                }
                else
                {
                    if (2 * b[j] == temp.s)
                    {
                        cout << i + 1 << ' ' << j + 1 << '\n';
                        return;
                    }
                }
            }
        }
        else if (res.size() == 3)
        {
            int i = res[1][0], i1 = res[2][0];
            ll x = suma - sumb - 2 * a[i] - 2 * a[i1];
            auto temp = get_closest(-x, aux);
            db(temp);
            bool ch = abs(x + temp.f) < abs(x + temp.s);
            for (size_t j = 0; j < m; j++)
            {
                for (size_t k = j + 1; k < m; k++)
                {
                    if (ch)
                    {
                        if (2 * b[j] + 2 * b[k] == temp.f)
                        {
                            cout << i + 1 << ' ' << j + 1 << '\n';
                            cout << i1 + 1 << ' ' << k + 1 << '\n';
                            return;
                        }
                    }
                    else
                    {
                        if (2 * b[j] + 2 * b[k] == temp.s)
                        {
                            cout << i + 1 << ' ' << j + 1 << '\n';
                            cout << i1 + 1 << ' ' << k + 1 << '\n';
                            return;
                        }
                    }
                }
            }
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
