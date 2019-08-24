//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
#ifdef WIN32
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__);
#define pc(...) PC(#__VA_ARGS__, __VA_ARGS__);
template <typename T, typename U>
ostream &operator<<(ostream &out, const pair<T, U> &p)
{
	out << '[' << p.first << ", " << p.second << ']';
	return out;
}
template <typename Arg>
void PC(const char *name, Arg &&arg)
{
	std::cerr << name << " { ";
	for (const auto &v : arg)
		cerr << v << ' ';
	cerr << " }\n";
}
template <typename Arg1>
void ZZ(const char *name, Arg1 &&arg1)
{
	std::cerr << name << " = " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void ZZ(const char *names, Arg1 &&arg1, Args &&... args)
{
	const char *comma = strchr(names + 1, ',');
	std::cerr.write(names, comma - names) << " = " << arg1;
	ZZ(comma, args...);
}
#else
#define db(...)
#define pc(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
const long long mod = 1000000007;
auto TimeStart = chrono::steady_clock::now();

const int nax = 5e5 + 10;
int n, a, b, k;

ll add(ll a, ll b)
{
	a += b;
	if (a >= mod)
		a -= mod;
	return a;
}

ll sub(ll a, ll b)
{
	a -= b;
	if (a < 0)
		a += mod;
	return a;
}

void solve()
{
	cin >> n >> a >> b >> k;
	vector<vector<ll>> Dp(2, vector<ll>(n + 10));
	bool turn = false;
	Dp[0][a] = 1;
	while (k--)
	{
		bool next = !turn;
		fill(Dp[next].begin(), Dp[next].end(), 0);
		for (int i = 1; i <= n; ++i)
			if (i != b)
				if (Dp[turn][i])
				{
					int d = abs(i - b);
					int start = max(1, i + 1);
					int end = min(n, i + d - 1);
					Dp[next][start] = add(Dp[next][start], Dp[turn][i]);
					Dp[next][end + 1] = sub(Dp[next][end + 1], Dp[turn][i]);
					start = max(1, i - d + 1);
					end = min(n, i - 1);
					Dp[next][start] = add(Dp[next][start], Dp[turn][i]);
					Dp[next][end + 1] = sub(Dp[next][end + 1], Dp[turn][i]);
				}
		for (int i = 1; i <= n; ++i)
		{
			Dp[next][i] = add(Dp[next][i], Dp[next][i - 1]);
		}
		turn = next;
	}
	ll ans = 0;
	for (int i = 1; i <= n; ++i)
		ans = add(Dp[turn][i], ans);
	cout << ans;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (t--)
		solve();
#ifdef WIN32
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}