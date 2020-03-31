#include <iostream>
#include <cstdio>
#include <cmath>
#include <iomanip>
#define ld double

using namespace std;
const ld step = 0.05;
struct pt
{
    ld x, y;
};

ld dist(pt a, pt b)
{
    return hypot(a.x - b.x, a.y - b.y);
}

ld a, r1, r2, r3;

void solve()
{
    cin >> a >> r1 >> r2 >> r3;

    pt M1 = {0, 0};
    pt M2 = {a * 0.5, a * sqrt(3) * 0.5};
    pt M3 = {-a * 0.5, a * sqrt(3) * 0.5};

    ld res = 0;
    for (ld x = -a; x < 0; x += step)
        for (ld y = 0; y < (x + a) * sqrt(3) and dist({x, y}, M1) < r1; y += step)
        {
            if (dist({x, y}, M2) <= r2 and dist({x, y}, M3) <= r3)
            {
                res += step * step;
            }
        }

    for (ld x = 0; x < a; x += step)
        for (ld y = 0; y < (-x + a) * sqrt(3) and dist({x, y}, M1) < r1; y += step)
        {
            if (dist({x, y}, M2) <= r2 and dist({x, y}, M3) <= r3)
                res += step * step;
        }

    cout << setprecision(4) << fixed << res << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    int t;
    cin >> t;
    for (int i = 1; i <= t; i++)
        solve();

    return 0;
}
