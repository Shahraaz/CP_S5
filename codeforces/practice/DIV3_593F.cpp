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
    string s, t;
    cin >> n;
    cin >> s >> t;
    vector<int> hash1(26);
    vector<int> hash2(26);
    for (size_t i = 0; i < n; i++)
    {
        hash1[s[i] - 'a']++;
        hash2[t[i] - 'a']++;
    }
    bool ok = false;
    // db(hash1, hash2);
    for (size_t i = 0; i < 26; i++)
    {
        ok = ok || (hash1[i] > 1) || (hash2[i] > 1);
        if (hash1[i] != hash2[i])
        {
            db("a");
            cout << "NO\n";
            return;
        }
    }
    ll invCnt = 0;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < (s[i] - 'a'); j++)
            invCnt += hash1[j];
        hash1[s[i] - 'a']--;
    }
    db(s);
    db(invCnt);
    invCnt %= 2;
    if (invCnt)
        swap(t[n - 1], t[n - 2]);
    sort(all(s));
    invCnt = 0;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < (t[i] - 'a'); j++)
            invCnt += hash2[j];
        hash2[t[i] - 'a']--;
    }
    db(t);
    db(invCnt);
    if (invCnt % 2)
        swap(s[n - 1], s[n - 2]);
    sort(all(t));
    db(s, t);
    if (s == t || ok)
        cout << "YES\n";
    else
        cout << "NO\n";
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
