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
#define int long long

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, m, p;
        cin >> n >> m >> p;
        vector<int> a(n), b(m);
        for (auto &x : a)
            cin >> x;
        map<int, int> bHash;
        for (auto &x : b)
        {
            cin >> x;
            bHash[x]++;
        }
        int temp = bHash.size();
        vector<int> res;
        vector<bool> vis(n);
        for (int i = 0; i < n; i++)
        {
            if (vis[i])
                continue;
            int last = i + (m - 1) * p;
            if (last >= n)
                break;
            map<int, int> currHash;
            int matchCnt = 0;
            auto doChange = [&](int num, int dx) {
                matchCnt -= currHash[num] == bHash[num];
                currHash[num] += dx;
                matchCnt += currHash[num] == bHash[num];
            };
            for (int j = i; j < n; j += p)
            {
                vis[j] = true;
                if (j - m * p >= 0)
                    doChange(a[j - m * p], -1);
                doChange(a[j], 1);
                db(j, j - (m - 1) * p, bHash, currHash, matchCnt);
                if (matchCnt == temp)
                    res.pb(j - (m - 1) * p);
            }
        }
        cout << res.size() << '\n';
        sort(all(res));
        for (auto &x : res)
            cout << x + 1 << ' ';
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
