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

int64_t solveCase(int N, const vector<int64_t> &X)
{
    // TODO: edit here
    vector<int> vecc(51);
    for (auto &x : X)
        vecc[x] = 1;
    for (int i = 51 - 1; i >= 2; i--)
    {
        while (true)
        {
            __int128_t g2 = g;
            for (size_t i = 2; i < 50; i++)
                if (vecc[i] && g2 % i == 0)
                    g2 /= i;
            if (g2 != 1)
                break;
            auto vecc2 = vecc;
            for (size_t i = 2; i < 50; i++)
                if (vecc[i] && g2 % i == 0)
                {
                    vecc2[i] = 0;
                    g2 /= i;
                }
            bool ok = true;
            for (auto &x : X)
            {
                int cnt = 0;
                for (size_t i = 2; i < 50; i++)
                {
                    if(vecc[i])
                }
            }
            
        }
    }
    return g;
}

// generated by oj-template v4.7.2 (https://github.com/online-judge-tools/template-generator)
int main()
{
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    constexpr char endl = '\n';
    int N = 50;
    // cin >> N;
    vector<int64_t> X(N);
    for (int i = 0; i < N; ++i)
    {
        X[i] = i + 1;
        // cin >> X[i];
    }
    auto ans = solveCase(N, X);
    cout << ans << endl;
    return 0;
}