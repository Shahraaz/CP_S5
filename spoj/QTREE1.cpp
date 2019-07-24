//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
#ifdef Debug
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

const int nax = 1e4 + 10, LN = 14;
int n;
vector<int> Adj[nax], costs[nax], Index[nax];
int chainHead[nax], pa[LN][nax], chainNo, depth[nax];
int subsize[nax], otherend[nax], chainInd[nax], ptr, baseArr[nax], posInBase[nax], st[4 * nax];

template <typename Arg>
void parray(Arg *a, int size)
{
	cerr << "{ ";
	for (int i = 0; i < size; ++i)
		cerr << a[i] << ' ';
	cerr << "}\n";
}

void build(int node, int start, int end)
{
	if (start == end)
	{
		st[node] = baseArr[start];
		return;
	}
	int mid = (start + end) / 2;
	build(2 * node, start, mid);
	build(2 * node + 1, mid + 1, end);
	st[node] = max(st[2 * node], st[2 * node + 1]);
}

int query_tree(int node, int start, int end, int qstart, int qend)
{
	// db(start, end, qstart, qend);
	if (end < qstart || start > qend)
		return -1;
	if (qstart <= start && end <= qend)
		return st[node];
	int mid = (start + end) / 2;
	return max(query_tree(2 * node, start, mid, qstart, qend),
			   query_tree(2 * node + 1, mid + 1, end, qstart, qend));
}

void update_tree(int node, int start, int end, int pos, int val)
{
	if (pos < start || pos > end)
		return;
	if (start == end)
	{
		st[node] = val;
		return;
	}
	int mid = (start + end) / 2;
	update_tree(2 * node, start, mid, pos, val);
	update_tree(2 * node + 1, mid + 1, end, pos, val);
	st[node] = max(st[2 * node], st[2 * node + 1]);
}

int query_up(int u, int v)
{
	if (u == v)
		return 0;
	int uchain, vchain, ans;
	vchain = chainInd[v];
	ans = -1;
	while (true)
	{
		db(u, v);
		uchain = chainInd[u];
		if (uchain == vchain)
		{
			if (u == v)
				return ans;
			return max(ans, query_tree(1, 0, ptr - 1, posInBase[v] + 1, posInBase[u] + 1));
		}
		ans = max(ans, query_tree(1, 0, ptr - 1, posInBase[chainHead[uchain]], posInBase[u] + 1));
		u = chainHead[uchain];
		u = pa[0][u];
	}
	return ans;
}

int LCA(int u, int v)
{
	if (depth[u] < depth[v])
		swap(u, v);
	int diff = depth[u] - depth[v];
	for (int i = 0; i < LN; ++i)
		if ((diff >> i) & 1)
			u = pa[i][u];
	if (u == v)
		return u;
	for (int i = LN - 1; i >= 0; --i)
		if (pa[i][u] != pa[i][v])
		{
			u = pa[i][u];
			v = pa[i][v];
		}
	return pa[0][u];
}

int query(int u, int v)
{
	int lca = LCA(u, v);
	// db(u, v, lca);
	// cerr << lca << '\n';
	int temp = query_up(u, lca);
	int temp2 = query_up(v, lca);
	cerr << lca << ' ' << temp << ' ' << temp2 << '\n';
	return max(temp, temp2);
}

void change(int i, int val)
{
	int u = otherend[i];
	update_tree(1, 0, ptr - 1, posInBase[u], val);
}

void HLD(int currNode, int cost, int prev)
{
	if (chainHead[chainNo] == -1)
		chainHead[chainNo] = currNode;
	chainInd[currNode] = chainNo;
	posInBase[currNode] = ptr;
	baseArr[ptr++] = cost;
	int sc = -1, ncost;
	for (int i = 0; i < Adj[currNode].size(); ++i)
		if (Adj[currNode][i] != prev)
			if (sc == -1 || subsize[sc] < subsize[Adj[currNode][i]])
			{
				sc = Adj[currNode][i];
				ncost = costs[currNode][i];
			}
	if (sc >= 0)
		HLD(sc, ncost, currNode);
	for (int i = 0; i < Adj[currNode].size(); ++i)
		if ((Adj[currNode][i] != prev) && (i != sc))
		{
			chainNo++;
			HLD(Adj[currNode][i], costs[currNode][i], currNode);
		}
}

void dfs(int node, int p, int _depth = 0)
{
	pa[0][node] = p;
	// db(node,0,p);
	depth[node] = _depth;
	subsize[node] = 1;
	for (int i = 0; i < Adj[node].size(); ++i)
		if (Adj[node][i] != p)
		{
			otherend[Index[node][i]] = Adj[node][i];
			dfs(Adj[node][i], node, _depth + 1);
			subsize[node] += subsize[Adj[node][i]];
		}
}

void solve()
{
	cin >> n;
	int u, v, c;
	for (int i = 0; i < n; ++i)
	{
		Adj[i].clear();
		costs[i].clear();
		Index[i].clear();
	}
	memset(pa, -1, sizeof(pa));
	memset(chainHead, -1, sizeof(chainHead));
	memset(st, -1, sizeof(st));
	for (int i = 1; i < n; ++i)
	{
		cin >> u >> v >> c;
		--u;
		--v;
		Adj[u].pb(v);
		costs[u].pb(c);
		Index[v].pb(i - 1);
		Adj[v].pb(u);
		costs[v].pb(c);
		Index[u].pb(i - 1);
	}
	chainNo = 0;
	dfs(0, -1);
	ptr = 0;
	HLD(0, -1, -1);
	// parray(baseArr, ptr);
	build(1, 0, ptr - 1);
	for (int i = 1; i < LN; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (pa[i - 1][j] >= 0)
				pa[i][j] = pa[i - 1][pa[i - 1][j]];
			// db(i, j, pa[i][j],pa[i-1][j]);
		}
	}
	string s;
	while (true)
	{
		cin >> s;
		if (s[0] == 'D')
			return;
		cin >> u >> v;
		if (s[0] == 'Q')
			cout << query(u - 1, v - 1) << '\n';
		else
			change(u - 1, v);
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
#ifdef TIME
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}