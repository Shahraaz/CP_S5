#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
using ll = long long;
const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    int maxidx = max_element(all(a)) - a.begin();
    deque<int> left, right;
    for (size_t i = 0; i < maxidx; i++)
        left.pb(a[i]);
    for (size_t i = maxidx + 1; i < n; i++)
        right.pb(a[i]);
    int now = a[maxidx];
    reverse(all(left));
    reverse(all(right));
    while (left.size() || right.size())
    {
        if (right.empty())
        {
            if (now > left.front())
                now = left.front(), left.pop_front();
            else
            {
                cout << "NO\n";
                return;
            }
        }
        else if (left.empty())
        {
            if (now > right.back())
                now = right.back(), right.pop_back();
            else
            {
                cout << "NO\n";
                return;
            }
        }
        else
        {
            if (left.front() > right.back())
            {
                if (now > left.front())
                    now = left.front(), left.pop_front();
                else
                {
                    cout << "NO\n";
                    return;
                }
            }
            else
            {
                if (now > right.back())
                    now = right.back(), right.pop_back();
                else
                {
                    cout << "NO\n";
                    return;
                }
            }
        }
    }
    cout << "YES\n";
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}