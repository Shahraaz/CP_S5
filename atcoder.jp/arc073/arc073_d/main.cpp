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
constexpr char endl = '\n';
const int NAX = 2e5 + 5, MOD = 1000000007;


int64_t solveCase(int64_t N, int Q, int64_t A, int64_t B, const vector<int64_t> & x) {
    // TODO: edit here
}

// generated by oj-template v4.7.2 (https://github.com/online-judge-tools/template-generator)
int main() 
{
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    int N;
    int64_t Q;
    int64_t A, B;
    cin >> N >> Q;
    vector<int64_t> x(Q);
    cin >> A >> B;
    for (int i = 0; i < Q; ++i) {
        cin >> x[i];
    }
    auto ans = solveCase(N, Q, A, B, x);
    cout << ans << endl;
    return 0;
}