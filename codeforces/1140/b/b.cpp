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
    deque<char> dQ(n);
    for (auto &x : dQ)
        cin >> x;
    int res = n - 1;
    auto calc = [&]() -> int {
        auto now = dQ;
        int meow = 0;
        while (now.size() && now.front() == '<')
        {
            now.pop_front();
            meow++;
        }
        return meow;
    };
    res = min(res, calc());
    reverse(all(dQ));
    for (auto &x : dQ)
        x = x ^ '<' ^ '>';
    res = min(res, calc());
    cout << res << '\n';
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
        solveCase();
    return 0;
}