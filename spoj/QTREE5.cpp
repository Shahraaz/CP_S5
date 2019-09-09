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

const int nax = 1e5 + 10;

struct CentroidDecomposition
{
	vector<vector<int>> &Adj;
	vector<int> subTreeSize, parentInCentroid;
	vector<bool> Computed;
	int root, n, currentTreeSize;
	CentroidDecomposition(vector<vector<int>> &tree) : Adj(tree)
	{
		n = Adj.size();
		parentInCentroid.assign(n, -1);
		subTreeSize.assign(n, 0);
		Computed.assign(n, false);
		decompose(0, -1);
	}
	void dfs(int node, int parent)
	{
		currentTreeSize++;
		subTreeSize[node] = 1;
		for (auto child : Adj[node])
		{
			if (child == parent || Computed[child])
				continue;
			dfs(child, node);
			subTreeSize[node] += subTreeSize[child];
		}
	}
	int getCentroid(int node, int parent)
	{
		for (auto child : Adj[node])
			if (child != parent && !Computed[child])
				if (subTreeSize[child] > currentTreeSize / 2)
					return getCentroid(child, node);
		return node;
	}
	void decompose(int node, int parent)
	{
		currentTreeSize = 0;
		dfs(node, node);
		int centroid = getCentroid(node, node);
		parentInCentroid[centroid] = (parent == -1) ? centroid : parent;
		Computed[centroid] = true;
		for (auto child : Adj[centroid])
			if (!Computed[child])
				decompose(child, centroid);
	}
};

struct LeastCommonAncestor
{
	vector<int> Level;
	vector<vector<int>> dp;
	vector<vector<int>> Adj;
	int Log;
	LeastCommonAncestor(vector<vector<int>> Tree) : Adj(Tree)
	{
		Log = 20;
		int n = Tree.size();
		dp.assign(Log, vector<int>(n));
		Level.assign(n, 0);
		dfs(0, 0, 0);
		for (int i = 1; i < Log; ++i)
			for (int j = 0; j < n; ++j)
				dp[i][j] = dp[i - 1][dp[i - 1][j]];
	}
	void dfs(int node, int parent, int level)
	{
		dp[0][node] = parent;
		Level[node] = level;
		for (auto child : Adj[node])
			if (child != parent)
				dfs(child, node, level + 1);
	}
	int lca(int a, int b)
	{
		db(a, b);
		if (Level[a] > Level[b])
			swap(a, b);
		int d = Level[b] - Level[a];
		for (int i = 0; i < Log; ++i)
			if (d & (1 << i))
				b = dp[i][b];
		if (a == b)
			return a;
		for (int i = Log - 1; i >= 0; --i)
			if (dp[i][a] != dp[i][b])
			{
				a = dp[i][a];
				b = dp[i][b];
			}
		db(dp[0][a]);
		return dp[0][a];
	}
	int dist(int a, int b)
	{
		return Level[a] + Level[b] - 2 * Level[lca(a, b)];
	}
};

struct node
{
	int pos, dist;
	node(int pos, int dist) : pos(pos), dist(dist) {}
	bool operator<(const node &x) const
	{
		return dist > x.dist;
	}
};

priority_queue<node> Q[nax];
bool white[nax];

int distw(int x)
{
	while (!Q[x].empty())
	{
		node curr = Q[x].top();
		if (!white[curr.pos])
			Q[x].pop();
		else
			return curr.dist;
	}
	return INT_MAX;
}

void solve()
{
	int n, u, v;
	cin >> n;
	vector<vector<int>> Tree(n);
	for (int i = 1; i < n; ++i)
	{
		cin >> u >> v;
		--u;
		--v;
		Tree[u].pb(v);
		Tree[v].pb(u);
	}
	int q, ch;
	cin >> q;
	CentroidDecomposition cd(Tree);
	LeastCommonAncestor lcaTree(Tree);
	while (q--)
	{
		cin >> ch >> v;
		--v;
		if (!ch)
		{
			white[v] = !white[v];
			if (white[v])
			{
				int curr = v;
				while (true)
				{
					Q[curr].push(node(v, lcaTree.dist(v, curr)));
					int next = cd.parentInCentroid[curr];
					if (next == curr)
						break;
					curr = next;
				}
			}
		}
		else
		{
			ll ans = INT_MAX;
			int curr = v;
			while (true)
			{
				ans = min(ans, (ll)lcaTree.dist(v, curr) + distw(curr));
				int next = cd.parentInCentroid[curr];
				if (next == curr)
					break;
				curr = next;
			}
			if (ans > n)
				cout << -1 << '\n';
			else
				cout << ans << '\n';
			flush(cout);
		}
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