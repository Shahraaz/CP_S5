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
    int m;
    cin >> m;
    string str;
    cin >> str;
    int n = str.size();
    vector<vector<int>> cnt(n, vector<int>(26));
    vector<int> poses[26];
    for (size_t i = 0; i < n; i++)
    {
        // db(i, str[i]);
        poses[str[i] - 'a'].pb(i);
        if (i > 0)
            cnt[i] = cnt[i - 1];
        cnt[i][str[i] - 'a']++;
    }
    for (int c = 0; c < 26; c++)
    {
        if (poses[c].empty())
            continue;
        string res;
        int now = 0;
        int prev = -1;
        bool golbOk = true;
        while (now < n)
        {
            int cc = str[now] - 'a';
            db(now, prev, c, cc, res);
            if (cc < c)
            {
                db("a");
                prev = now;
                ++now;
            }
            else if ((now - prev) >= m)
            {
                db("b");
                int j = now;
                int cnt = m;
                bool ok = false;
                while (j >= 0 && cnt > 0)
                {
                    if (str[j] == ('a' + c))
                    {
                        res.pb(str[j]);
                        ok = true;
                        prev = j;
                        break;
                    }
                    --cnt;
                    --j;
                }
                ++now;
                if (!ok)
                {
                    golbOk = false;
                    break;
                }
            }
            else
                now++;
        }
        if (golbOk)
        {
            string res2;
            for (int c1 = 0; c1 < c; c1++)
                for (size_t i = 0; i < poses[c1].size(); i++)
                    res2.pb(c1 + 'a');
            db(res, res2);
            cout << res2 << res << '\n';
            return;
        }
    }
    // assert(false);
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