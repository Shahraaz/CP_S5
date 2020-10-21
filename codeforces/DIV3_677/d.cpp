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
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, vector<int>> cnt;
    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
        cnt[a[i]].pb(i);
    }
    if (cnt.size() == 1)
        cout << "NO\n";
    else
    {
        cout << "YES\n";
        pair<int, vector<int>> mini = *cnt.begin();
        for (pair<int, vector<int>> x : cnt)
            if (x.s.size() < mini.s.size())
                mini = x;
        cnt.erase(mini.f);
        auto prev = -1;
        while (mini.s.size())
        {
            auto temp = cnt.begin();
            if (prev >= 0)
                cout << prev + 1 << ' ' << temp->s.back() + 1 << '\n';
            cout << mini.s.back() + 1 << ' ' << temp->s.back() + 1 << '\n';
            prev = mini.s.back();
            mini.s.pop_back();
            temp->s.pop_back();
            if (temp->s.size() == 0)
                cnt.erase(temp);
        }
        while (cnt.size())
        {
            auto temp = cnt.begin();
            cout << prev + 1 << ' ' << temp->s.back() + 1 << '\n';
            temp->s.pop_back();
            if (temp->s.size() == 0)
                cnt.erase(temp);
        }
    }
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
