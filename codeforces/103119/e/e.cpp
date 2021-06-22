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
const int NAX = 215 + 5, MOD = 1000000007;

using ld = long double;

inline void up(ld &a, ld b) { a < b ? (a = b) : 0; }
int n, W, H, h[NAX], q[NAX], m, ALL, o;
ld f[2][(1 << ((5 * 2) - 1)) + 1][NAX], tmp;

inline ld solve(int A, int B, int K)
{
    if (K <= 0)
        return 0;
    if (K <= A)
        return K;
    if (K >= B)
        return (A + B) * 0.5;
    return (A + B) * 0.5 - (0.5 * (B - K) * (B - K)) / (B - A);
}

ld calc(int x, int S)
{
    int l, r, L, R, cnt, i, j, k, A, B;
    l = max(x - W, 0);
    r = min(x + W, n + 1);
    ld ret = 0;
    for (int i = l; i < r; i++)
    {
        L = max(i - W + 1, max(1, x - m));
        R = min(i + W, x);
        A = h[i], B = h[i + 1];
        if (A > B)
            swap(A, B);
        cnt = 0;
        for (j = L; j <= R; j++)
            if (S >> (x - j) & 1)
                q[++cnt] = h[j];
        sort(q + 1, q + cnt + 1);
        for (j = 1; j <= cnt; j = k + 1)
        {
            k = j;
            while (k < cnt && q[k + 1] - q[k] <= H * 2)
                k++;
            ret += solve(A, B, q[k] + H) - solve(A, B, q[j] - H);
        }
    }
    return ret;
}

void solveCase()
{
    cin >> n >> W >> H;
    for (size_t i = 1; i <= n; i++)
        cin >> h[i];
    m = 2 * W - 1;
    ALL = (1 << m) - 1;
    for (int i = 1; i <= n; i++, o ^= 1)
    {
        for (size_t i = 0; i <= ALL; i++)
            for (size_t j = 0; j <= n; j++)
                f[o ^ 1][i][j] = 0;
        for (size_t S = 0; S <= ALL; S++)
        {
            int T = (S << 1) & ALL;
            tmp = calc(i, S << 1 | 1) - calc(i, S << 1);
            for (int j = 0; j <= n; j++)
            {
                up(f[o ^ 1][T][j], f[o][S][j]);
                up(f[o ^ 1][T + 1][j + 1], f[o][S][j] + tmp);
            }
        }
    }
    for (size_t i = 1; i <= n; i++)
    {
        tmp = 0;
        for (size_t S = 0; S <= ALL; S++)
            up(tmp, f[o][S][i]);
        cout << fixed << setprecision(10) << tmp << '\n';
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
        solveCase();
    return 0;
}