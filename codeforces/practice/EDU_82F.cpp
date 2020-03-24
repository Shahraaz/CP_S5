// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define MULTI_TEST
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

const int NAX = 300043 + 5, MOD = 1000000007, K = 5;

ll x, y, z, n;
ll a[NAX];
using state = vector<vector<int>>;
map<state, int> d;
int cnt;
int p;
vector<vector<int>> state_log;

class Solution
{
private:
    int mex(const vector<int> &a)
    {
        for (size_t i = 0; i < a.size(); i++)
            if (count(all(a), i) == 0)
                return i;
        return a.size();
    }
    state go(state s)
    {
        int f1 = mex({s[0][K - x], s[1][K - y], s[2][K - z]});
        int f2 = mex({s[0][K - x], s[2][K - z]});
        int f3 = mex({s[0][K - x], s[1][K - y]});
        state nw = s;
        nw[0].pb(f1);
        nw[0].erase(nw[0].begin());
        nw[1].pb(f2);
        nw[1].erase(nw[1].begin());
        nw[2].pb(f3);
        nw[2].erase(nw[2].begin());
        return nw;
    }
    void precalc_my()
    {
        d.clear();
        state_log.clear();
        state cur(3, vector<int>(K, 0));
        db("precalc_start");
        cnt = 0;
        while (!d.count(cur))
        {
            db(cnt);
#ifdef LOCAL
            for (auto &e : cur)
                pc(e);
#else

#endif
            d[cur] = cnt;
            state_log.pb({cur[0].back(), cur[1].back(), cur[2].back()});
            cur = go(cur);
            cnt++;
        }
        db("precalc_end");
        p = cnt - d[cur];
    }
    int check(int x, int y)
    {
        return x == y;
    }
    int get_grundy(ll x, int t)
    {
        if (x < cnt)
            return state_log[x][t];
        // else
        int pp = cnt - p;
        x -= pp;
        return state_log[pp + (x % p)][t];
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> n >> x >> y >> z;
        db(n, x, y, z);
        for (size_t i = 0; i < n; i++)
            cin >> a[i];
        precalc_my();
        int ans = 0;
        for (size_t i = 0; i < n; i++)
            ans ^= get_grundy(a[i], 0);
        int res = 0;
        for (size_t i = 0; i < n; i++)
        {
            ans ^= get_grundy(a[i], 0);
            res += check(ans, get_grundy(max(0LL, a[i] - x), 0));
            res += check(ans, get_grundy(max(0LL, a[i] - y), 1));
            res += check(ans, get_grundy(max(0LL, a[i] - z), 2));
            ans ^= get_grundy(a[i], 0);
        }
        cout << res << '\n';
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