#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
using ll = int;
const ll NAX = 22 + 5, MOD = 1000000007;

int n;
ll l[NAX], m[NAX], w[NAX];
string res[NAX];

vector<vector<pair<pair<ll, ll>, pair<ll, string>>>> cache(NAX);

void solve(int fptr, int rptr, ll a_b, ll b_c, ll _a = 0)
{
    if (fptr == rptr)
        return;
    // cache[fptr][{a_b,b_c}]

    // LM
    ll a_b_next = a_b + l[fptr] - m[fptr];
    ll b_c_next = b_c + m[fptr];
    // auto it = cache[fptr + 1].find({a_b_next, b_c_next});
    // if (it == cache[fptr + 1].end() || it->second.first < _a + l[fptr])
    // {
    cache[fptr + 1].pb({{a_b_next, b_c_next}, {_a + l[fptr], "LM"}});
    solve(fptr + 1, rptr, a_b_next, b_c_next, _a + l[fptr]);
    // }

    // LW
    a_b_next = a_b + l[fptr];
    b_c_next = b_c - w[fptr];
    // it = cache[fptr + 1].find({a_b_next, b_c_next});
    // if (it == cache[fptr + 1].end() || it->second.first < _a + l[fptr])
    // {
    //     cache[fptr + 1][{a_b_next, b_c_next}] = {_a + l[fptr], "LW"};
    cache[fptr + 1].pb({{a_b_next, b_c_next}, {_a + l[fptr], "LW"}});
    solve(fptr + 1, rptr, a_b_next, b_c_next, _a + l[fptr]);
    // }

    // MW
    a_b_next = a_b - m[fptr];
    b_c_next = b_c + m[fptr] - w[fptr];
    // if (it == cache[fptr + 1].end() || it->second.first < _a)
    // {
    // cache[fptr + 1][{a_b_next, b_c_next}] = {_a, "MW"};
    cache[fptr + 1].pb({{a_b_next, b_c_next}, {_a, "MW"}});
    solve(fptr + 1, rptr, a_b_next, b_c_next, _a);
    // }
}

pair<ll, string> find(int idx, pair<ll, ll> to_find)
{
    pair<pair<ll, ll>, pair<ll, string>> f;
    f.first = to_find;
    f.second = {2 * MOD, "AB"};
    auto it = lower_bound(all(cache[idx]), f);
    if (it == cache[idx].begin())
        return {0, ""};
    --it;
    if (it->first == to_find)
    {
        // val = it->second.first;
        return it->second;
    }
    return {0, ""};
}

void build_res(int fptr, int rptr, ll a_b, ll b_c)
{
    if (fptr == rptr)
        return;
    auto it = find(rptr, {a_b, b_c});
    // db(fptr, rptr, a_b, b_c, cache[rptr][{a_b, b_c}]);
    assert(it.second.size());
    auto no_res = it.second;
    res[rptr - 1] = no_res;
    if (no_res == "LM")
    { // LM
        ll a_b_next = a_b - l[rptr - 1] + m[rptr - 1];
        ll b_c_next = b_c - m[rptr - 1];
        // cache[fptr + 1][{a_b_next, b_c_next}] = "LM";
        // solve(fptr + 1, rptr, a_b_next, b_c_next);
        build_res(fptr, rptr - 1, a_b_next, b_c_next);
        return;
    }
    if (no_res == "LW")
    { // LW
        ll a_b_next = a_b - l[rptr - 1];
        ll b_c_next = b_c + w[rptr - 1];
        // cache[fptr + 1][{a_b_next, b_c_next}] = "LM";
        // solve(fptr + 1, rptr, a_b_next, b_c_next);
        build_res(fptr, rptr - 1, a_b_next, b_c_next);
        return;
    }
    if (no_res == "MW")
    { // MW
        ll a_b_next = a_b + m[rptr - 1];
        ll b_c_next = b_c - m[rptr - 1] + w[rptr - 1];
        // cache[fptr + 1][{a_b_next, b_c_next}] = "LM";
        // solve(fptr + 1, rptr, a_b_next, b_c_next);
        build_res(fptr, rptr - 1, a_b_next, b_c_next);
        return;
    }
    assert(false);
}

void solveCase()
{
    n = 14;
    cin >> n;
    // db(5, MOD, 5 * MOD);
    for (size_t i = 0; i < n; i++)
        cin >> l[i] >> m[i] >> w[i];
    const int LIM = 12;
    if (n > LIM)
    {
        solve(0, LIM, 0, 0);
        solve(LIM, n, 0, 0);
        for (size_t i = 0; i <= n; i++)
            sort(all(cache[i]));
        // db(n, cache[n]);
        bool ok = false;
        long long nval = LLONG_MIN;
        pair<ll, ll> res;
        for (auto x : cache[LIM])
        {
            auto it = find(n, {-x.first.first, -x.first.second});
            if (it.second == "")
                continue;
            db(nval, x.second.first + it.first, it.first, x);
            if (nval < x.second.first + it.first)
            {
                ok = true;
                nval = it.first + x.second.first;
                res = x.first;
            }
        }
        for (auto x : cache[n])
        {
            auto it = find(LIM, {-x.first.first, -x.first.second});
            if (it.second == "")
                continue;
            db(nval, x.second.first + it.first, it.first, x);
            if (nval < x.second.first + it.first)
            {
                ok = true;
                nval = it.first + x.second.first;
                res.first = -x.first.first;
                res.second = -x.first.second;
            }
        }
        if (!ok)
        {
            cout << "Impossible\n";
            return;
        }
        build_res(0, LIM, res.first, res.second);
        build_res(LIM, n, -res.first, -res.second);
    }
    else
    {
        solve(0, n, 0, 0);
        for (size_t i = 0; i <= n; i++)
            sort(all(cache[i]));
        auto it = find(n, {0, 0});
        if (it.second.empty())
        {
            cout << "Impossible\n";
            return;
        }
        build_res(0, n, 0, 0);
    }
    for (size_t i = 0; i < n; i++)
        cout << res[i] << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    srand(time(NULL));
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}