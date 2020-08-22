// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 2e5 + 5, MOD = 1000000007;

struct Solution
{
    Solution() {}
    void solveCase();
};

void Solution::solveCase()
{
    deque<int> poses[26];
    deque<char> t, u;
    string str;
    cin >> str;
    if (is_sorted(all(str)))
    {
        cout << str << '\n';
        return;
    }
    for (size_t i = 0; i < str.size(); i++)
        poses[str[i] - 'a'].pb(i);
    // string t;
    int ptr = 0;
    set<pair<int, char>> ss;
    for (size_t i = 0; i < str.size(); i++)
        ss.insert({i, str[i]});
    for (size_t i = 0; i < 26; i++)
    {
        if (poses[i].empty())
            continue;
        int lptr = poses[i].front();
        int rptr = poses[i].back();
        db(i, lptr, rptr);
        while (t.size() && t.back() <= ('a' + i))
        {
            u.pb(t.back());
            t.pop_back();
        }
        db(ss);
        // auto end_it = ss.upper_bound({rptr, 'a'});
        while (ss.size())
        {
            auto it = ss.begin();
            if (it == ss.end())
                break;
            if (it->f > rptr)
                break;
            if (it->s == (i + 'a'))
                u.pb(i + 'a');
            else
                t.pb(it->s);
            ss.erase(it);
        }
        db(u);
        db(t);
    }
    while (t.size())
    {
        u.pb(t.back());
        t.pop_back();
    }
    db(u);
    db(t);
    for (auto &x : u)
    {
        cout << x;
    }
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
