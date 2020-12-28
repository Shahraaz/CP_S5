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
    int n;
    cin >> n;
    string str;
    cin >> str;
    vector<int> res(n);
    int num = n, last = 0;
    for (size_t i = 0; i < n; i++)
        if (i == (n - 1) || str[i] == '>')
        {
            for (int j = i; j >= last; j--)
                res[j] = num--;
            last = i + 1;
        }
    for (auto &x : res)
        cout << x << ' ';
    cout << '\n';
    num = 1, last = 0;
    for (size_t i = 0; i < n; i++)
        if (i == (n - 1) || str[i] == '<')
        {
            for (int j = i; j >= last; j--)
                res[j] = num++;
            last = i + 1;
        }
    for (auto &x : res)
        cout << x << ' ';
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
        solveCase();
    return 0;
}