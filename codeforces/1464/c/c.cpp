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
const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    int n;
    cin >> n;
    ll t;
    cin >> t;
    string str;
    cin >> str;
    auto get_val = [](char c) -> ll {
        return 1LL << (c - 'a');
    };
    t -= get_val(str[n - 1]);
    t += get_val(str[n - 2]);
    vector<int> cnt(63);
    for (size_t i = 0; i + 2 < n; i++)
    {
        cnt[str[i] - 'a' + 1]++;
        t += get_val(str[i]);
    }
    db(cnt);
    db(t);
    if (t < 0)
    {
        cout << "NO\n";
        return;
    }
    t = abs(t);
    for (int i = 0; i + 1 < 63; i++)
    {
        db(i, t, cnt[i], t & (1LL << i));
        if (t & (1LL << i))
        {
            cnt[i]--;
            t ^= (1LL << i);
        }
        if (cnt[i] < 0)
        {
            cout << "NO\n";
            return;
        }
        cnt[i + 1] += cnt[i] / 2;
    }
    cout << "YES\n";
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