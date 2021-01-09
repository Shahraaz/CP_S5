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

const int _NSeive = 1e6 + 10;
vector<bool> isPrime(_NSeive, true);
vector<int> spf(_NSeive);
vector<int> myhash(_NSeive);

void buildSeive()
{
    isPrime[1] = false;
    isPrime[0] = false;
    for (int i = 4; i < _NSeive; i += 2)
    {
        isPrime[i] = false;
        spf[i] = 2;
    }
    for (int i = 3; i * i < _NSeive; i += 2)
        if (isPrime[i])
            for (int j = i * 2; j < _NSeive; j += i)
            {
                if (spf[j] == 0)
                    spf[j] = i;
                isPrime[j] = false;
            }
    for (size_t i = 1; i < _NSeive; i++)
    {
        int i1 = i, conv = 1;
        while (spf[i1])
        {
            int p1 = spf[i1];
            int cnt = 0;
            while (i1 % p1 == 0)
            {
                cnt++;
                i1 /= p1;
            }
            if (cnt & 1)
                conv *= p1;
        }
        if (i1 > 1)
            conv *= i1;
        myhash[i] = conv;
        // db(i, conv);
    }
}

void solveCase()
{
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, int> mymap;
    map<int, int> mymap1;
    for (auto &x : a)
    {
        cin >> x;
        db(x, myhash[x]);
        x = myhash[x];
        mymap[x]++;
    }
    vector<int> res(2);
    for (auto &x : mymap)
    {
        res[0] = max(res[0], x.second);
        if (x.second & 1)
            mymap1[x.first] += x.second;
        else
            mymap1[1] += x.second;
    }
    for (auto &x : mymap1)
        res[1] = max(res[1], x.second);
    db(mymap);
    db(mymap1);
    int q;
    cin >> q;
    for (size_t i = 0; i < q; i++)
    {
        ll x;
        cin >> x;
        if (x == 0)
            cout << res[0] << '\n';
        else
            cout << res[1] << '\n';
    }
}

int32_t main()
{
    buildSeive();
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}