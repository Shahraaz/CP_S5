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

void solveCase()
{
    int r, c;
    cin >> r >> c;
    vector<string> vecc(r);
    vector<int> R(r), C(c);
    for (size_t i = 0; i < r; i++)
        cin >> vecc[i];
    int total = 0;
    for (size_t i = 0; i < r; i++)
        for (size_t j = 0; j < c; j++)
            if (vecc[i][j] == 'A')
            {
                total++;
                R[i]++;
                C[j]++;
            }
    if (total == 0)
        cout << "MORTAL" << '\n';
    else if (total == (r * c))
        cout << 0 << '\n';
    else if (R.front() == c || R.back() == c || C.front() == r || C.back() == r)
        cout << 1 << '\n';
    else if (vecc.front().front() == 'A' || vecc.front().back() == 'A' || vecc.back().front() == 'A' || vecc.back().back() == 'A')
        cout << 2 << '\n';
    else if (*max_element(all(R)) == c || *max_element(all(C)) == r)
        cout << 2 << '\n';
    else if (R.front() || R.back() || C.front() || C.back())
        cout << 3 << '\n';
    else
        cout << 4 << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
