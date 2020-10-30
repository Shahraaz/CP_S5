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
    vector<int> a(6);
    for (auto &x : a)
        cin >> x;
    int n;
    cin >> n;
    vector<int> b(n);
    for (auto &x : b)
        cin >> x;
    vector<pair<int, int>> temp;
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < 6; j++)
            temp.pb({b[i] - a[j], i});
    sort(all(temp));
    ll low = 0, high = temp.back().f;
    ll ans = high;
    auto check = [&](ll sz) -> bool {
        vector<int> cnt(n);
        int res = 0;
        int l = 0, r = -1;
        db(sz);
        db(temp);
        while (l < temp.size())
        {
            if (r < l)
            {
                if (cnt[temp[l].s] == 0)
                    ++res;
                cnt[temp[l].s]++;
                r = l;
            }
            db(l, r);
            while (r + 1 < temp.size() && temp[r + 1].f - temp[l].f <= sz)
            {
                if (cnt[temp[r + 1].s] == 0)
                    res++;
                cnt[temp[r + 1].s]++;
                ++r;
            }
            db(l, r, res);
            db(cnt);
            if (res == n)
                return true;
            cnt[temp[l].s]--;
            if (cnt[temp[l].s] == 0)
                --res;
            ++l;
        }
        return false;
    };
    while (low <= high)
    {
        auto mid = low + high;
        mid /= 2;
        if (check(mid))
        {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else
            low = mid + 1;
    }
    cout << ans << '\n';
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
