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

int64_t solveCase(int N, const vector<int64_t>& h, const vector<int64_t>& u, const vector<int64_t>& v, int K, const vector<int64_t>& s, const vector<int64_t>& t) {
    // TODO: edit here
}

// generated by oj-template v4.7.2 (https://github.com/online-judge-tools/template-generator)
int main() {
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    constexpr char endl = '\n';
    int N, K;
    cin >> N;
    vector<int64_t> h(N), u(N - 1), v(N - 1);
    for (int i = 0; i < N; ++i) {
        cin >> h[i];
    }
    for (int i = 0; i < N - 1; ++i) {
        cin >> u[i] >> v[i];
    }
    cin >> K;
    vector<int64_t> s(K), t(K);
    for (int i = 0; i < K; ++i) {
        cin >> s[i] >> t[i];
    }
    auto ans = solveCase(N, h, u, v, K, s, t);
    cout << ans << endl;
    return 0;
}