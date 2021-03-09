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

string str;

void addString(string &rhs)
{
    int len_rhs = min(str.size(), rhs.size());
    int n = str.size();
    auto pp = rhs + "$" + str.substr(n - len_rhs, len_rhs);
    vector<int> p(pp.size());
    db(str, rhs, pp);
    for (size_t i = 1; i < pp.size(); i++)
    {
        int g = p[i - 1];
        while (g && pp[i] != pp[g])
            g = p[g - 1];
        p[i] = g + (pp[i] == pp[g]);
        db(i, p[i]);
    }
    int common = p.back();
    for (size_t i = common; i < rhs.size(); i++)
        str += rhs[i];
    db(common, str);
}

void solveCase()
{
    int n;
    cin >> n;
    cin >> str;
    for (size_t i = 1; i < n; i++)
    {
        string str2;
        cin >> str2;
        addString(str2);
    }
    cout << str << '\n';
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