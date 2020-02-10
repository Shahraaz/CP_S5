#define ll long long
inline ll add(ll a, ll b, ll m) { return (((a % m + b % m) % m + m) % m); }
inline ll mul(ll a, ll b, ll m) { return (((a % m * b % m) % m + m) % m); }
const ll MOD = 1e9 + 7;

const int N = 3e5 + 5;
ll fact[N], ifact[N], inv[N];

void pre()
{
    inv[1] = fact[0] = fact[1] = ifact[0] = ifact[1] = 1;
    for (ll i = 2; i < N; i++)
    {
        inv[i] = mul(MOD - MOD / i, inv[MOD % i], MOD);
        fact[i] = mul(i, fact[i - 1], MOD);
        ifact[i] = mul(inv[i], ifact[i - 1], MOD);
    }
    return;
}

ll nCr(ll n, ll r)
{
    if (n < 0 || n < r)
        return 0;
    return mul(fact[n], mul(ifact[r], ifact[n - r], MOD), MOD);
}
