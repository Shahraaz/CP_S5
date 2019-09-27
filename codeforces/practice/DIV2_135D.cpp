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

vector<int> Adj[nax];
set<int> Forward[nax];
int Sol[nax], Sol2[nax];

void dfs(int node, int par)
{
	db(node, par);
	Sol[node] = 0;
	for (auto child : Adj[node])
		if (child != par)
		{
			dfs(child, node);
			Sol[node] += Sol[child];
			if (!Forward[node].count(child))
				Sol[node] += 1;
		}
	db(node, Sol[node]);
}

void dfs2(int node, int par)
{
	if (par > 0)
	{
		int A = Sol2[par];
		if (Forward[par].count(node))
			A++;
		else
			A--;
		Sol2[node] = A;
	}
	else
		Sol2[node] = Sol[node];
	for (auto child : Adj[node])
		if (child != par)
			dfs2(child, node);
	db(node, Sol2[node]);
}

void solve()
{
	int n, u, v;
	cin >> n;
	db("Here");
	for (int i = 1; i < n; ++i)
	{
		cin >> u >> v;
		Adj[u].pb(v);
		Adj[v].pb(u);
		Forward[u].insert(v);
	}
	db("Here");
	dfs(1, 0);
	db("Here");
	dfs2(1, 0);
	int ret = INT_MAX;
	for (int i = 1; i <= n; ++i)
		ret = min(ret, Sol2[i]);
	cout << ret << '\n';
	for (int i = 1; i <= n; ++i)
		if (Sol2[i] == ret)
			cout << i << ' ';
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