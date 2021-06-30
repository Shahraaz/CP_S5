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
    int n, k;
    ll A, B;
    cin >> n >> k >> A >> B;
    vector<int> a(k);
    for (auto &x : a)
        cin >> x;
    sort(all(a));
    db(a, A, B);
    function<ll(int, int, int, int)> solve = [&](int start, int len, int astart, int aend) -> ll
    {
        int len_array = len, len_people = aend - astart;
        if (len_array == 1)
            return len_people ? B * len_people * len_array : A;
        if (len_people == 0)
            return A;
        int mid = start + len / 2;
        int mptr = lower_bound(all(a), mid) - a.begin();
        // while (mptr < aend && a[mptr] < mid)
        //     ++mptr;
        ll now = min(B * len_people * len_array, solve(start, len / 2, astart, mptr) + solve(mid, len / 2, mptr, aend));
        db(start, len, astart, aend, mid, mptr, now, B * len_people * len_array);
        return now;
    };
    cout << solve(1, 1 << n, 0, a.size()) << '\n';
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