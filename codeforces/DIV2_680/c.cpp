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
    ll p, q;
    cin >> p >> q;
    vector<ll> tempRes;
    ll p1 = p, q1 = q;
    db(p, q);
    for (ll i = 2; i * i <= q1; i++)
    {
        if (q1 % i == 0)
        {
            int cntp = 0, cntq = 0;
            ll p2 = p;
            while (p1 % i == 0)
            {
                p1 /= i;
                cntp++;
                p2 /= i;
            }
            while (q1 % i == 0)
            {
                q1 /= i;
                cntq++;
            }
            db(i, cntp, cntq);
            db(p1, p2, q1);
            if (cntp < cntq)
            {
                cout << p << '\n';
                return;
            }
            else
            {
                for (size_t j = 1; j < cntq; j++)
                    p2 *= i;
                tempRes.pb(p2);
            }
        }
    }
    if (q1 > 1)
    {
        int i = q1;
        int cntp = 0, cntq = 0;
        ll p2 = p;
        while (p1 % i == 0)
        {
            p1 /= i;
            cntp++;
            p2 /= i;
        }
        while (q1 % i == 0)
        {
            q1 /= i;
            cntq++;
        }
        db(i, cntp, cntq);
        db(p1, p2, q1);
        if (cntp < cntq)
        {
            cout << p << '\n';
            return;
        }
        else
        {
            for (size_t j = 1; j < cntq; j++)
                p2 *= i;
            tempRes.pb(p2);
        }
    }
    cout << *max_element(all(tempRes)) << '\n';
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
