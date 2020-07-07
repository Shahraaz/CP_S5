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

const int NAX = 2e5 + 5, MOD = 1000000007;

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> a(n, vector<int>(m));
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < m; j++)
                cin >> a[i][j];
        auto isValid = [&](int x, int y) -> bool {
            return 0 <= x && x < n && 0 <= y && y < m;
        };
        int l[] = {0, 0, 1, -1};
        int r[] = {1, -1, 0, 0};
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int cnt = 0;
                for (size_t k = 0; k < 4; k++)
                {
                    int x = i + l[k];
                    int y = j + r[k];
                    cnt += isValid(x, y);
                }
                if (a[i][j] > cnt)
                {
                    cout << "NO\n";
                    return;
                }
                a[i][j] = cnt;
            }
        }
        cout << "YES\n";
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < m; j++)
                cout << a[i][j] << ' ';
            cout << '\n';
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
    cin >> t;
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
