// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define MULTI_TEST
#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#define pc(...)
#endif

#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
using ll = long long;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 2e5 + 5, MOD = 1000000007;

int ind[2][NAX];
int sum[2][NAX];

class Solution
{
private:
    vector<int> a;
    int _sum(int k, int a, int b)
    {
        return sum[k][b] - (a == 0 ? 0 : sum[k][a - 1]);
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        a.resize(n);
        for (auto &x : a)
        {
            cin >> x;
            --x;
        }
        for (size_t j = 0; j < 2; j++)
        {
            int cnt = 1;
            for (size_t i = 0; i < n; i++)
                if (a[i] == j)
                    ind[j][cnt++] = i;
            for (size_t i = cnt; i < NAX; i++)
                ind[j][i] = n;
            sum[j][0] = (a[0] == j) ? 1 : 0;
            for (size_t i = 1; i < n; i++)
            {
                if (a[i] == j)
                    sum[j][i] = sum[j][i - 1] + 1;
                else
                    sum[j][i] = sum[j][i - 1];
            }
        }
        vector<pair<int, int>> ans;
        for (size_t t = 1; t <= n; t++)
        {
            int ch[2] = {0, 0};
            int cnt[2] = {0, 0};
            int pos = 0, la = 0;
            bool ok = true;
            while (pos < n)
            {
                int ind0 = ind[0][cnt[0] + t];
                int ind1 = ind[1][cnt[1] + t];
                if (ind0 == ind1 && ind0 == n)
                {
                    ok = false;
                    break;
                }
                if (ind0 > ind1)
                {
                    la = 1;
                    ch[1]++;
                    cnt[1] += t;
                    cnt[0] += _sum(0, pos, ind1);
                }
                else
                {
                    la = 0;
                    ch[0]++;
                    cnt[0] += t;
                    cnt[1] += _sum(1, pos, ind0);
                }
                pos = min(ind0, ind1) + 1;
            }
            if (!ok)
                continue;
            int l_ans = max(ch[0], ch[1]);
            ch[la]--;
            if (l_ans != max(ch[0], ch[1]))
                ans.pb({l_ans, t});
        }
        sort(all(ans));
        cout << ans.size() << '\n';
        for (auto &x : ans)
            cout << x.f << ' ' << x.s << '\n';
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
#ifdef MULTI_TEST
    cin >> t;
#endif
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}