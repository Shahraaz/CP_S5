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
    int cntone = count(all(str), '1');
    int cnttzero = n - cntone;
    db(n, str);
    db(cntone, cnttzero);
    if (n % 2 || cntone % 2 || str.front() == '0' || str.back() == '0')
    {
        cout << "NO\n";
        return;
    }
    vector<char> res(n, '$');
    vector<char> res2(n, '$');
    int one = 0;
    bool zero = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (str[i] == '1')
        {
            one++;
            if (2 * one > cntone)
                res[i] = res2[i] = ')';
            else
                res[i] = res2[i] = '(';
        }
        else
        {
            res[i] = zero ? '(' : ')';
            res2[i] = (!zero) ? '(' : ')';
            zero = !zero;
        }
    }
    cout << "YES\n";
    for (auto &x : res)
        cout << x;
    cout << '\n';
    for (auto &x : res2)
        cout << x;
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