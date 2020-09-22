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
    vector<ll> a(n + 1);
    vector<ll> pea(n + 1), pda(n + 1);
    for (size_t i = 1; i <= n; i++)
        cin >> a[i];
    stack<pair<ll, ll>> st;
    st.push({MOD, 0});
    for (int i = 1; i <= n; i++)
    {
        while (st.top().f <= a[i])
            st.pop();
        pea[i] = i - st.top().s;
        st.push({a[i], i});
    }
    while (st.size())
        st.pop();
    st.push({MOD, n + 1});
    for (int i = n; i >= 1; i--)
    {
        while (st.top().f < a[i])
            st.pop();
        pea[i] *= st.top().s - i;
        st.push({a[i], i});
    }
    while (st.size())
        st.pop();

    // part 2
    st.push({0, 0});
    for (int i = 1; i <= n; i++)
    {
        while (st.top().f >= a[i])
            st.pop();
        pda[i] = i - st.top().s;
        st.push({a[i], i});
    }
    while (st.size())
        st.pop();
    st.push({0, n + 1});
    for (int i = n; i >= 1; i--)
    {
        while (st.top().f > a[i])
            st.pop();
        pda[i] *= st.top().s - i;
        st.push({a[i], i});
    }
    while (st.size())
        st.pop();

    ll res = 0;
    for (int i = 1; i <= n; i++)
    {
        db(i, a[i], pea[i], pda[i]);
        res += a[i] * (pea[i] - pda[i]);
    }
    cout << res << '\n';
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
