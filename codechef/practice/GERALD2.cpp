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
int dp[19][nax], Level[nax];
struct LeastCommonAncestor
{
	int Log;
	LeastCommonAncestor() {}
	LeastCommonAncestor(int n)
	{
		Log = 19;
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
		return dp[0][a];
	}
	int dist(int a, int b)
	{
		return Level[a] + Level[b] - 2 * Level[lca(a, b)];
	}
};

struct Node
{
	int val, name;
	Node(int val = INT_MIN, int name = 0) : val(val), name(name) {}
	Node operator+(const Node &rhs)
	{
		Node a = *this;
		if (a.val == rhs.val)
			a.name = max(a.name, rhs.name);
		else if (a.val < rhs.val)
			a.name = rhs.name;
		a.val = max(a.val, rhs.val);
		return a;
	}
};
ostream &operator<<(ostream &out, const Node &p)
{
	out << "Val " << p.val << ' ';
	out << "Name " << p.name << ' ';
	return out;
}
istream &operator>>(istream &in, Node &p)
{
	in >> p.val;
	return in;
}

struct Segtree
{
	vector<Node> Seg;
	vector<Node> Base;
	int n;
	Segtree(int n = 5)
	{
		this->n = n;
		Seg.resize(4 * n + 10);
	}
	void build(int node, int start, int end)
	{
		if (start == end)
		{
			Seg[node] = Base[start];
			return;
		}
		int mid = (start + end) / 2;
		build(2 * node, start, mid);
		build(2 * node + 1, mid + 1, end);
		Seg[node] = Seg[2 * node] + Seg[2 * node + 1];
	}
	void build(vector<Node> &Arr)
	{
		Base = Arr;
		n = Arr.size();
		Seg.resize(4 * n + 10);
		build(1, 0, n - 1);
	}
	Node Query(int node, int start, int end, int qstart, int qend)
	{
		if (qend < start || qstart > end || start > end)
			return Node();
		if (qstart <= start && end <= qend)
			return Seg[node];
		int mid = (start + end) / 2;
		return Query(2 * node, start, mid, qstart, qend) + Query(2 * node + 1, mid + 1, end, qstart, qend);
	}
	void pUpdate(int node, int start, int end, int pos, Node val)
	{
		if (start == end)
		{
			Seg[node] = val;
			return;
		}
		int mid = (start + end) / 2;
		if (pos <= mid)
			pUpdate(2 * node, start, mid, pos, val);
		else
			pUpdate(2 * node + 1, mid + 1, end, pos, val);
		Seg[node] = Seg[2 * node] + Seg[2 * node + 1];
	}
	Node query(int left, int right)
	{
		return Query(1, 0, n - 1, left, right);
	}
	void update(int pos, Node val)
	{
		pUpdate(1, 0, n - 1, pos, val);
	}
};

struct ToStore
{
	int PosinTree;
	Node res;
	ToStore(int c = 0, Node res = 0) : PosinTree(c), res(res) {}
};

Segtree Seg[nax];
LeastCommonAncestor lca;
vector<int> Ct[nax], inSubTree[nax];
int sizeOfSubtree[nax], CenPar[nax];
bool Computed[nax], isWhite[nax];
map<int, ToStore> Storage[nax];
map<int, int> StartSeg[nax], EndSeg[nax];

class Solver
{
	int n, currentTreeSize, root;
	int dfsSize(int node, int par)
	{
		sizeOfSubtree[node] = 1;
		for (auto child : Adj[node])
			if (child != par && !Computed[child])
				sizeOfSubtree[node] += dfsSize(child, node);
		return sizeOfSubtree[node];
	}
	int getCentroid(int node, int par)
	{
		for (auto child : Adj[node])
			if (child != par && !Computed[child])
				if (sizeOfSubtree[child] > currentTreeSize / 2)
					return getCentroid(child, node);
		return node;
	}
	void decompose(int node, int par)
	{
		currentTreeSize = dfsSize(node, node);
		int centroid = getCentroid(node, par);
		db(node, centroid, par);
		if (par == -1)
		{
			CenPar[centroid] = centroid;
			root = centroid;
		}
		else
		{
			CenPar[centroid] = par;
			Ct[centroid].pb(par);
			Ct[par].pb(centroid);
		}
		Computed[centroid] = true;
		for (auto child : Adj[centroid])
			if (child != par && !Computed[child])
				decompose(child, centroid);
	}
	void prepareForQueries(int node, int par)
	{
		vector<Node> base;
		inSubTree[node].pb(node);
		base.push_back(Node(0, node));
		Storage[node][node] = ToStore(0, Node(0, node));
		for (auto child : Ct[node])
			if (child != par)
			{
				StartSeg[node][child] = base.size();
				prepareForQueries(child, node);
				for (auto grandChild : inSubTree[child])
				{
					int temp = lca.dist(grandChild, node);
					Storage[node][grandChild] = ToStore(base.size(), Node(temp, grandChild));
					base.push_back(Node(temp, grandChild));
					inSubTree[node].pb(grandChild);
				}
				EndSeg[node][child] = base.size() - 1;
			}
		db(node);
		pc(inSubTree[node]);
		pc(base);
		Seg[node].build(base);
	}
	void makeBlack(int node)
	{
		int curr = node;
		Seg[node].update(0, Node());
		while (true)
		{
			if (CenPar[curr] == curr)
				break;
			int par = CenPar[curr];
			Seg[par].update(Storage[par][node].PosinTree, Node());
			curr = par;
		}
	}
	void makeWhite(int node)
	{
		int curr = node;
		Seg[node].update(0, Node(0, node));
		while (true)
		{
			if (CenPar[curr] == curr)
				break;
			int par = CenPar[curr];
			auto temp = Storage[par][node];
			Seg[par].update(temp.PosinTree, temp.res);
			curr = par;
		}
	}
	int query(int node)
	{
		db("Query", node);
		int curr = node;
		Node base(0, node);
		base = Seg[node].query(0, inSubTree[node].size() - 1);
		while (true)
		{
			if (CenPar[curr] == curr)
				break;
			int par = CenPar[curr];
			ll dist1 = Storage[par][node].res.val;
			Node temp = Seg[par].query(0, StartSeg[par][curr] - 1) + Seg[par].query(EndSeg[par][curr] + 1, inSubTree[par].size() - 1);
			temp.val += dist1;
			base = base + temp;
			db(curr, temp, base);
			curr = par;
		}
		return base.name;
	}

public:
	void solve()
	{
		int m;
		cin >> n >> m;
		// db(n);
		for (int i = 0; i < n; ++i)
		{
			Adj[i].clear();
			Ct[i].clear();
			inSubTree[i].clear();
			Computed[i] = false;
			isWhite[i] = true;
			Storage[i].clear();
		}
		int v;
		// cerr << "Time elapsed: Init" << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
		// TimeStart = chrono::steady_clock::now();
		for (int i = 1; i < n; ++i)
		{
			cin >> v;
			--v;
			Adj[v].pb(i);
			Adj[i].pb(v);
		}
		// cerr << "Time elapsed: Input " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
		// TimeStart = chrono::steady_clock::now();
		lca = LeastCommonAncestor(n);
		// cerr << "Time elapsed: Lca " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
		// TimeStart = chrono::steady_clock::now();
		decompose(0, -1);
		// cerr << "Time elapsed: CD " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
		// TimeStart = chrono::steady_clock::now();
		prepareForQueries(root, -1);
		// TimeStart = chrono::steady_clock::now();
		// cerr << "Time elapsed: Prepare " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
		// pc(CenPar);
		while (m--)
		{
			cin >> v;
			--v;
			bool ok = isWhite[v];
			if (!ok) //isBlack
			{
				makeWhite(v);
				isWhite[v] = true;
			}
			int ans = query(v);
			db("Query", v, ans);
			cout << ans + 1 << '\n';
			if (ok) //isWhite
			{
				makeBlack(v);
				isWhite[v] = false;
			}
		}
		// cerr << "Time elapsed: Queries " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
		// TimeStart = chrono::steady_clock::now();
	}
};

void solve()
{
	Solver s;
	s.solve();
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
	// cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
	return 0;
}