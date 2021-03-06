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

ll dp_mask[1 << 16][17][17];

int64_t solveCase(int64_t H, int64_t W, int64_t A, int64_t B)
{
    // TODO: edit here
    memset(dp_mask, -1, sizeof dp_mask);
    function<ll(int, int, int)> solve = [&](int mask, int a, int b) -> ll {
        if (a < 0 || b < 0)
            return 0;
        int cnt = __builtin_popcount(mask);
        if (cnt == H * W)
        {
            auto ret = a == 0 && b == 0;
            db("basecase", bitset<16>(mask), a, b, ret, cnt);
            return ret;
        }
        auto &ret = dp_mask[mask][a][b];
        if (ret >= 0)
            return ret;
        ret = 0;
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                int curr = i * W + j;
                if ((mask >> curr) & 1)
                {
                }
                else
                {
                    ret += solve(mask | (1 << curr), a - 1, b);
                    if (i + 1 < H)
                    {
                        int curr2 = (i + 1) * W + j;
                        if (mask & (1 << curr2))
                            ;
                        else
                            ret += solve(mask | (1 << curr) | (1 << curr2), a, b - 1);
                    }
                    if (j + 1 < W)
                    {
                        int curr2 = i * W + j + 1;
                        if (mask & (1 << curr2))
                            ;
                        else
                            ret += solve(mask | (1 << curr) | (1 << curr2), a, b - 1);
                    }
                    db("midloop", bitset<16>(mask), a, b, ret, cnt);
                    return ret;
                }
            }
        }
        db("endloop", bitset<16>(mask), a, b, ret, cnt);
        return ret;
    };
    return solve(0, B, A);
}

// generated by oj-template v4.7.2 (https://github.com/online-judge-tools/template-generator)
int main()
{
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    constexpr char endl = '\n';
    int64_t H, W, A, B;
    cin >> H >> W >> A >> B;
    auto ans = solveCase(H, W, A, B);
    cout << ans << endl;
    return 0;
}