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

#define NO              \
    {                   \
        cout << "NO\n"; \
        return;         \
    }

void solveCase()
{
    int k;
    string a, b, s;
    cin >> k >> s >> a >> b;
    vector<char> res(k, '$');
    vector<bool> used(k);
    int n = s.size();
    bool is_s_greater_than_a = false;
    db(k, n);
    db(s);
    db(a);
    db(b);

    function<bool(int, int)> solve = [&](int pos, int rel) -> bool {
        if (pos == n)
            return true;
        int cidx = s[pos] - 'a';
        if (res[cidx] != '$')
        {
            if (!rel && res[cidx] < a[pos])
                return false;
            return solve(pos + 1, rel || (a[pos] < res[cidx]));
        }
        for (char c = 'a'; c < 'a' + k; c++)
        {
            if (!rel && c < a[pos])
                continue;
            if (used[c - 'a'])
                continue;
            used[c - 'a'] = 1;
            res[cidx] = c;
            if (solve(pos + 1, rel || (a[pos] < res[cidx])))
            {
                db("true", pos, rel, c, used);
                db(res);
                return true;
            }
            res[cidx] = '$';
            used[c - 'a'] = 0;
        }
        db("false", pos, rel, used);
        db(res);
        return false;
    };

    if (!solve(0, 0))
        NO;

    db(res);
    for (size_t i = 0; i < n; i++)
        s[i] = res[s[i] - 'a'];
    for (char c = 'a'; c < 'a' + k; c++)
        if (res[c - 'a'] == '$')
        {
            bool done = false;
            for (char c1 = 'a'; !done && c1 < 'a' + k; c1++)
                if (!used[c1 - 'a'])
                {
                    used[c1 - 'a'] = 1;
                    res[c - 'a'] = c1;
                    done = true;
                }
            assert(done);
        }
    assert(a <= s);
    if (s <= b)
    {
        cout << "YES\n";
        for (auto &c : res)
            cout << c;
        cout << '\n';
    }
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