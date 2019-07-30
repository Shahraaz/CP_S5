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

const int nax = 1e5 + 10;

struct edge
{
	int to, cost;
	edge(int to, int cost) : to(to), cost(cost) {}
};

vector<edge> G[nax];
int n, blackCnt;
bool color[nax];

int fa[nax], fv[nax], s[nax], id[nax], idR[nax], bel[nax], timestamp, sz[nax];
int sum[nax], root[nax];
const int maxNode = (1 << 18) + 10;

struct Node
{
	int maxL, maxR, opt;
	Node(int maxL = -mod, int maxR = -mod, int opt = -mod) : maxL(maxL), maxR(maxR), opt(opt) {}
} segs[maxNode];
int ls[maxNode], rs[maxNode];
int segCnt = 0;

template <typename T>
struct Rint
{
	bool operator()(const T &l, const T &r) const
	{
		return l > r;
	}
};

multiset<int, Rint<int>> ch[nax], ans;

int dfs1(int node, int parent)
{
	fa[node] = parent;
	s[node] = 1;
	for (auto a : G[node])
	{
		auto v = a.to;
		if (v != parent)
		{
			fv[v] = a.cost;
			s[node] += dfs1(v, node);
		}
	}
	return s[node];
}

void dfs2(int node, int num)
{
	idR[timestamp] = node;
	id[node] = timestamp++;
	bel[node] = num;
	sz[num]++;
	int Max = 0, idx = -1;
	for (int i = 0; i < G[node].size(); ++i)
	{
		auto &e = G[node][i];
		if (e.to != fa[node])
			if (s[e.to] > Max)
			{
				Max = s[e.to];
				idx = e.to;
			}
	}
	if (Max == 0)
		return;
	dfs2(idx, num);
	for (int i = 0; i < G[node].size(); ++i)
	{
		auto &e = G[node][i];
		if (e.to != fa[node])
			if (e.to != idx)
				dfs2(e.to, e.to);
	}
}

Node merge(const Node &ln, const Node &rn, int dL, int dMid, int dR)
{
	Node newNode;
	newNode.maxL = max(ln.maxL, dL + rn.maxL);
	newNode.maxR = max(rn.maxR, dR + rn.maxR);
	newNode.maxL = max(ln.maxL, dL + rn.maxL);
	newNode.opt = max(max(ln.opt, rn.opt), dMid + ln.maxR + rn.maxL);
	return newNode;
}

void maintain(int o, int u)
{
	int d1 = -mod, d2 = -mod;
	if (color[u] == 0)
		d1 = d1 = 0;
	if (ch[u].size())
		d1 = max(d1, *ch[u].begin());
	if (ch[u].size() > 1)
		d2 = max(d2, *(++ch[u].begin()));
	segs[o].maxL = segs[o].maxR = d1;
	segs[o].opt = d1 + d2;
	if (color[u] == 0)
		segs[o].opt = max(segs[o].opt, 0);
}

void buildTree(int o, int l, int r)
{
	if (r - l == 1)
	{
		int u = idR[l];
		for (int i = 0; i < G[u].size(); ++i)
		{
			auto &e = G[u][i];
			if (e.to != fa[u])
				if (bel[e.to] != bel[u])
				{
					buildTree(root[e.to] = segCnt++, id[e.to], id[e.to] + sz[e.to]);
					ch[u].insert(segs[root[e.to]].maxL, e.cost);
					ans.insert(segs[root[e.to]].opt);
				}
		}
		maintain(o, u);
	}
	else
	{
		int mid = (l + r) / 2;
		buildTree(ls[o] = segCnt++, l, mid);
		buildTree(rs[o] = segCnt++, mid, r);
		segs[o] = merge(segs[ls[0]], segs[rs[0]], sum[mid] - sum[l], sum[mid] - sum[mid - 1], sum[r - 1] - sum[mid - 1]);
	}
}

void process()
{
	dfs1(0, -1);
	dfs2(0, 0);
	for (int i = 0; i < n; ++i)
		sum[id[i]] = fv[i];
	for (int i = 1; i < n; ++i)
		sum[i] += sum[i - 1];
	buildTree(root[0] = segCnt++, id[0], id[0] + sz[0]);
}

void solve()
{
	int f, t, c;
	cin >> n;
	blackCnt = n;
	for (int i = 1; i < n; ++i)
	{
		cin >> f >> t >> c;
		--f;
		--t;
		G[f].pb(edge(t, c));
		G[t].pb(edge(f, c));
	}
	process();
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