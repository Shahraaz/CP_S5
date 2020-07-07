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
        int n, k;
        cin >> n >> k;
        vector<vector<int>> mat(n, vector<int>(n,0));
        int p, q;
        p = q = 0;
        for (size_t i = 0; i < k; i++)
        {
            mat[p][q] = 1;
            p++, q++;
            q %= n;
            if (p == n)
            {
                p = 0;
                q++;
                q %= n;
            }
        }
        vector<int> r(n), c(n);
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < n; j++)
            {
                r[i] += (mat[i][j] > 0);
                c[i] += (mat[j][i] > 0);
            }
        int temp = *max_element(all(r)) - *min_element(all(r));
        ll cost = temp * (1LL) * temp;
        temp = *max_element(all(c)) - *min_element(all(c));
        cost += temp * (1LL) * temp;
        cout << cost << '\n';
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                cout << mat[i][j] ;
            }
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