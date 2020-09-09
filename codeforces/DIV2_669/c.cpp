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

struct Solution
{
    Solution() {}
    void solveCase();
};

void Solution::solveCase()
{
    int n;
    cin >> n;
    set<int> rem;
    set<int> inset;
    for (size_t i = 0; i < n; i++)
    {
        rem.insert(i + 1);
        inset.insert(i + 1);
    }
    vector<int> perm(n + 1);
    while (rem.size() > 1)
    {
        auto idx1 = *rem.begin();
        auto idx2 = *next(rem.begin());
        db(rem);
        db(perm);
        int a, b;
        cout << "? ";
        cout << idx1 << ' ' << idx2 << endl;
        cin >> a;
        cout << "? ";
        cout << idx2 << ' ' << idx1 << endl;
        cin >> b;
        if (a > b)
        {
            perm[idx1] = a;
            inset.erase(a);
            rem.erase(idx1);
        }
        else
        {
            perm[idx2] = b;
            inset.erase(b);
            rem.erase(idx2);
        }
    }
    if (rem.size())
    {
        perm[*rem.begin()] = *inset.begin();
    }
    cout << "! ";
    for (size_t i = 1; i <= n; i++)
        cout
            << perm[i] << ' ';
    cout << endl;
}

int32_t main()
{
#ifndef LOCAL
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
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
