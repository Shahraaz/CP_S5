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

void print(__int128_t t)
{
    if (t >= 1e18)
        exit(1);
    string temp;
    while (t)
    {
        temp += t % 10 + '0';
        t /= 10;
    }
    reverse(all(temp));
    if (temp.empty())
        temp = "0";
    cout << temp << ' ';
}

void solveCase()
{
    map<__int128_t, int> curr;
    curr[0] = 1;
    for (size_t i = 0; i < 5; i++)
    {
        map<__int128_t, int> next;
        for (size_t j = 0; j < 8; j++)
        {
            for (auto &x : curr)
            {
                auto y = x.f + __int128_t(1LL << i) * j;
                next[y] += x.s;
            }
        }
        curr = next;
        db(i, curr.size());
        for (auto &x : curr)
        {
            cout << "[ ";
            print(x.f);
            cout << ", ";
            print(x.s);
            cout << " ]";
            cout << ", ";
        }
        cout << '\n';
        // print(*(--curr.end()));
        // cout << '\n';
        // print((*(--curr.end())) * (*(--curr.end())) * (*(--curr.end())) * (*(--curr.end())));
        // cout << '\n';
#ifdef LOCAL
        cerr << "Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        // TimeStart = chrono::steady_clock::now();
#endif
    }
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
