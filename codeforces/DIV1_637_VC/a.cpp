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
    int n;
    cin >> n;
    vector<int> vecc(n + 1);
    vector<int> inverse(n + 1);
    set<pair<int, int>> ss;
    multiset<int> maxResSet;
    for (size_t i = 1; i <= n; i++)
    {
        maxResSet.insert(1);
        int x;
        cin >> x;
        // vecc[i] = x;
        inverse[x] = i;
        ss.insert({i, 1});
    }
    db(vecc);
    db(inverse);
    db(ss);
    for (size_t i = 1; i <= n; i++)
    {
        db(i, ss);
        int maxRes = *maxResSet.rbegin();
        db(maxRes);
        auto it = ss.lower_bound({inverse[i], 0});
        if (it != ss.end())
        {
            db(*it);
        }
        if (it == ss.end() || it->f != inverse[i] || it->s != maxRes)
        {
            cout << "no\n";
            return;
        }
        auto temp = *it;
        db(temp);
        auto it2 = it;
        if (it2 != ss.end() && (++it2) != ss.end())
        {
            auto temp2 = *it2;
            db(temp2);
            ss.erase(it);
            ss.erase(it2);
            maxResSet.erase(maxResSet.find(temp.s));
            maxResSet.erase(maxResSet.find(temp2.s));
            temp2.s += temp.s;
            maxResSet.insert(temp2.s);
            ss.insert(temp2);
        }
        else
        {
            ss.erase(it);
            maxResSet.erase(maxResSet.find(temp.s));
            // maxResSet.insert(temp2.s);
        }
    }
    cout << "yes\n";
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
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
