#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define deb(x) cout << #x << " " << x << "\n";
#define MAX 9223372036854775807
#define MIN -9223372036854775807
#define setbits(n) __builtin_popcountll(n)
#define mkunique(a)           \
    sort(a.begin(), a.end()); \
    a.resize(unique(a.begin(), a.end()) - a.begin());
#define print(s)          \
    for (ll u : s)        \
        cout << u << " "; \
    cout << "\n";
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const ll mod = 1e9 + 7;

#include "/debug.h"

const int N = 21;
ll w;
vector<ll> a(4);
ll n, m;
vector<vector<ll>> g(N, vector<ll>(N));
ll dp[N][N][N][N];

ll sum(ll x, ll y, ll tx, ll ty)
{
    ll ans = g[tx][ty];
    db(x, y, tx, ty);
    if (x != 0)
        ans -= g[x - 1][ty];
    if (y != 0)
        ans -= g[tx][y - 1];
    if (x != 0 && y != 0)
        ans += g[x - 1][y - 1];
    db(ans);
    return ans;
}

ll go(ll x, ll y, ll tx, ll ty)
{
    if (x == tx && y == ty)
        return a[sum(x, y, tx, ty)];
    if (dp[x][y][tx][ty] != -1)
        return dp[x][y][tx][ty];
    ll ans = mod * mod, lenx = tx - x + 1, leny = ty - y + 1;
    if (sum(x, y, tx, ty) < 4)
        ans = a[sum(x, y, tx, ty)];
    for (ll i = x; i < tx; i++)
        ans = min(ans, w * leny + go(x, y, i, ty) + go(x + 1, y, tx, ty));
    for (ll i = y; i < ty; i++)
        ans = min(ans, w * lenx + go(x, y, tx, i) + go(x, y + 1, tx, ty));
    return dp[x][y][tx][ty] = ans;
}

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll TT = clock();

    cin >> a[0] >> a[1] >> a[2] >> a[3] >> w;
    cin >> n >> m;
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
            cin >> g[i][j];
    }
    for (ll i = 1; i < n; i++)
        g[i][0] += g[i - 1][0];
    for (ll i = 1; i < m; i++)
        g[0][i] += g[0][i - 1];
    for (ll i = 1; i < n; i++)
    {
        for (ll j = 1; j < m; j++)
        {
            g[i][j] += g[i - 1][j] + g[i][j - 1] - g[i - 1][j - 1];
        }
    }
    memset(dp, -1, sizeof(dp));
    cout << go(0, 0, n, m);

    cerr << "\n\nTIME: " << (long double)(clock() - TT) / CLOCKS_PER_SEC << " sec\n";
    TT = clock();
    return 0;
}