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

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        vector<int> B, R, P;
        // ll res = 0;
        vector<pair<int, ll>> adj[n];
        set<pair<int, int>> dispute;
        for (size_t i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            char c;
            cin >> c;
            if (c == 'B')
                B.pb(x);
            else if (c == 'R')
                R.pb(x);
            else
            {
                dispute.insert({x, P.size()});
                R.pb(x);
                B.pb(x);
                P.pb(x);
            }
        }
        ll res = 0;
        if (R.size())
        {
            vector<int> isConn(P.size());
            res = R.back() - R.front();
            auto checkIdx = [&](int x) {
                auto it = dispute.lower_bound({x, -1});
                if (it != dispute.end())
                    if (it->f == x)
                        return it->s;
                return -1;
            };
            for (size_t i = 0; i + 1 < R.size(); i++)
            {
                int x = R[i];
                int idx = checkIdx(x);
                if (idx != -1)
                    if (idx + 1 < P.size())
                    {
                        int idx2 = checkIdx(R[i + 1]);
                        if (idx2 != -1)
                            isConn[idx] = true;
                    }
                db(x, idx);
            }
            pc(P);
            pc(isConn);
            ll excess = 0, cntB, cntP;
            cntB = cntP = 0;
            for (size_t i = 0; i + 1 < B.size(); i++)
            {
                int x = B[i];
                int idx = checkIdx(x);
                if (idx == -1)
                {
                    int idx2 = checkIdx(B[i + 1]);
                    if (idx2 == -1)
                    {
                        excess += B[i + 1] - B[i];
                    }
                    else
                    {
                        excess += B[i + 1] - B[i];
                    }
                }
                else
                {
                    if (isConn[idx])
                    {
                        int j = i + 1;
                        while (j < B.size() && B[j] < P[idx + 1])
                        {
                            ++j;
                        }
                        i = j - 1;
                    }
                    else
                    {
                        excess += B[i + 1] - B[i];
                    }
                }
                db(x, idx);
            }
            cout << res + excess << '\n';
            return;
        }
        else
        {
            res = B.back() - B.front();
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