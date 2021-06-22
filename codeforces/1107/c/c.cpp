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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    string str;
    cin >> str;
    priority_queue<int> pQ;
    char prev = '$';
    ll res = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (prev == str[i])
            pQ.push(a[i]);
        else
        {
            int cnt = 0;
            while (pQ.size())
            {
                if (cnt < k)
                    res += pQ.top();
                pQ.pop();
                cnt++;
            }
            prev = str[i];
            pQ.push(a[i]);
        }
    }
    int cnt = 0;
    while (pQ.size())
    {
        if (cnt < k)
            res += pQ.top();
        pQ.pop();
        cnt++;
    }
    cout << res << '\n';
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