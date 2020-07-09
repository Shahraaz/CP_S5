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
        int n, k;
        cin >> n >> k;
        --k;
        vector<ll> factorials;
        while (true)
        {
            if (factorials.size() && factorials.back() > INT_MAX)
                break;
            if (factorials.size() == 0)
                factorials.pb(1);
            else
            {
                ll temp = factorials.back() * (factorials.size() + 1);
                factorials.pb(temp);
            }
        }
        db(factorials, n, factorials.size());
        if (n < factorials.size())
        {
            db(k, factorials[n - 1]);
            if (k + 1 > factorials[n - 1])
            {
                cout << -1 << '\n';
                return;
            }
        }
        set<ll> luckyNumbers;
        function<void(ll)> dfs = [&](ll prev) -> void {
            if (prev > INT_MAX)
                return;
            ll curr = prev * 10 + 4;
            luckyNumbers.insert(curr);
            dfs(curr);
            curr = prev * 10 + 7;
            luckyNumbers.insert(curr);
            dfs(curr);
        };
        function<bool(int)> isLucky = [&](int x) -> bool {
            // while (x)
            // {
            //     if (x % 10 == 7 || x % 10 == 4)
            //     {
            //         x /= 10;
            //         continue;
            //     }
            //     return false;
            // }
            // return true;
            return luckyNumbers.count(x);
        };
        dfs(0);
        db(luckyNumbers.size());
        set<int> s;
        int startIdx = 0;
        int res = 0;
        /*
            compute startIdx
        */
        if (n > 20)
        {
            startIdx = n - 20;
            for (auto &x : luckyNumbers)
                if (x < startIdx)
                    res++;
        }
        for (size_t i = startIdx; i <= n; i++)
            s.insert(i);
        int lim = factorials.size();
        for (int i = startIdx; i <= n; i++)
        {
            int next = n - i - 1;
            db(i, next, lim, k, s);
            if (next >= lim)
            {
                // cout << *s.begin() << '\n';
                if (isLucky(i) && isLucky(*s.begin()))
                    res++;
                s.erase(s.begin());
                continue;
            }
            if (s.size() == 1)
            {
                if (isLucky(i) && isLucky(*s.begin()))
                    res++;
                // cout << *s.begin() << '\n';
                s.erase(s.begin());
                continue;
            }
            int pos = k / factorials[next];
            k -= pos * factorials[next];
            db(next, pos, factorials[next]);
            for (auto &x : s)
            {
                if (pos <= 0)
                {
                    if (isLucky(i) && isLucky(x))
                        res++;
                    // s.erase(s.begin());
                    // cout << x << '\n';
                    s.erase(x);
                    break;
                }
                pos--;
            }
        }
        cout << res << '\n';
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
