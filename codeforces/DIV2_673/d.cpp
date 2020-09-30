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

#define int ll

void solveCase()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (size_t i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    db(n, a);
    ll sum = accumulate(all(a), 0LL);
    if (sum % n)
    {
        cout << -1 << '\n';
        return;
    }
    sum /= n;
    db(sum);
    set<pair<int, int>> ss;
    for (size_t i = 2; i <= n; i++)
        ss.insert({a[i], i});
    vector<vector<int>> queries;
    auto perform_query = [&](int i, int j, int x) {
        if (x == 0)
            return;
        queries.pb({i, j, x});
        a[i] -= i * x;
        a[j] += i * x;
        db(i, j, x, a[i], a[j]);
        if (a[i] < 0 || a[j] < 0)
        {
            exit(1);
        }
    };
    while (ss.size())
    {
        // db(a[1], ss);
        // db(a);
        auto it = *(--ss.end());
        ss.erase(it);
        int diff = it.f;
        // db(diff, it);
        diff /= it.s;
        while ((diff + 1) * it.s <= it.f)
            diff++;
        perform_query(it.s, 1, diff);
    }
    db(a);
    vector<vector<int>> myVec;
    vector<vector<int>> bag;
    for (int i = 2; i <= n; i++)
        if (a[i] > sum)
        {
            int diff = i - a[i];
            db(i, a[i], sum, diff);
            myVec.pb({diff, -i, diff, i});
        }
        else if (a[i] > 0)
        {
            int diff = i - a[i];
            db(i, a[i], sum, diff);
            bag.pb({diff, -i, diff, i});
        }
    sort(all(myVec));
    sort(all(bag));
    reverse(all(bag));
    db(myVec);
    // reverse(all(myVec));
    for (auto &x : myVec)
    {
        db(x);
        db(a);
        int diff = x[2];
        int i = x[3];
        while (diff > a[1] && bag.size())
        {
            int diff = bag.back()[2];
            int i = bag.back()[3];
            bag.pop_back();
            perform_query(1, i, diff);
            perform_query(i, 1, 1);
        }
        // if (diff > a[1])
        // {
        //     cout << -1 << '\n';
        //     return;
        // }
        perform_query(1, i, diff);
        perform_query(i, 1, 1);
        db(a);
    }
    for (int i = 2; i <= n; i++)
    {
        if (a[i] < sum)
        {
            int diff = sum - a[i];
            perform_query(1, i, diff);
        }
    }
    if (queries.size() > 3 * n)
    {
        db("sizeoverflow")
        // exit(1);
    }
    cout << queries.size() << '\n';
    db(a);
    for (auto &x : queries)
    {
        for (auto &y : x)
        {
            cout << y << ' ';
        }
        cout << '\n';
    }
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
