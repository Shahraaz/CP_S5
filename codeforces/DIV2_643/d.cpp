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

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int N, S;
        cin >> N >> S;
        vector<int> vec(N, 1);
        for (size_t i = 0; i + 1 < N; i++)
            S--;
        vec[N - 1] = S;
        set<int> ss;
        for (size_t i = 1; i < N; i++)
            ss.insert(i);
        int revSum = 0;
        for (int i = N - 1; i > 0; i--)
        {
            revSum += vec[i];
            ss.insert(revSum);
        }
        for (size_t i = 1; i < S; i++)
        {
            if (ss.count(i))
                continue;
            cout << "YES\n";
            for (auto &x : vec)
                cout << x << ' ';
            cout << '\n';
            cout << i << '\n';
            return;
        }
        cout << "NO\n";
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
