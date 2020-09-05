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
    string str;
    cin >> str;
    int n = str.size();
    vector<vector<int>> prefSum(n, vector<int>(3));
    int maxLen = 0;
    int startIdx = 0;
    int endIdx = 0;
    map<vector<int>, int> mp;
    vector<int> cntOpen(n);
    for (size_t i = 0; i < n; i++)
    {
        if (i > 0)
            cntOpen[i] = cntOpen[i - 1];
        cntOpen[i] += (str[i] == '[');
    }
    mp[{0, 0, 0}] = -1;
    for (size_t i = 0; i < n; i++)
    {
        if (i > 0)
            prefSum[i] = prefSum[i - 1];

        if (str[i] == '(')
            prefSum[i][0]++;
        else if (str[i] == ')')
            prefSum[i][0]--;
        else if (str[i] == '{')
            prefSum[i][1]++;
        else if (str[i] == '}')
            prefSum[i][1]--;
        else if (str[i] == '[')
            prefSum[i][2]++;
        else if (str[i] == ']')
            prefSum[i][2]--;

        // prefSum[i][0] = -prefSum[i][0];
        // prefSum[i][1] = -prefSum[i][1];
        // prefSum[i][2] = -prefSum[i][2];

        auto it = mp.find(prefSum[i]);
        db(i, prefSum[i]);
        db(mp);
        if (it != mp.end())
        {
            int lptr = it->s;
            int cnt = cntOpen[i];
            if (lptr > 0)
                cnt -= cntOpen[lptr - 1];
            db(lptr, i, cnt);
            if (cnt > maxLen)
            {
                maxLen = cnt;
                startIdx = lptr + 1;
                endIdx = i;
            }
        }
        // prefSum[i][0] = -prefSum[i][0];
        // prefSum[i][1] = -prefSum[i][1];
        // prefSum[i][2] = -prefSum[i][2];
        it = mp.find(prefSum[i]);
        if (it == mp.end())
            if (i + 1 >= n || str[i + 1] == '(' || str[i + 1] == '{' || str[i + 1] == '[')
                mp[prefSum[i]] = i;
        db(startIdx, endIdx, i);
    }
    cout << maxLen << '\n';
    if (maxLen)
    {
        cout << str.substr(startIdx, endIdx - startIdx + 1) << '\n';
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
