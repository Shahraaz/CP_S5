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

int64_t solveCase(int64_t R, int64_t X, int64_t Y)
{
    // TODO: edit here
    auto d = X * X + Y * Y;
    if (d < (R * R))
        return 2;
    return ceil(sqrtl((long double)d / (R * R)));
}

// generated by oj-template v4.7.2 (https://github.com/online-judge-tools/template-generator)
int main()
{
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    constexpr char endl = '\n';
    int64_t R, X, Y;
    cin >> R >> X >> Y;
    auto ans = solveCase(R, X, Y);
    cout << ans << endl;
    return 0;
}