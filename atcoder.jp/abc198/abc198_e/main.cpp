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

auto solveCase(int N, const vector<int64_t> &C, const vector<int64_t> &A, const vector<int64_t> &B)
{
    // TODO: edit here
    vector<vector<int>> adj(N);
    for (size_t i = 0; i < A.size(); i++)
    {
        adj[A[i] - 1].pb(B[i] - 1);
        adj[B[i] - 1].pb(A[i] - 1);
    }

    vector<int> cnt(NAX);
    for (auto &x : C)
        cnt[x]++;

    set<pair<int, int>> seen;
    vector<int> ret;
    function<void(int, int)> dfs = [&](int node, int par) -> void {
        auto it = seen.lower_bound({C[node], 0});
        if (it == seen.end() || it->first != C[node])
            ret.pb(node + 1);
        seen.insert({C[node], node});
        for (auto &x : adj[node])
        {
            if (x == par)
                continue;
            dfs(x, node);
        }
        seen.erase({C[node], node});
    };
    dfs(0, 0);
    sort(all(ret));
    return ret;
}

// generated by oj-template v4.7.2 (https://github.com/online-judge-tools/template-generator)
int main()
{
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    constexpr char endl = '\n';
    int N;
    cin >> N;
    vector<int64_t> C(N), A(N - 1), B(N - 1);
    for (int i = 0; i < N; ++i)
    {
        cin >> C[i];
    }
    for (int i = 0; i < N - 1; ++i)
    {
        cin >> A[i] >> B[i];
    }
    auto ans = solveCase(N, C, A, B);
    // failed to analyze output format
    // TODO: edit here
    for (auto &x : ans)
    {
        cout << x << '\n';
    }

    return 0;
}