/*
Problem Name: Maximum Value
Problem Code: MXVAL
Problem Link: https://www.codechef.com/COFW2020/problems/MXVAL

Author Name: Shrey Kaushik
Author Link: https://www.codechef.com/users/shreyk5
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 1e9 + 7;

#define speedup_IO                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(0);                       \
    cout.tie(0)
#define forn(i, a, n) for (ll i = a; i < n; i++)
#define ford(i, n, a) for (ll i = n - 1; i >= a; i--)
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define pll pair<ll, ll>
#define all(a) (a).begin(), (a).end()
#define reset(a, x) memset(a, x, sizeof(a))

ll mypow(ll base, ll exp)
{
    ll res = 1;
    while (exp)
    {
        if (exp & 1)
            res = (res * base) % mod;
        exp >>= 1, base = (base * base) % mod;
    }
    return res;
}
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll mult(ll a, ll b)
{
    if (a < 0)
    {
        a += mod;
    }
    if (b < 0)
    {
        b += mod;
    }
    return ((a % mod) * (b % mod)) % mod;
}
ll add(ll a, ll b)
{
    if (a < 0)
    {
        a += mod;
    }
    if (b < 0)
    {
        b += mod;
    }
    return (a % mod + b % mod) % mod;
}
ll sub(ll a, ll b)
{
    if (a < 0)
    {
        a += mod;
    }
    if (b < 0)
    {
        b += mod;
    }
    return (a % mod + mod - b % mod) % mod;
}

const ll inf = 1e18;
const int nax = 1e5 + 5;

int main()
{
    speedup_IO;
    ll n;
    cin >> n;

    ll a;
    priority_queue<ll> Q;
    forn(i, 0, n)
    {
        cin >> a;
        Q.push(a);
    }

    ll ans = 0;

    while (Q.size() >= 2)
    {
        ll a = Q.top();
        Q.pop();
        ll b = Q.top();
        Q.pop();

        Q.push(a + b);
        ans += (a + b);
    }

    cout << ans;

    return 0;
}