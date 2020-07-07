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

using score = vector<int>;

map<string, score> mp;
map<string, int> cnt;

class Solution
{
private:
    score dfs(string curr)
    {
        if (mp.find(curr) != mp.end())
            return mp[curr];
        vector<int> ret = {0, 0, 0};
        for (char c = 'a'; c <= 'z'; c++)
            for (size_t i = 0; i < 2; i++)
            {
                auto next = curr;
                if (i)
                    next += c;
                else
                    next = c + next;
                if (cnt.find(next) == cnt.end())
                    continue;
                int score = cnt[next];
                int sum = 0, maxVal = 0;
                for (auto &x : next)
                {
                    sum += x - 'a' + 1;
                    maxVal = max(maxVal, x - 'a' + 1);
                }
                score += maxVal * sum;
                auto future = dfs(next);
                future[0] = 1 - future[0];
                swap(future[1], future[2]);
                future[1] *= -1;
                future[2] *= -1;
                future[1] += score;
                ret = max(ret, future);
            }
        return mp[curr] = ret;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        for (size_t i = 0; i < n; i++)
        {
            string str;
            cin >> str;
            set<string> mySet;
            for (size_t j = 0; j < str.size(); j++)
                for (size_t k = j; k < str.size(); k++)
                    mySet.insert(str.substr(j, k - j + 1));
            for (auto &x : mySet)
                cnt[x]++;
        }
        auto res = dfs("");
        if (!res[0])
            cout << "Second\n";
        else
            cout << "First\n";
        cout << res[1] << ' ' << -res[2] << '\n';
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
