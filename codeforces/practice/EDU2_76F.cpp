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

const int AUX = 5e6 + 5, MOD = 1000000007;
const int NAX = 100, K = 15;

int n, t = 1;
ll a[NAX];
ll a1[NAX];
ll a2[NAX];
int lst[AUX];
map<int, int> nxt[AUX];

vector<int> get_diff(ll *arr, int x)
{
    // db("b");
    vector<int> cnt(n);
    for (size_t i = 0; i < n; i++)
        cnt[i] = __builtin_popcount(arr[i] ^ x);
    // db("c", n, n - 1);
    vector<int> diff(n - 1);
    for (size_t i = 0; i + 1 < n; i++)
        diff[i] = cnt[i + 1] - cnt[0];
    // db("d");
    return diff;
}

int get_nxt(int v, int x)
{
    if (!nxt[v].count(x))
        nxt[v][x] = t++;
    return nxt[v][x];
}

void add(vector<int> diff, int x)
{
    int v = 0;
    for (auto &i : diff)
        v = get_nxt(v, i);
    lst[v] = x;
}

int try_find(vector<int> diff)
{
    int v = 0;
    for (auto &i : diff)
    {
        if (!nxt[v].count(i))
            return -1;
        v = nxt[v][i];
    }
    return lst[v];
}

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        cin >> n;
        for (size_t i = 0; i < n; i++)
        {
            cin >> a[i];
            a1[i] = a[i] >> K;
            a2[i] = a[i] ^ (a1[i] << K);
        }
        // db("a");
        for (size_t i = 0; i < 1 << K; i++)
        {
            auto d = get_diff(a1, i);
            add(d, i);
        }
        // db("a");
        for (size_t i = 0; i < 1 << K; i++)
        {
            auto d = get_diff(a2, i);
            for (size_t j = 0; j + 1 < n; j++)
                d[j] *= -1;
            int x = try_find(d);
            if (x != -1)
            {
                ll res = (ll(x) << K) ^ i;
#ifdef LOCAL
                for (size_t i = 0; i < n; i++)
                {
                    cout << __builtin_popcount(a[i] ^ res) << ' ';
                }
                cout << '\n';
#else

#endif
                cout << res << '\n';
                return;
            }
        }
        cout << -1 << '\n';
    }
};

int32_t main()
{
    // db("Start");
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
