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
    ll ret = 0;
    for (size_t i = 1; i <= N; i++)
    {
        auto i_str = to_string(i);
        i_str += i_str;
        auto curr = stoll(i_str);
        if (curr <= N)
            ret++;
        else
            break;
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