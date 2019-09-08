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

const int nax = 1e5 + 10, Log = 20;
set<int> G[nax];
int Level[nax], dp[20][nax];
int n, m, u, v;

void dfs(int Node, int parent, int level)
{
	dp[0][Node] = parent;
	Level[Node] = level;
	for (auto child : G[Node])
		if (child != parent)
			dfs(child, Node, level + 1);
}

void constructLca()
{
	Level[0] = 0;
	dp[0][0] = 0;
	dfs(0, 0, 0);
	for (int i = 1; i < Log; ++i)
		for (int j = 0; j < n; ++j)
			dp[i][j] = dp[i - 1][dp[i - 1][j]];
}

int lca(int a, int b)
{
	if (Level[a] > Level[b])
		swap(a, b);
	int d = Level[b] - Level[a];
	for (int i = 0; i < Log; ++i)
		if (d & (1 << i))
			b = dp[i][b];
	if (a == b)
		return a;
	for (int i = Log; i >= 0; --i)
		if (dp[i][a] != dp[i][b])
		{
			a = dp[i][a];
			b = dp[i][b];
		}
	return dp[0][a];
}

int dist(int a, int b)
{
	return Level[a] + Level[b] - 2 * Level[lca(a, b)];
}

int subTreeSize[nax], parentInCentroid[nax], currentTreeSize;
void dfs1(int node, int parent)
{
	currentTreeSize++;
	subTreeSize[node] = 1;
	for (auto child : G[node])
		if (child != parent)
		{
			dfs1(child, node);
			subTreeSize[node] += subTreeSize[child];
		}
}

int getCentroid(int node, int parent)
{
	for (auto child : G[node])
		if (child != parent)
			if (subTreeSize[child] > currentTreeSize / 2)
				return getCentroid(child, node);
	return node;
}

void centroidDecompose(int node, int parent)
{
	db("Decomposing with root at", node, parent);
	currentTreeSize = 0;
	dfs1(node, node);
	// db("dfs1 Done");
	int centroid = getCentroid(node, node);
	db(centroid);
	parentInCentroid[centroid] = parent;
	if (parent == -1)
		parentInCentroid[centroid] = centroid;
	for (auto child : G[centroid])
	{
		G[child].erase(centroid);
		centroidDecompose(child, centroid);
	}
	db("All Child called", centroid, node);
	G[centroid].clear();
}

long long ans[nax];
void update(int node)
{
	db("Update", node);
	int x = node;
	while (true)
	{
		db(x);
		ans[x] = min(ans[x], (ll)dist(x, node));
		if (x == parentInCentroid[x])
			break;
		x = parentInCentroid[x];
	}
}

int query(int node)
{
	db("Query", node);
	int x = node;
	ll ret = INT_MAX;
	while (true)
	{
		db(x);
		ret = min(ret, dist(x, node) + ans[x]);
		if (x == parentInCentroid[x])
			break;
		x = parentInCentroid[x];
	}
	db(node, ret);
	return ret;
}

void solve()
{
	db("Start Db");
	cin >> n >> m;
	for (int i = 1; i < n; ++i)
	{
		cin >> u >> v;
		--u;
		--v;
		G[u].insert(v);
		G[v].insert(u);
	}
	db("Input taken");
	constructLca();
	db("LCA constructed");
	centroidDecompose(0, -1);
	db("Centroid Decomposed");
	for (int i = 0; i < n; ++i)
		ans[i] = INT_MAX;
	update(0);
	int choice, v;
	while (m--)
	{
		cin >> choice >> v;
		v--;
		if (choice == 1)
			update(v);
		else
			cout << query(v) << '\n';
	}
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