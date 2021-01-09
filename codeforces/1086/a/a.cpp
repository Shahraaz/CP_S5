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
    vector<pair<int, int>> A(3);
    for (auto &x : A)
        cin >> x.first >> x.second;
    int res = MOD;
    set<pair<int, int>> path;
    auto get_path = [](pair<int, int> src, pair<int, int> dest, int dir) -> set<pair<int, int>> {
        set<pair<int, int>> path;
        path.insert(src);
        path.insert(dest);
        if (dir == 0)
        {
            while (src.first != dest.first)
            {
                if (src.first < dest.first)
                    src.first++;
                else
                    src.first--;
                path.insert(src);
            }
            while (src.second != dest.second)
            {
                if (src.second < dest.second)
                    src.second++;
                else
                    src.second--;
                path.insert(src);
            }
        }
        else
        {
            while (src.second != dest.second)
            {
                if (src.second < dest.second)
                    src.second++;
                else
                    src.second--;
                path.insert(src);
            }
            while (src.first != dest.first)
            {
                if (src.first < dest.first)
                    src.first++;
                else
                    src.first--;
                path.insert(src);
            }
        }
        return path;
    };
    for (size_t i = 0; i < 3; i++)
    {
        int next = -1, nnext = -1;
        for (size_t j = 0; j < 3; j++)
            if (j != i)
                next = j;
        for (size_t j = 0; j < 3; j++)
            if (j != next && j != i)
                nnext = j;
        for (int d1 = 0; d1 < 2; d1++)
        {
            auto path1 = get_path(A[i], A[next], d1);
            for (int d2 = 0; d2 < 2; d2++)
            {
                auto path2 = get_path(A[i], A[nnext], d2);
                set<pair<int, int>> ret = path1;
                for (auto &x : path2)
                    ret.insert(x);
                if (res > ret.size())
                {
                    res = ret.size();
                    path = ret;
                }
            }
        }
    }
    cout << res << '\n';
    for (auto &x : path)
        cout << x.first << ' ' << x.second << '\n';
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