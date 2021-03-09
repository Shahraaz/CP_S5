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

int64_t solveCase(int N, const vector<int64_t> &A, const vector<int64_t> &B)
{
    // TODO: edit here
    int64_t ret = LLONG_MAX;
    for (size_t i = 0; i < N; i++)
    {
        ret = min(ret, A[i] + B[i]);
        for (size_t j = 0; j < N; j++)
            if (i != j)
                ret = min(ret, max(A[i], B[j]));
    }
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
    vector<int64_t> A(N), B(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> A[i] >> B[i];
    }
    auto ans = solveCase(N, A, B);
    cout << ans << endl;
    return 0;
}