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

string solveCase(int N, string S, int Q, const vector<int64_t> &T, const vector<int64_t> &A, const vector<int64_t> &B)
{
    // TODO: edit here
    bool f = false;
    int n = N ;
    for (size_t i = 0; i < T.size(); i++)
    {
        if (T[i] == 1)
        {
            int a = A[i] - 1;
            int b = B[i] - 1;
            if (f)
            {
                if (a >= n)
                    a -= n;
                else
                    a += n;

                if (b >= n)
                    b -= n;
                else
                    b += n;
            }
            swap(S[a], S[b]);
            db(a, b, S);
        }
        else
            f = !f;
        db(S, f);
    }
    auto ret = S;
    if (f)
        for (size_t i = 0; i < n; i++)
        {
            db(i, ret[i], ret[i + n]);
            swap(ret[i], ret[i + n]);
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
    string S;
    int Q;
    cin >> N >> S >> Q;
    vector<int64_t> T(Q), A(Q), B(Q);
    for (int i = 0; i < Q; ++i)
    {
        cin >> T[i] >> A[i] >> B[i];
    }
    auto ans = solveCase(N, S, Q, T, A, B);
    cout << ans << endl;
    return 0;
}