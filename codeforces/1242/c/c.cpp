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

const int K = 16, N = 5001;
int n_array[K];
ll a[K][N], sum[K], totalsum;
int pos_mask[K][N];
map<ll, int> aij_i;
int k;

int dp[1 << K];
int c[K];

bool solve(int mask)
{
    if (__builtin_popcount(mask) == k)
    {
        // cout << "Yes\n";
        return true;
    }
    auto &ret = dp[mask];
    db(mask, ret);
    if (ret != -1)
        return ret;
    ret = 0;
    int firstunset = -1;
    for (size_t i = 0; i < k; i++)
        if (mask & (1 << i))
            ;
        else
        {
            firstunset = i;
            break;
        }
    assert(firstunset != -1);
    db(mask, firstunset);
    for (size_t j = 0; j < n_array[firstunset]; j++)
        if (pos_mask[firstunset][j] != 0 && (mask & pos_mask[firstunset][j]) == 0)
            if (solve(mask | (pos_mask[firstunset][j])))
            {
                bool ok = true;
                int i = firstunset;
                ll curr = totalsum - sum[i] + a[i][j];
                mask = 1 << firstunset;
                c[i] = a[i][j];
                if (curr != a[firstunset][j])
                    while (true)
                    {
                        auto it = aij_i.find(curr);
                        if (it == aij_i.end())
                        {
                            ok = false;
                            break;
                        }
                        int nextidx = it->second;
                        c[nextidx] = curr;
                        ll nextnum = totalsum - sum[nextidx] + curr;
                        db(i, j, curr, nextidx, nextnum, a[i][j], bitset<5>(mask));
                        if (mask & (1 << nextidx))
                        {
                            if (nextidx != i)
                                ok = false;
                            else if (curr != a[i][j])
                                ok = false;
                            break;
                        }
                        mask |= (1 << nextidx);
                        curr = nextnum;
                    }
                assert(ok);
                ret = true;
                break;
            }
    db(bitset<5>(mask), ret);
    return ret;
}

void solveCase()
{
    memset(dp, -1, sizeof dp);
    cin >> k;
    for (size_t i = 0; i < k; i++)
    {
        cin >> n_array[i];
        for (size_t j = 0; j < n_array[i]; j++)
        {
            cin >> a[i][j];
            aij_i[a[i][j]] = i;
            sum[i] += a[i][j];
        }
        totalsum += sum[i];
        db(i, sum[i], totalsum);
    }
    if (totalsum % k)
    {
        cout << "No\n";
        return;
    }
    totalsum /= k;
    db(totalsum);
    for (size_t i = 0; i < k; i++)
    {
        for (size_t j = 0; j < n_array[i]; j++)
        {
            int mask = 0;
            ll curr = totalsum - sum[i] + a[i][j];
            bool ok = true;
            mask = 1 << i;
            if (curr != a[i][j])
                while (true)
                {
                    auto it = aij_i.find(curr);
                    if (it == aij_i.end())
                    {
                        ok = false;
                        break;
                    }
                    int nextidx = it->second;
                    ll nextnum = totalsum - sum[nextidx] + curr;
                    db(i, j, curr, nextidx, nextnum, a[i][j], bitset<5>(mask));
                    if (mask & (1 << nextidx))
                    {
                        if (nextidx != i)
                            ok = false;
                        else if (curr != a[i][j])
                            ok = false;
                        break;
                    }
                    mask |= (1 << nextidx);
                    curr = nextnum;
                }
            if (ok)
            {
                db(i, j, a[i][j], bitset<5>(mask));
                pos_mask[i][j] = mask;
            }
        }
    }
    if (!solve(0))
    {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    vector<int> p(k);
    for (size_t i = 0; i < k; i++)
    {
        ll i_needs = totalsum - sum[i] + c[i];
        p[aij_i[i_needs]] = i;
    }
    for (size_t i = 0; i < k; i++)
        cout << c[i] << ' ' << p[i] + 1 << '\n';
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