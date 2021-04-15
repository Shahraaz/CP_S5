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

const int NAX_PRIME = 2e5 + 5;
bool is_composite[NAX_PRIME];
vector<int> primes;

vector<vector<int>> primes_list(11);

bool is_prime(int x)
{
    for (long long i = 2; i * i <= x; i++)
    {
        if (x % i == 0)
            return false;
    }
    return true;
}

void seive(int n = NAX_PRIME)
{
    primes_list[0] = {1, 1};
    for (int i = 1; i < 10; i++)
    {
        int c = i - 1, x = 1;
        while (c--)
            x = x * 10;
        while (primes_list[i].size() < 2)
        {
            if (is_prime(x))
                primes_list[i].pb(x);
            ++x;
        }
        db(i, primes_list[i]);
    }
}

void solveCase()
{
    int a, b, c;
    cin >> a >> b >> c;
    int base = 1, l = c - 1;
    db(a, b, c);
    while (l--)
        base = base * 10;
    db(base);
    db(a - c, b - c);
    if (a == b)
    {
        cout << primes_list[a - c + 1][0] * base << ' ';
        cout << primes_list[b - c + 1][1] * base << '\n';
    }
    else
    {
        cout << primes_list[a - c + 1][0] * base << ' ';
        cout << primes_list[b - c + 1][1] * base << '\n';
    }
}

int32_t main()
{
    seive();
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}