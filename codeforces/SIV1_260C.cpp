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
auto TimeStart = chrono::steady_clock::now();

const int nax = 3e5 + 10, mod = 1000000007;
vector<int> G[nax];
int par[nax], Size[nax], Diam[nax];
bool vis[nax];

int find(int u)
{
	if (u == par[u])
		return u;
	return par[u] = find(par[u]);
}

bool Union(int u, int v)
{
	u = find(u);
	v = find(v);
	if (u == v)
		return false;
	if (Size[u] < Size[v])
		swap(u, v);
	par[v] = u;
	Size[u] += Size[v];
	return true;
}

int maxDepth, Node;
void dfs(int node, int par, int depth)
{
	// db(node, par, depth);
	if (depth > maxDepth)
	{
		maxDepth = depth;
		Node = node;
	}
	for (auto child : G[node])
		if (child != par)
			dfs(child, node, depth + 1);
}

int diam(int node)
{
	maxDepth = -1;
	dfs(node, -1, 0);
	maxDepth = -1;
	dfs(Node, -1, 0);
	// db(node, maxDepth);
	return maxDepth;
}

int rad(int node)
{
	return (Diam[node] + 1) / 2;
}

void solve(int caseNo)
{
	int n, m, u, v, q;
	cin >> n >> m >> q;
	for (int i = 0; i <= n; ++i)
	{
		par[i] = i;
		Size[i] = 1;
	}
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v;
		G[u].pb(v);
		G[v].pb(u);
		Union(u, v);
	}
	for (int i = 1; i <= n; ++i)
	{
		// db(i);
		int u = find(i);
		// db(u, i);
		if (vis[u])
			continue;
		vis[u] = true;
		Diam[u] = diam(u);
	}
	int ch;
	while (q--)
	{
		cin >> ch;
		switch (ch)
		{
		case 1:
			cin >> u;
			cout << Diam[find(u)] << '\n';
			break;
		case 2:
			cin >> u >> v;
			u = find(u);
			v = find(v);
			if (Union(u, v))
			{
				Diam[find(u)] = max(Diam[u], max(Diam[v], rad(u) + rad(v) + 1));
				db(Diam[find(u)], find(u), find(v));
			}
		default:
			break;
		}
	}
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
	for (int i = 0; i < t; ++i)
		solve(i);
#ifdef WIN32
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}