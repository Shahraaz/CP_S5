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

const int NAX = 100 + 5, MOD = 1000000007;

bool fav[NAX];
int n, m, k, x, p;
int lower[NAX], upper[NAX];

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> m >> k;
        for (size_t i = 0; i < k; i++)
        {
            int x;
            cin >> x;
            fav[x] = true;
        }
        int n;
        cin >> n;
        for (size_t i = 0; i < n; i++)
        {
            string namse;
            cin >> namse;
            int p;
            cin >> p;
            int a, b, c;
            a = b = c = 0;
            for (size_t i = 0; i < p; i++)
            {
                int x;
                cin >> x;
                if (x == 0)
                    b++;
                else if (fav[x])
                    ++a;
                else
                    c++;
            }
            lower[i] = a + max(0, b - (m - k - c));
            upper[i] = min(k, a + b);
        }
        for (size_t i = 0; i < n; i++)
        {
            bool die = false;
            bool must = true;
            for (size_t j = 0; j < n; ++j)
                if (i != j)
                {
                    if (upper[i] < lower[j])
                        die = true;
                    if (lower[i] < upper[j])
                        must = false;
                }
            if (die)
                cout << 1 << '\n';
            else if (must)
                cout << 0 << '\n';
            else
                cout << 2 << '\n';
        }
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
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
