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
    string s;
    cin >> n;
    cin >> s;
    bool cycleExist = true;
    vector<bool> isChill(n);
    for (size_t i = 0; i < n; i++)
    {
        if (s[i] == '-' || s[i] == '<')
            continue;
        cycleExist = false;
    }
    if (!cycleExist)
    {
        cycleExist = true;
        for (size_t i = 0; i < n; i++)
        {
            if (s[i] == '-' || s[i] == '>')
                continue;
            cycleExist = false;
        }
    }
    for (size_t i = 0; i < n; i++)
    {
        if (s[i] == '-')
        {
            isChill[i] = 1;
            isChill[(i + 1) % n] = 1;
        }
        else if (s[i] == '<' && s[(i - 1 + n) % n] == '<')
            isChill[i] = cycleExist;
        else if (s[i] == '>' && s[(i - 1 + n) % n] == '>')
            isChill[i] = cycleExist;
    }
    cout << count(all(isChill), 1) << '\n';
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
