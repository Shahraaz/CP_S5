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
    for (size_t len = 1; len <= n; len++)
    {
        string b, en;
        for (size_t i = 0; i < len; i++)
        {
            b += "a";
            en += "z";
        }
        while (true)
        {
            bool ok = false;
            for (int i = 0; i + len - 1 < n; i++)
                if (str.substr(i, len) == b)
                    ok = true;
            if (!ok)
            {
                cout << b << '\n';
                return;
            }
            if (b == en)
                break;
            for (int i = len - 1; i >= 0; i--)
            {
                if (b[i] == 'z')
                    b[i] = 'a';
                else
                {
                    b[i]++;
                    break;
                }
            }
        }
    }
    assert(false);
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