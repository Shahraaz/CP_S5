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
    int n, k;
    cin >> n >> k;
    map<int, int> cnt;
    for (size_t i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        cnt[x]++;
    }
    vector<int> m(k + 1);
    for (size_t i = 0; i < k; i++)
        cin >> m[i + 1];
    m[0] = n;
    vector<vector<int>> res;
    while (cnt.size())
    {
        int done = 0;
        res.pb({});
        while (true)
        {
            int low = 0, high = k, ans = 0;
            while (low <= high)
            {
                int mid = (low + high) / 2;
                auto it = cnt.lower_bound(mid);
                db(low, mid, high);
                if (it != cnt.end() && m[it->f] > done)
                {
                    ans = max(ans, it->f);
                    low = it->f + 1;
                }
                else
                    high = mid - 1;
            }
            db(cnt);
            db(m);
            db(done, ans, "\n");
            if (ans == 0)
                break;
            if (cnt.find(ans) == cnt.end())
                break;
            // assert(vecc[ans].size());
            res.back().pb(ans);
            // vecc[ans].pop_back();
            done++;
            cnt[ans]--;
            if (cnt[ans] == 0)
                cnt.erase(ans);
        }
    }

    cout << res.size() << '\n';
    for (auto &x : res)
    {
        cout << x.size() << ' ';
        for (auto &y : x)
            cout << y << ' ';
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
