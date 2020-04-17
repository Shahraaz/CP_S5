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

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        map<int, int> rs;
        for (size_t i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            rs[x]++;
        }
        set<pair<int, int>> s;
        vector<vector<int>> res;
        for (auto &elem : rs)
            s.insert({elem.s, elem.f});
        while (s.size() > 2)
        {
            db(s);
            auto one = *s.rbegin();
            auto two = *(++s.rbegin());
            auto three = *(++(++s.rbegin()));
            s.erase(one);
            s.erase(two);
            s.erase(three);
            res.pb({one.s, two.s, three.s});
            one.f--;
            two.f--;
            three.f--;
            if (one.f)
                s.insert(one);
            if (two.f)
                s.insert(two);
            if (three.f)
                s.insert(three);
        }
        cout << res.size() << '\n';
        for (auto &x : res)
        {
            sort(all(x));
            reverse(all(x));
            for (auto &y : x)
                cout << y << ' ';
            cout << '\n';
        }
    }
};

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
