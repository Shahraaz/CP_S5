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
std::random_device rd;
std::mt19937 g(rd());

#include <bits/stdc++.h>
using namespace std;

template <typename inpType, int (*func)(int, int)>
struct sparseTree
{
    int n, logLim, def;
    vector<vector<int>> lookup;

    void buildSparseTable(inpType &arr, int n, int def)
    {
        this->n = n;
        this->def = def;
        logLim = __lg(n) + 1;
        lookup.resize(n, vector<int>(logLim, def));
        for (int i = 0; i < n; i++)
            lookup[i][0] = arr[i];
        for (int j = 1; (1 << j) <= n; j++)
            for (int i = 0; (i + (1 << j) - 1) < n; i++)
                lookup[i][j] = func(lookup[i][j - 1], lookup[i + (1 << (j - 1))][j - 1]);
    }

    int query(int L, int R)
    {
        if (L < 0 || L > n - 1 || R < 0 || R > n - 1 || L > R)
            return def;
        int j = __lg(R - L + 1);
        return func(lookup[L][j], lookup[R - (1 << j) + 1][j]);
    }
};

int min(int a, int b)
{
    return std::min(a, b);
}
int max(int a, int b)
{
    return std::max(a, b);
}

void solveCase()
{
    int n;
    cin >> n;
    vector<int> perm(n);
    for (size_t i = 0; i < n; i++)
    {
        perm[i] = i + 1;
        cin >> perm[i];
    }
    // std::shuffle(perm.begin(), perm.end(), g);
    db(perm);
    vector<int> QL(n), DL(n);
    vector<int> QR(n), DR(n);
    for (int i = 0; i < n; i++)
    {
        QL[i] = DL[i] = 1;
        if (i > 0 && perm[i - 1] < perm[i])
            QL[i] += QL[i - 1];
    }
    for (int i = n - 1; i >= 0; i--)
    {
        QR[i] = DR[i] = 1;
        if (i + 1 < n && perm[i] > perm[i + 1])
        {
            QR[i] += QR[i + 1];
        }
    }
    int maxi = -1, cnt = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (QL[i] > maxi)
            maxi = QL[i], cnt = 1;
        else if (QL[i] == maxi)
            cnt++;
        if (QR[i] > maxi)
            maxi = QR[i], cnt = 1;
        else if (QR[i] == maxi)
            cnt++;
    }
    int chances = 0;
    for (size_t i = 1; i + 1 < n; i++)
    {
        if (perm[i - 1] < perm[i] && perm[i] > perm[i + 1])
        {
            if (QL[i] == maxi)
                chances++;
            if (QR[i] == maxi)
                chances++;
        }
    }
    db(cnt, chances);
    if (cnt > chances)
    {
        cout << "0\n";
        return;
    }
    // cnt == chances
    if (chances > 2)
    {
        cout << "0\n";
        return;
    }
    if (chances == 1)
    {
        cout << "0\n";
        return;
    }
    assert(chances == 2);
    for (size_t i = 1; i + 1 < n; i++)
    {
        if (perm[i - 1] < perm[i] && perm[i] > perm[i + 1])
        {
            if (QL[i] == maxi && QR[i] == maxi)
            {
                if (QL[i] & 1)
                    cout << "1\n";
                else
                    cout << "0\n";
                return;
            }
        }
    }
    cout << "0\n";
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