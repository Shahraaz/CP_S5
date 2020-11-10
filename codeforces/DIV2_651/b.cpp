#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
using ll = long long;
const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    int n;
    cin >> n;
    vector<int> odd, even;
    for (size_t i = 0; i < 2 * n; i++)
    {
        int x;
        cin >> x;
        if (x & 1)
            odd.push_back(i + 1);
        else
            even.push_back(i + 1);
    }
    if (odd.size() & 1)
    {
        odd.pop_back();
        assert(even.size());
        even.pop_back();
    }
    else if (odd.size() > 1)
    {
        odd.pop_back();
        odd.pop_back();
    }
    else if (even.size() > 1)
    {
        even.pop_back();
        even.pop_back();
    }
    else
        assert(false);
    while (odd.size())
    {
        cout << odd.back() << ' ';
        odd.pop_back();
    }
    while (even.size())
    {
        cout << even.back() << ' ';
        even.pop_back();
    }
    cout << '\n';
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
#ifdef TIMER
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}