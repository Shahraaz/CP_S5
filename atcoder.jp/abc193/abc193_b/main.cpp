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

int64_t solveCase(int N, const vector<int64_t> &A, const vector<int64_t> &P, const vector<int64_t> &X)
{
    // TODO: edit here
    int64_t ret = LLONG_MAX;
    for (size_t i = 0; i < N; i++)
    {
        if (X[i] - A[i] > 0)
            ret = min(ret, P[i]);
    }
    if (ret == LLONG_MAX)
        ret = -1;
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
    vector<int64_t> A(N), P(N), X(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> A[i] >> P[i] >> X[i];
    }
    auto ans = solveCase(N, A, P, X);
    cout << ans << endl;
    return 0;
}