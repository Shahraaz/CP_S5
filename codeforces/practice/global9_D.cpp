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
        vector<int> x(n);
        multiset<int> ms;
        for (size_t i = 0; i < n; i++)
        {
            cin >> x[i];
            ms.insert(x[i]);
        }
        auto getMex = [&]() {
            int ret = 0;
            while (ms.count(ret))
                ++ret;
            return ret;
        };
        auto add = [&](int x) {
            ms.insert(x);
        };
        auto remove = [&](int x) {
            ms.erase(ms.find(x));
        };
        vector<int> res;
        int curr = 0;
        while (!is_sorted(x.begin(), x.end()))
        {
            auto mex = getMex();
            curr = 0;
            while (x[curr] == curr)
                curr++;
            db(mex, curr);
            db(x);
            if (mex < n)
            {
                remove(x[mex]);
                x[mex] = mex;
                res.pb(mex);
                add(x[mex]);
                continue;
            }
            if (mex >= curr)
            {
                bool b = true;
                for (int i = n - 1; i >= 0; i--)
                    if (x[i] == curr)
                    {
                        b = false;
                        // curr++;
                        if (x[i] != mex)
                        {
                            remove(x[i]);
                            res.pb(i);
                            x[i] = mex;
                            add(x[i]);
                        }
                        break;
                    }
                if (b)
                {
                    if (x[curr] != mex)
                    {
                        remove(x[curr]);
                        x[curr] = mex;
                        res.pb(curr);
                        add(x[curr]);
                    }
                }
            }
            else //mex <= curr
            {
                if (x[curr] != mex)
                {
                    remove(x[curr]);
                    x[curr] = mex;
                    res.pb(curr);
                    add(x[curr]);
                } // curr++;
            }
        }
        db(2 * x.size(), res.size());
        db(x);
        cout << res.size() << '\n';
        for (auto &x : res)
            cout << x + 1 << ' ';
        cout << '\n';
    }
};

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