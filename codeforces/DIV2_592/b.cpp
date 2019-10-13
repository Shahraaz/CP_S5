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

const int nax = 1e3 + 10;

vector<int> Adj[nax];
bool vis[nax];

int dfs(int node)
{
	int ret = 0;
	vis[node] = true;
	for (auto c : Adj[node])
		if (!vis[c])
			ret = max(ret, dfs(c));
	vis[node] = false;
	++ret;
	// db(node, ret);
	return ret;
}

void solve()
{
	int n;
	char x;
	cin >> n;
	// for (int i = 0; i < 2 * n; ++i)
	// {
	// 	vis[i] = false;
	// 	Adj[i].clear();
	// 	Adj[i + n].clear();
	// }
	vector<int> X(n);
	vector<int> Ones, twos;
	for (int i = 0; i < n; ++i)
	{
		// if (i != n - 1)
		// {
		// 	Adj[i].pb(i + 1);
		// 	Adj[i + n].pb(i + 1 + n);
		// }
		// if (i != 0)
		// {
		// 	Adj[i].pb(i - 1);
		// 	Adj[i + n].pb(i - 1 + n);
		// }
		cin >> x;
		// db(x);
		X[i] = x - '0';
		if (x == '1')
		{
			twos.pb(n - i);
			Ones.pb(i);
			// Adj[i].pb(i + n);
			// Adj[i + n].pb(i);
		}
	}
	// for (int i = 0; i < n; ++i)
	// {
	// 	cerr << i << ' ' << i + n - 1 << '\n';
	// 	pc(Adj[i], Adj[i + n - 1]);
	// }
	int res = n;
	// res = max(res, dfs(n));
	// res = max(res, dfs(n - 1));
	// res = max(res, dfs(2 * n - 1));
	// // for (int i = 0; i < 2 * n; ++i)
	// // res = max(res, dfs(i));
	int cnt = 0;
	for (int i = 0; i < n; ++i)
	{
		int temp = cnt++;
		if (X[i])
		{
			cnt++;
			res = max(res, 2 * (i + 1));
			int last = Ones.back();
			if (last != i)
			{
				temp += 2 * (last - i + 1);
				res = max(res, temp);
			}
			// else
			{
				res = max(res, n + 1);
			}
		}
		// else
		// {
		// 	continue;
		// }
	}
	reverse(X.begin(), X.end());
	cnt = 0;
	for (int i = 0; i < n; ++i)
	{
		int temp = cnt++;
		if (X[i])
		{
			cnt++;
			res = max(res, 2 * (i + 1));
			int last = twos.back();
			if (last != i)
			{
				temp += 2 * (last - i + 1);
				res = max(res, temp);
			}
			// else
			{
				res = max(res, n + 1);
			}
		}
		// else
		// {
		// 	continue;
		// }
	}
	cout << res << '\n';
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