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

const int nax = 1e3 + 10;
vector<int> a[5], Adj[nax];
int pos[nax][nax], dp[nax];
bool vis[nax];
int ans = 0;

int dfs(int node)
{
	if (vis[node])
		return dp[node];
	vis[node] = true;
	dp[node] = 1;
	for (auto child : Adj[node])
		dp[node] = max(dp[node], 1 + dfs(child));
	ans = max(ans, dp[node]);
	return dp[node];
}

void solve()
{
	int n, k;
	cin >> n >> k;
	for (int j = 0; j < k; ++j)
	{
		a[j].resize(n + 1);
		for (int i = 1; i <= n; ++i)
		{
			cin >> a[j][i];
			pos[j][a[j][i]] = i;
		}
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
		{
			if (i == j)
				continue;
			bool ok = true;
			for (int K = 0; K < k; ++K)
				if (pos[K][i] >= pos[K][j])
					ok = false;
			if (ok)
				Adj[i].pb(j);
		}
	int ret = 0;
	for (int i = 1; i <= n; ++i)
		ret = max(ret, dfs(i));
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