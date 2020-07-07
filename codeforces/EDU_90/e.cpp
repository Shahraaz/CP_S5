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
    int f(int lastD, int k, int cnt9)
    {
        int ans = 0;
        int prev = 0;
        int n = lastD;
        // db(lastD, k, cnt9);
        for (size_t j = 0; j < k; j++)
        {
            ++lastD;
            if (lastD == 10)
            {
                lastD = 0;
                ans -= n - 1 + cnt9 * 9;
                prev = n - 1 + cnt9 * 9;
                prev = -prev;
                lastD = 0;
            }
            else
            {
                ans += prev + 1;
                prev++;
            }
        }
        // db(ans);
        return ans;
    }

    string minn(int x)
    {
        string ans = "";
        if (x < 8)
        {
            ans += x + '0';
            return ans;
        }
        ans.pb('8');
        x -= 8;
        while (x >= 9)
        {
            ans.pb('9');
            x -= 9;
        }
        if (x > 0)
            ans.pb('0' + x);
        reverse(all(ans));
        return ans;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, k;
        cin >> n >> k;
        vector<string> v;
        for (int lastDigit = 0; lastDigit <= 9; lastDigit++)
        {
            for (int cnt9 = 0; cnt9 < 500; cnt9++)
            {
                int extra = f(lastDigit, k, cnt9);
                if (n >= extra && (n - extra) % (k + 1) == 0)
                {
                    int x = n - extra;
                    x /= (k + 1);
                    x -= lastDigit + cnt9 * 9;
                    if (x < 0)
                        continue;
                    string s = "";
                    if (x > 0)
                        s = minn(x);
                    for (size_t i = 0; i < cnt9; i++)
                        s += '9';
                    s += '0' + lastDigit;
                    v.pb(s);
                }
            }
        }
        db(n, k, v);
        if (v.size() == 0)
        {
            cout << -1 << '\n';
            return;
        }
        cout << *min_element(all(v), [](string a, string b) {
            if (a.length() == b.length())
                return a < b;
            return a.length() < b.length();
        }) << '\n';
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
