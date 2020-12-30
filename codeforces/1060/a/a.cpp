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
    string pat = "8xxxxxxxxxx";
    int l = pat.size() - 1;
    map<char, int> mp;
    for (auto &x : str)
        mp[x]++;
    int res = 0;
    while (mp['8'])
    {
        mp['8']--;
        int l1 = l;
        for (size_t i = '0'; i <= '9' && l1; i++)
        {
            if (i == '8')
                continue;
            int temp = min(l1, mp[i]);
            l1 -= temp;
            mp[i] -= temp;
        }
        if (l1 == 0)
        {
            res++;
        }
        else
        {
            int temp = min(l1, mp['8']);
            l1 -= temp;
            mp['8'] -= temp;
            if (l1 == 0)
            {
                res++;
            }
            else
                break;
        }
    }
    cout << res << '\n';
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