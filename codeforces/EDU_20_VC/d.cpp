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
    int k;
    cin >> k;
    string str;
    cin.ignore();
    getline(cin, str);
    db(str);
    stringstream sin(str);
    vector<string> strs;
    while (sin >> str)
        strs.pb(str);
    for (size_t i = 0; i + 1 < strs.size(); i++)
        strs[i].pb(' ');
    int low = 0, high = 1e7;
    int ans = high;
    auto check = [&](int width) -> int {
        int lineCnt = 1;
        int currLineLen = 0;
        for (size_t i = 0; i < strs.size(); i++)
        {
            int prefLen = 0;
            int j = 0;
            int prev = 0;
            while (j < strs[i].size())
            {
                prefLen++;
                if (prefLen > width)
                    return MOD;
                if (strs[i][j] == '-' || strs[i][j] == ' ')
                    if (prefLen + currLineLen <= width)
                    {
                        currLineLen += prefLen;
                        prefLen = 0;
                    }
                    else
                    {
                        lineCnt++;
                        currLineLen = prefLen;
                        prefLen = 0;
                    }
                ++j;
            }
            if (prefLen + currLineLen <= width)
            {
                currLineLen += prefLen;
                prefLen = 0;
            }
            else
            {
                lineCnt++;
                currLineLen = prefLen;
                prefLen = 0;
            }
        }
        return lineCnt;
    };
    while (low <= high)
    {
        int mid = low + high;
        mid /= 2;
        if (check(mid) <= k)
        {
            ans = min(ans, mid);
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    cout << ans << '\n';
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
