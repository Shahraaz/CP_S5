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

#define int ll

const int NAX = 2e5 + 5, MOD = 1e18;

struct Solution
{
    Solution() {}
    void solveCase();
};

void Solution::solveCase()
{
    int n, k, x;
    cin >> n >> k >> x;
    set<pair<int, int>> neg, zero, pos;
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        if (x < 0)
            neg.insert({-x, i});
        else if (x == 0)
            zero.insert({x, i});
        else if (x > 0)
            pos.insert({x, i});
    }
    int currSign = 0;

    while (k)
    {
        if (zero.size())
            currSign = 0;
        if (neg.size() & 1)
            currSign = -1;
        else
            currSign = 1;
        db(zero, pos, neg, k);
        if (zero.size())
        {
            auto it = *zero.begin();
            zero.erase(it);

            if (zero.size())
                currSign = 0;
            if (neg.size() & 1)
                currSign = -1;
            else
                currSign = 1;

            if (currSign > 0)
                neg.insert({x, it.s});
            else
                pos.insert({x, it.s});
            --k;
        }
        else if (currSign == 1)
        {
            pair<int, int> it = {MOD, MOD};
            if (pos.size())
                it = *pos.begin();
            k--;
            if (neg.size())
            {
                if (*neg.begin() < it)
                {
                    it = *neg.begin();
                    neg.erase(neg.begin());

                    it.first -= x;
                    if (it.first == 0)
                        zero.insert(it);
                    else if (it.f > 0)
                        neg.insert(it);
                    else
                    {
                        it.f = -it.f;
                        pos.insert(it);
                    }
                }
                else
                {
                    pos.erase(it);
                    it.first -= x;
                    if (it.first == 0)
                        zero.insert(it);
                    else if (it.f > 0)
                        pos.insert(it);
                    else
                    {
                        it.f = -it.f;
                        neg.insert(it);
                    }
                }
            }
            else
            {
                pos.erase(it);
                it.first -= x;
                if (it.first == 0)
                    zero.insert(it);
                else if (it.f > 0)
                    pos.insert(it);
                else
                {
                    it.f = -it.f;
                    neg.insert(it);
                }
            }
        }
        else
        {
            k--;
            pair<int, int> it = {MOD, MOD};
            if (pos.size())
                it = *pos.begin();
            if (neg.size())
            {
                if (*neg.begin() < it)
                {
                    it = *neg.begin();
                    neg.erase(neg.begin());
                    it.f += x;
                    neg.insert(it);
                }
                else
                {
                    pos.erase(it);
                    it.f += x;
                    pos.insert(it);
                }
            }
            else
            {
                pos.erase(it);
                it.f += x;
                pos.insert(it);
            }
        }
    }
    db(zero, pos, neg, k);
    vector<pair<int, int>> vecc;
    for (auto &x : pos)
        vecc.pb({x.s, x.f});
    for (auto &x : neg)
        vecc.pb({x.s, -x.f});
    for (auto &x : zero)
        vecc.pb({x.s, x.f});
    sort(all(vecc));
    db(vecc);
    for (auto &x : vecc)
        cout << x.s << ' ';
    cout << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
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
