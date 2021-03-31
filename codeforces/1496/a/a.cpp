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

void solveCase()
{
    int n, k;
    cin >> n >> k;
    string str;
    cin >> str;
    vector<int> res(k + 1);
    int fptr = 0, rptr = n - 1;
    for (size_t i = 0; i < k; i++)
    {
        if (fptr > rptr || str[fptr] != str[rptr])
        {
            cout << "NO\n";
            return;
        }
        ++fptr;
        --rptr;
    }
    if (rptr - fptr + 1 >= 1)
        cout << "YES\n";
    else
        cout << "NO\n";
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
        solveCase();
    return 0;
}