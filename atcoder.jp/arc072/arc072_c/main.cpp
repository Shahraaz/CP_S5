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

const string YES = "YES";
const string NO = "NO";
auto solveCase(int N, int64_t D, const vector<int64_t> & d, int Q, const vector<int64_t> & q) {
    // TODO: edit here
}

// generated by oj-template v4.7.2 (https://github.com/online-judge-tools/template-generator)
int main() 
{
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    constexpr char endl = '\n';
    int64_t N;
    int D;
    int Q;
    cin >> N;
    vector<int64_t> d(N);
    cin >> D;
    for (int i = 0; i < N; ++i) {
        cin >> d[i];
    }
    cin >> Q;
    vector<int64_t> q(Q);
    for (int i = 0; i < Q; ++i) {
        cin >> q[i];
    }
    auto ans = solveCase(N, D, d, Q, q);
    for (int i = 0; i < Q; ++i) {
        cout << a[i] << endl;
    }
    return 0;
}