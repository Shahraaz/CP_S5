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
    string truncate(string str)
    {
        string ret = "";
        for (auto &x : str)
        {
            if (ret.size() == 0 && x == '0')
                continue;
            ret += x;
        }
        if (ret == "" and count(all(str), '0'))
            ret = "0";
        return ret;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        string n;
        cin >> n;
        int sum = 0;
        for (auto &x : n)
            sum += (x - '0') % 3;
        sum %= 3;
        db(n, sum);
        vector<string> sols;
        if (sum == 0)
        {
            sols.pb(truncate(n));
        }
        else
        {
            for (int i = n.size() - 1; i >= 0; i--)
            {
                if ((n[i] - 0) % 3 == sum)
                {
                    auto t = n.substr(0, i) + n.substr(i + 1);
                    t = truncate(t);
                    if (t.size())
                        sols.pb(t);
                    break;
                }
            }
            int p1 = -1;
            for (int i = n.size() - 1; i >= 0; i--)
            {
                if ((n[i] - 0) % 3 == 0)
                    continue;
                if ((n[i] - 0) % 3 != sum)
                {
                    if (p1 == -1)
                    {
                        p1 = i;
                        continue;
                    }
                    auto t = n.substr(0, i) + n.substr(i + 1, p1 - i - 1) + n.substr(p1 + 1);
                    t = truncate(t);
                    if (t.size())
                        sols.pb(t);
                    break;
                }
            }
        }
        db(sols);
        if (sols.size() == 0)
            cout << -1 << '\n';
        else
            cout << *max_element(sols.begin(), sols.end(), [](string a, string b) -> bool { return a.length() < b.length(); }) << '\n';
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
