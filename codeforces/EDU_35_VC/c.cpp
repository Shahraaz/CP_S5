// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    vector<int> k(3);
    for (auto &x : k)
        cin >> x;
    auto rangeDivisors = [](int l, int r, int val) -> int {
        return r / val - (l - 1) / val;
    };
    vector<int> cnt(k[0]);
    for (size_t i = 0; i < k[0]; i++)
    {
        cnt[0] = 1;
        int empty = k[0] - 1;
        for (size_t j = i; j < k[0]; j += k[1])
        {
            if (cnt[j] == 0)
                empty--;
            cnt[j]++;
        }
        for (size_t j = 0; j < k[0]; j++)
        {
            for (size_t l = j; l < k[0]; l += k[2])
            {
                cnt[l]++;
                if (cnt[l] == 1)
                    empty--;
            }
            if (empty == 0)
            {
                db(i, j);
                cout << "YES\n";
                return;
            }
            for (size_t l = j; l < k[0]; l += k[2])
            {
                if (cnt[l] == 1)
                    empty++;
                cnt[l]--;
            }
        }
        for (size_t j = i; j < k[0]; j += k[1])
        {
            cnt[j]--;
        }
    }
    cout << "NO\n";
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
