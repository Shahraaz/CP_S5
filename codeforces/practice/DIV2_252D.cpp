// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 3000 + 5, MOD = 1000000007;

int n, m, k, p[NAX];
bool used[NAX];

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> n;
        for (size_t i = 0; i < n; i++)
        {
            cin >> p[i];
            --p[i];
        }
        cin >> m;
        m = n - m;
        auto use_cycle = [&](int v) -> void {
            for (size_t i = v; !used[i]; i = p[i])
                used[i] = true;
        };
        for (size_t i = 0; i < n; i++)
            if (!used[i])
            {
                k++;
                use_cycle(i);
            }
        for (size_t i = 0; i < n; i++)
            used[i] = false;
        cout << abs(k - m) << '\n';
        if (k > m)
        {
            use_cycle(0);
            for (size_t i = 1; i < n && k > m; i++)
            {
                if (!used[i])
                {
                    cout << 1 << ' ' << i + 1 << ' ';
                    k--;
                    use_cycle(i);
                }
            }
        }
        if (k < m)
        {
            for (size_t i = 0; i < n && k < m; i++)
            {
                vector<int> pos(n, -1);
                int cur = 0;
                for (size_t j = p[i]; j != i; j = p[j])
                    pos[j] = cur++;
                pos[i] = cur;
                cur = 0;
                for (size_t j = i + 1; j < n && k < m; j++)
                    if (pos[j] >= cur)
                    {
                        cout << i + 1 << ' ' << j + 1 << '\n';
                        ++k;
                        cur = pos[j] + 1;
                        swap(p[i], p[j]);
                    }
            }
        }
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
