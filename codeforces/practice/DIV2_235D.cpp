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

const int nax = 2e5 + 10;
string n;
int m;
ll dp[1 << 18][100];

void solve()
{
	cin >> n >> m;
	int l = n.length();
	dp[0][0] = 1;
	for (int mask = 0; mask < (1 << l); ++mask)
		for (int rem = 0; rem < 100; ++rem)
		{
			if (dp[mask][rem] == 0)
				continue;
			vector<bool> vis(10);
			for (int i = 0; i < l; ++i)
			{
				if (mask & (1 << i))
					continue;
				if (mask == 0 && n[i] == '0')
					continue;
				if (vis[n[i] - '0'])
					continue;
				vis[n[i] - '0'] = true;
				int newMask = mask | (1 << i);
				int newRem = (rem * 10 + n[i] - '0') % m;
				dp[newMask][newRem] += dp[mask][rem];
			}
		}
	cout << dp[(1 << l) - 1][0] << '\n';
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
	flush(cout);
#endif
	return 0;
}