#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
using ll = long long;
const int NAX = 2e5 + 5, MOD = 1000000007, LIM = 20;

int n, m;
int cnt[NAX], dp[LIM][NAX];

void solveCase()
{
    cin >> n >> m;
    for (size_t i = 0; i < n; i++)
    {
        int c;
        cin >> c;
        --c;
        cnt[c]++;
    }

    // for (size_t i = 0; i < m; i++)
    //     cout << '[' << i << ' ' << cnt[i] << "] ";
    // cout << '\n';

    for (size_t i = 1; i < m; i++)
    {
        cnt[i] += cnt[i - 1];
    }

    // for (size_t i = 0; i < m; i++)
    //     cout << cnt[i] << ' ';
    // cout << '\n';

    auto getsum = [&](int l, int r) -> int {
        if (l > r)
            return 0;
        return cnt[r] - cnt[l - 1];
    };
    auto cnt = [&](int l, int r, int x) -> int {
        int ans = dp[x][l];
        int mid = r - (r - l + 1) % (1 << (x + 1)) + 1;
        int sep = mid + (1 << x);
        ans -= dp[x][mid];
        if (sep <= r)
            ans += getsum(sep, r);
        db(l, r, x, mid, sep, ans);
        return ans;
    };
    for (size_t x = 0; x < LIM; x++)
    {
        for (int pos = m - 1; pos >= 0; pos--)
        {
            int len = (1 << x);
            int f = pos + len;
            int s = pos + 2 * len - 1;
            if (f < m)
                dp[x][pos] = getsum(f, min(s, m - 1));
            if (s + 1 < m)
                dp[x][pos] += dp[x][s + 1];
            // db(x, pos, dp[x][pos]);
        }
    }
    int q;
    cin >> q;
    for (size_t i = 0; i < q; i++)
    {
        int l, r;
        cin >> l >> r;
        --l, --r;
        bool has_1_bit = false;
        for (size_t x = 0; x < LIM; x++)
            if (cnt(l, r, x) & 1)
            {
                has_1_bit = 1;
                break;
            }
        if (has_1_bit)
            cout << "A";
        else
            cout << "B";
#ifdef LOCAL
        cout << '\n';
#endif
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
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}