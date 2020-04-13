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

int a[10][3];
int b[10][3];

ll dist[30];

class Solution
{
private:
    bool check()
    {
        // db("a");
        int k = 0;
        for (size_t i = 0; i < 8; i++)
            for (size_t j = i + 1; j < 8; j++)
            {
                dist[k] = 0;
                for (size_t z = 0; z < 3; z++)
                    dist[k] += (0LL + b[i][z] - b[j][z]) * (0LL + b[i][z] - b[j][z]);
                k++;
            }
        sort(dist, dist + 28);
        if (dist[0] == 0)
            return false;
        for (size_t i = 0; i < 12; i++)
        {
            if (dist[0] != dist[i])
                return false;
            if (2 * dist[0] != dist[i + 12])
                return false;
        }
        for (size_t i = 0; i < 4; i++)
            if (3 * dist[0] != dist[i + 24])
                return false;
        db("b");
        ll X = 0, Y = 0, Z = 0, S = 0;
        for (size_t i = 0; i < 8; i++)
        {
            X += b[i][0];
            Y += b[i][1];
            Z += b[i][2];
        }
        for (size_t i = 0; i < 8; i++)
        {
            ll x = X - 8 * b[i][0];
            ll y = Y - 8 * b[i][1];
            ll z = Z - 8 * b[i][2];
            ll d = x * x + y * y + z * z;
            if (i == 0)
                S = d;
            else if (d != S)
                return false;
        }
        return true;
    }
    bool dfs(int pos)
    {
        if (pos == 8)
            return check();
        int p[] = {0, 1, 2};
        do
        {
            for (size_t i = 0; i < 3; i++)
                b[pos][i] = a[pos][p[i]];
            if (dfs(pos + 1))
                return true;
        } while (next_permutation(p, p + 3));
        return false;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        for (size_t i = 0; i < 8; i++)
            for (size_t j = 0; j < 3; j++)
                cin >> a[i][j];
        b[0][0] = a[0][0];
        b[0][1] = a[0][1];
        b[0][2] = a[0][2];
        bool ans = dfs(1);
        if (ans)
        {
            cout << "YES\n";
            for (size_t i = 0; i < 8; i++)
            {
                for (size_t j = 0; j < 3; j++)
                    cout << b[i][j] << ' ';
                cout << '\n';
            }
        }
        else
            cout << "NO\n";
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
