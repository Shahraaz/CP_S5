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

const string HAHA = "haha";
struct str
{
    string s;
    ll already;
    str(string _s = "", ll a = 0) : s(_s), already(a) {}
    bool operator<(const str &rhs) const
    {
        if (s == rhs.s)
            return already < rhs.already;
        return s < rhs.s;
    }
    str norm()
    {
        str now = *this;
        if (now.s.size() < 4)
            return now;
        now.s = now.s.substr(0, 3) + "$" + now.s.substr(now.s.size() - 3, 3);
        return now;
    }
};

ll comp(string s)
{
    int ret = 0;
    for (int i = 0; i + HAHA.size() - 1 < s.size(); i++)
    {
        if (s.substr(i, 4) == "haha")
            ret++;
    }
    db(s, ret);
    return ret;
}

str operator+(const str &l, const str &r)
{
    str ret(l.s + r.s, l.already + r.already + comp(l.s + r.s));
    return ret;
}

void solveCase()
{
    map<string, str> mp;
    int n;
    cin >> n;
    string prev = "$";
    for (size_t i = 0; i < n; i++)
    {
        string lhs, op;
        cin >> lhs >> op;
        prev = lhs;
        // db(lhs, op);
        if (op == ":=")
        {
            string rhs;
            cin >> rhs;
            // db(rhs);
            mp[lhs] = str(rhs, comp(rhs));
        }
        else
        {
            string rhs1, rhs2;
            cin >> rhs1 >> op >> rhs2;
            // db(rhs1, op, rhs2);
            mp[lhs] = mp[rhs1] + mp[rhs2];
        }
        mp[lhs] = mp[lhs].norm();
        db(lhs, mp[lhs].already, mp[lhs].s);
    }
    cout << mp[prev].already << '\n';
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