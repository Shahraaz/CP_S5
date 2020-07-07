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
    void no()
    {
        cout << "NO\n";
        exit(0);
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, a, b;
        cin >> n >> a >> b;
        bool ok = false;
        if (a > b)
        {
            swap(a, b);
            ok = true;
        }
        if (a != 1)
            no();
        if (b == 1)
        {
            if (n == 1)
            {
                cout << "YES\n";
                cout << "0\n";
                return;
            }
            else if (n == 2 || n == 3)
                no();
            else
            {
                cout << "YES\n";
                vector<string> mat(n);
                for (size_t i = 0; i < n; i++)
                {
                    mat[i] = string(n, '0');
                    if (i + 1 < n)
                        mat[i][i + 1] = '1';
                }
                for (size_t i = 0; i < n; i++)
                    for (size_t j = 0; j < i; j++)
                        mat[i][j] = mat[j][i];
                for (size_t i = 0; i < n; i++)
                    cout << mat[i] << '\n';
                // db(mat);
                return;
            }
        }
        cout << "YES\n";
        vector<string> mat(n);
        for (size_t i = 0; i < n; i++)
        {
            mat[i] = string(n, '0');
            if (b == 1)
            {
                for (size_t j = i + 1; j < n; j++)
                    mat[i][j] = '1';
            }
            else
                b--;
            // db(i, mat[i]);
        }
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < i; j++)
                mat[i][j] = mat[j][i];
        if (!ok)
            for (size_t i = 0; i < n; i++)
            {
                for (size_t j = 0; j < n; j++)
                {
                    if (i == j)
                        continue;
                    mat[i][j] = '1' - mat[i][j] + '0';
                }
                db(i, mat[i]);
            }
        for (size_t i = 0; i < n; i++)
            cout << mat[i] << '\n';
        // db(mat);
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
