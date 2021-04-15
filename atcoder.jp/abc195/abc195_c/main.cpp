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

int64_t solveCase(int64_t N)
{
    // TODO: edit here
    auto N_str = to_string(N);
    ll curr = 1;
    int64_t ret = 0;
    for (size_t i = 0; i < N_str.size(); i++)
    {
        int len = i + 1;
        if (i != 0)
            curr *= 10;
        if (len <= 3)
            continue;
        len--;
        if (i + 1 != N_str.size())
            ret += len / 3 * (curr * 9);
        else
            ret += len / 3 * (N - curr + 1);
    }
    return ret;
}

// generated by oj-template v4.7.2 (https://github.com/online-judge-tools/template-generator)
int main()
{
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    constexpr char endl = '\n';
    int64_t N;
    cin >> N;
    auto ans = solveCase(N);
    cout << ans << endl;
    return 0;
}