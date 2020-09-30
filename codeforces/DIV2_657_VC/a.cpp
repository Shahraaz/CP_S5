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

void solveCase()
{
    string s;
    int n;
    cin >> n;
    cin >> s;
    string res;
    string target = "abacaba";
    // int n = s.length();
    auto match = [&](int start, int end) -> bool {
        if (end > n)
            return false;
        db(start, end, res, "match begin");
        for (int i = start; i < end; i++)
        {
            if (res[i] == '?')
                res[i] = target[i - start];
            else if (res[i] != target[i - start])
            {
                db(res);
                db(start, end, i);
                return false;
            }
        }
        db(start, end, res, "match");
        return true;
    };
    auto not_match = [&](int start) -> bool {
        for (int i = 0; i < n; i++)
            if (res[i] == '?')
                res[i] = 'z';
        for (int i = 0; i < n; i++)
            if (i != start)
                if (res.substr(i, 7) == target)
                    return false;
        db(start, res);
        return true;
    };
    for (size_t i = 0; i < n; i++)
    {
        res = s;
        if (match(i, i + target.size()) && not_match(i))
        {
            cout << "Yes\n"
                 << res << '\n';
            return;
        }
    }
    cout << "No\n";
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
