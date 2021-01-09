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
    int n, m;
    cin >> n >> m;
    map<deque<int>, int> mp;
    vector<int> ind(m);
    vector<deque<int>> aux(m);
    for (size_t i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        deque<int> vecc(k);
        for (auto &x : vecc)
        {
            cin >> x;
            --x;
            aux[x].pb(i);
        }
        if (k == 1)
            ind[vecc[0]] = 1;
        else
        {
            if (vecc.size() && ind[vecc.front()])
                vecc.pop_front();
            if (vecc.size() && ind[vecc.back()])
                vecc.pop_back();
            if (vecc.size())
            {
                auto it = mp.find(vecc);
                if (it == mp.end())
                    mp[vecc] = i;
            }
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
        solveCase();
    return 0;
}