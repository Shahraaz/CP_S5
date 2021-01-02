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
    string str;
    cin >> str;
    int n = str.size();
    int res = 0;
    for (size_t i = 0; i < n; i++)
    {
        bool two = i + 1 < n && str[i] == str[i + 1];
        if (two)
        {
            db(i, "rwo");
            res++;
            set<int> ss;
            for (auto x : {i - 3, i - 2, i - 1, i, i + 1, i + 2, i + 3})
                if (x >= 0 && x < n)
                    ss.insert(str[x] - 'a');
            str[i + 1] = 0;
            while (ss.count(str[i + 1]))
                str[i + 1]++;
            str[i + 1] += 'a';
        }
        else if (i > 0 && i + 1 < n && str[i - 1] == str[i + 1])
        {
            db(i, "the");
            res++;
            set<int> ss;
            for (auto x : {i - 3, i - 2, i - 1, i, i + 1, i + 2, i + 3})
                if (x >= 0 && x < n)
                    ss.insert(str[x] - 'a');
            str[i + 1] = 0;
            while (ss.count(str[i + 1]))
                str[i + 1]++;
            str[i + 1] += 'a';
        }
        db(str, res);
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
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}