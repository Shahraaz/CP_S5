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

const int nax = 2e5 + 10, Log = 19;

vector<pair<int, int>> Adj[nax];
int dp[Log][nax], Level[nax];
bool vis[nax];
ll Dist[nax];

void Lca(int n)
{
	memset(dp, -1, sizeof(dp));
	queue<int> Q;
	Q.push(0);
	vis[0] = true;
	while (!Q.empty())
	{
		auto top = Q.front();
		Q.pop();
		for (auto child : Adj[top])
			if (!vis[child.f])
			{
				Level[child.f] = 1 + Level[top];
				Dist[child.f] = Dist[top] + child.s;
				dp[0][child.f] = top;
				vis[child.f] = true;
				Q.push(child.f);
			}
	}
	for (int i = 1; i < Log; ++i)
		for (int j = 0; j < n; ++j)
			if (dp[i - 1][j] != -1)
				dp[i][j] = dp[i - 1][dp[i - 1][j]];
}

int lca(int a, int b)
{
	if (Level[a] > Level[b])
		swap(a, b);
	int d = Level[b] - Level[a];
	for (int i = Log - 1; i >= 0; --i)
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
	return dp[0][a];
}

ll dist(int a, int b)
{
	return Dist[a] + Dist[b] - 2 * Dist[lca(a, b)];
}

int currentSize, subTreeSize[nax], parCentroid[nax];
bool Computed[nax];

void dfs1(int node, int par)
{
	currentSize++;
	subTreeSize[node] = 1;
	for (auto child : Adj[node])
		if (child.f != par && !Computed[child.f])
		{
			dfs1(child.f, node);
			subTreeSize[node] += subTreeSize[child.f];
		}
}

int getCentroid(int node, int par)
{
	for (auto child : Adj[node])
		if (child.f != par && !Computed[child.f])
			if (subTreeSize[child.f] > currentSize / 2)
				return getCentroid(child.f, node);
	return node;
}

vector<int> Ct[nax];
int root = -1;
vector<ll> distancesToChildren[nax], distancesToChildrenfromParent[nax], inChildTree[nax];
void decompose(int node, int par)
{
	if (Computed[node])
		return;
	currentSize = 0;
	dfs1(node, par);
	int centroid = getCentroid(node, par);
	if (par == -1)
	{
		root = centroid;
		parCentroid[centroid] = centroid;
	}
	else
	{
		Ct[centroid].pb(par);
		Ct[par].pb(centroid);
		parCentroid[centroid] = par;
	}
	Computed[centroid] = 1;
	for (auto child : Adj[centroid])
		if (child.f != par && !Computed[child.f])
			decompose(child.f, centroid);
}

int query(int node, ll len)
{
	int ret = 0, curr = node, prev = -1;
	ret += upper_bound(distancesToChildren[node].begin(), distancesToChildren[node].end(), len) - distancesToChildren[node].begin();
	while (true)
	{
		if (parCentroid[curr] == curr)
			break;
		ll d = len - dist(node, parCentroid[curr]);
		int sub = upper_bound(distancesToChildrenfromParent[curr].begin(), distancesToChildrenfromParent[curr].end(), d) - distancesToChildrenfromParent[curr].begin();
		curr = parCentroid[curr];
		int add = upper_bound(distancesToChildren[curr].begin(), distancesToChildren[curr].end(), d) - distancesToChildren[curr].begin();
		ret += add - sub;
	}
	return ret;
}

void prepareForQueries(int node, int par)
{
	inChildTree[node].pb(node);
	distancesToChildren[node].pb(0);
	if (par != -1)
		distancesToChildrenfromParent[node].pb(dist(par, node));
	for (auto child : Ct[node])
		if (child != par)
		{
			prepareForQueries(child, node);
			for (auto grandChild : inChildTree[child])
			{
				inChildTree[node].pb(grandChild);
				distancesToChildren[node].pb(dist(node, grandChild));
				if (par != -1)
					distancesToChildrenfromParent[node].pb(dist(par, grandChild));
			}
		}
	sort(distancesToChildren[node].begin(), distancesToChildren[node].end());
	sort(distancesToChildrenfromParent[node].begin(), distancesToChildrenfromParent[node].end());
	db(node, par);
	pc(Ct[node]);
	pc(inChildTree[node]);
	pc(distancesToChildren[node]);
	pc(distancesToChildrenfromParent[node]);
}

void solve()
{
	int n, q, u, v, w;
	cin >> n >> q;
	for (int i = 1; i < n; ++i)
	{
		cin >> u >> v >> w;
		--u, --v;
		Adj[u].pb({v, w});
		Adj[v].pb({u, w});
	}
	db("Lca Start");
	Lca(n);
	db("Lca End Decompose Start");
	decompose(0, -1);
	db("Decompose End prepareforqueries Start");
	prepareForQueries(root, -1);
	db("prepareforqueries end");
	ll len;
	while (q--)
	{
		cin >> u >> len;
		--u;
		cout << query(u, len) << '\n';
		// flush(cout);
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