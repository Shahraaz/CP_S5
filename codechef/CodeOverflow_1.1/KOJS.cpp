/*
Problem Name: Khojo 
Problem Code: KOJS
Problem Link: https://www.codechef.com/COFW2020/problems/KOJS

Author Name: Shubham Mittal
Author Link: https://www.codechef.com/users/shubhammittal2
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
const int nax = 2e5 + 5;

ll fact[nax], invfact[nax];

void pre()
{
    fact[0] = 1;
    forn(i, 1, nax)
    {
        fact[i] = mult(fact[i - 1], i);
    }

    invfact[nax - 1] = mypow(fact[nax - 1], mod - 2);

    ford(i, nax, 1)
    {
        invfact[i - 1] = mult(invfact[i], i);
    }
}

ll ncr(ll n, ll r)
{
    if (r > n || n < 0)
        return 0;

    ll ans = mult(fact[n], mult(invfact[n - r], invfact[r]));

    return ans;
}

int main()
{
    speedup_IO;
    ll q;
    cin >> q;

    set<ll> S;

    forn(i, 0, q)
    {
        ll t, n;
        cin >> t >> n;

        if (t == 1)
        {
            S.insert(n);
        }
        else if (t == 2)
        {
            if (S.find(n) == S.end())
            {
                cout << "No" << endl;
            }
            else
            {
                cout << "Yes" << endl;
            }
        }
        else
        {
            if (S.ub(n) == S.end())
            {
                cout << "-1" << endl;
            }
            else
            {
                cout << *S.ub(n) << endl;
            }
        }
    }
    return 0;
}