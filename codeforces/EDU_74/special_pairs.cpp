//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
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
	while (*name == ',' || *name == ' ')
		name++;
	std::cerr << name << " { ";
	for (const auto &v : arg)
		cerr << v << ' ';
	cerr << " }\n";
}
template <typename Arg1, typename... Args>
void PC(const char *names, Arg1 &&arg1, Args &&... args)
{
	while (*names == ',' || *names == ' ')
		names++;
	const char *comma = strchr(names, ',');
	std::cerr.write(names, comma - names) << " { ";
	for (const auto &v : arg1)
		cerr << v << ' ';
	cerr << " }\n";
	PC(comma, args...);
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

const int nax = 1e5 + 10, LOG = 22;
ll a[nax];
ll dp[1048576 + 5][22];
int freq[1048576 + 5];
int d[1000000 + 5];

void solve()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		// db(freq[a[i]], a[i]);
		cin >> a[i];
		freq[a[i]]++;
	}
	ll ans = 0;
	memset(dp, 0, sizeof(dp));
	for (int mask = 0; mask < (1 << 20); ++mask)
	{
		dp[mask][0] = freq[mask];
		if (mask & 1)
			dp[mask][0] += freq[mask ^ 1];
		for (int p = 1; p <= 20; ++p)
		{
			dp[mask][p] += dp[mask][p - 1];
			if (mask & (1 << p))
				dp[mask][p] += dp[mask ^ (1 << p)][p - 1];
		}
	}
	for (int i = 0; i < n; ++i)
	{
		ans += dp[(1 << 20) - 1 - a[i]][20];
		freq[a[i]] = 0;
	}
	cout << ans << '\n';
}

int main()
{
#ifndef WIN32
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#endif
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