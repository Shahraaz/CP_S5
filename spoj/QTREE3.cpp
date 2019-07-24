//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
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

const int nax = 2e5 + 10;
int n, q;
vector<vector<int>> Adj;
vector<int> Size, parent;
int LogN;

void dfs(int node, int p)
{
	Size[node] = 1;
	parent[node] = p;
	for (int c : Adj[node])
		if (c != p)
		{
			dfs(c, node);
			Size[node] += Size[c];
		}
}

vector<int> ChainHead, ChainPos, ChainId, nodeAtPos;
int ChainNo, pos;

void HLD(int node, int p)
{
	if (ChainHead[ChainNo] < 0)
		ChainHead[ChainNo] = node;
	ChainPos[node] = pos;
	ChainId[node] = ChainNo;
	nodeAtPos[pos] = node;
	++pos;
	int maxid = -1;
	for (int i = 0; i < Adj[node].size(); ++i)
		if (Adj[node][i] != p)
			if ((maxid < 0) || (Size[Adj[node][i]] > Size[Adj[node][maxid]]))
				maxid = i;
	if (maxid >= 0)
		HLD(Adj[node][maxid], node);
	for (int i = 0; i < Adj[node].size(); ++i)
		if (Adj[node][i] != p)
			if (i != maxid)
			{
				ChainNo++;
				HLD(Adj[node][i], node);
			}
}

vector<int> St, base;

int query(int node, int start, int end, int qstart, int qend)
{
	// db(start, end, qstart, qend);
	if (start > end || qend < start || end < qstart)
		return mod;
	if (qstart <= start && end <= qend)
		return St[node];
	int mid = (start + end) / 2;
	return min(query(2 * node, start, mid, qstart, qend), query(2 * node + 1, mid + 1, end, qstart, qend));
}

int Query(int u)
{
	int v = 1;
	int uchain = ChainId[u], vchain = ChainId[v];
	int ans = mod;
	while (true)
	{
		uchain = ChainId[u];
		if (uchain == vchain)
		{
			ans = min(ans, query(1, 0, pos - 1, ChainPos[v], ChainPos[u]));
			break;
		}
		ans = min(ans, query(1, 0, pos - 1, ChainPos[ChainHead[uchain]], ChainPos[u]));
		u = parent[ChainHead[uchain]];
	}
	if (ans >= mod)
		return -1;
	return nodeAtPos[ans];
}

void update(int node, int start, int end, int pos)
{
	db(start, end, pos);
	if (start == end)
	{
		base[start] = 1 - base[start];
		if (base[start])
			St[node] = start;
		else
			St[node] = mod;
		return;
	}
	int mid = (start + end) / 2;
	if (pos <= mid)
		update(2 * node, start, mid, pos);
	else
		update(2 * node + 1, mid + 1, end, pos);
	St[node] = min(St[2 * node], St[2 * node + 1]);
}

void Update(int node)
{
	update(1, 0, pos - 1, ChainPos[node]);
}

void solve()
{
	cin >> n >> q;
	Adj = vector<vector<int>>(n + 1);
	Size = vector<int>(n + 1);
	base = vector<int>(n + 1);
	nodeAtPos = vector<int>(n + 1);
	parent = vector<int>(n + 1);
	ChainHead = vector<int>(n + 1, -1);
	ChainPos = vector<int>(n + 1);
	ChainId = vector<int>(n + 1);
	int u, v;
	for (int i = 1; i < n; ++i)
	{
		cin >> u >> v;
		Adj[u].pb(v);
		Adj[v].pb(u);
	}
	dfs(1, 0);
	HLD(1, 0);
	St = vector<int>(4 * (n + 1), mod);
	while (q--)
	{
		cin >> u >> v;
		if (u)
			cout << Query(v) << '\n';
		else
			Update(v);
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