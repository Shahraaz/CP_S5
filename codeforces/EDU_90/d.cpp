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
        vector<int> a(n);
        vector<ll> diff(n);
        ll curr = 0;
        multiset<ll> setOdd, setEven;
        for (size_t i = 0; i < n; i++)
        {
            cin >> a[i];
            if (i > 0)
                diff[i] = diff[i - 1];
            if (i & 1)
            {
                diff[i] += a[i];
                setOdd.insert(diff[i]);
            }
            else
            {
                curr += a[i];
                diff[i] -= a[i];
                setEven.insert(diff[i]);
            }
        }
        db(diff);
        ll ret = 0;
        for (size_t i = 0; i < n; i++)
        {
            db(i, setEven, setOdd);
            ll temp = 0;
            if (i > 0)
                temp = diff[i - 1];
            if (i & 1)
            {
                if (setEven.size())
                    ret = max(ret, *setEven.rbegin() - temp);
                setOdd.erase(setOdd.find(diff[i]));
            }
            else
            {
                if (setOdd.size())
                    ret = max(ret, *setOdd.rbegin() - temp);
                setEven.erase(setEven.find(diff[i]));
            }
        }
        cout << curr + ret << '\n';
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
