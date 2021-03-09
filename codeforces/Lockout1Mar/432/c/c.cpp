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

// Optimise
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int NAX_PRIME = 1e5 + 5;
bool is_composite[NAX_PRIME];
vector<int> primes;

void seive(int n = NAX_PRIME)
{
    fill(is_composite, is_composite + n, false);
    for (int i = 2; i < n; i++)
    {
        if (!is_composite[i])
            primes.push_back(i);
        for (size_t j = 0; j < primes.size() && ((ll)i * primes[j] < n); j++)
        {
            is_composite[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

void solveCase()
{
    seive();
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> rev_a(n);
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        --x;
        a[i] = x;
        rev_a[x] = i;
    }
    vector<pair<int, int>> res;
    auto split = [&](int x) -> int {
        while (is_composite[x])
            --x;
        return x;
    };
    auto do_swap = [&](int i, int j) {
        if (i == j)
            return;
        swap(rev_a[a[i]], rev_a[a[j]]);
        swap(a[i], a[j]);
        res.pb({i, j});
        db(i, j);
    };
    for (int i = 0; i < n; i++)
    {
        db(i, a);
        db(i, rev_a);
        while (rev_a[i] != i)
        {
            int j = rev_a[i];
            db(i, j);
            int diff = j - i + 1;
            int diff2 = split(diff);
            do_swap(j - diff2 + 1, j);
        }
    }
    cout << res.size() << '\n';
    for (auto &x : res)
        cout << x.first + 1 << ' ' << x.second + 1 << '\n';
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
        solveCase();
    return 0;
}