//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
#ifdef Debug
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__);
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
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
const long long mod = 1000000007;
auto TimeStart = chrono::steady_clock::now();

const int nax = 2e5 + 10;
int u, v, w;

class Solver
{
	int n;
	vector<vector<pair<int, int>>> G;
	vector<vector<int>> root;
	vector<int> pi, dist, lvl;
	void dfs(int node, int p, int depth)
	{
		lvl[node] = depth;
		for (auto child : G[node])
		{
			if (child.f == p)
				continue;
			dist[child.f] = child.s + dist[node];
			pi[child.f] = node;
			dfs(child.f, node, depth + 1);
		}
	}
	void calcRoot()
	{
		for (int i = 1; i <= n; ++i)
		{
			root[i][0] = pi[i];
			db(i, 0, root[i][0]);
		}
		for (int j = 1; (1 << j) < n; ++j)
			for (int i = 1; i <= n; ++i)
			{
				if (root[i][j - 1] != -1)
					root[i][j] = root[root[i][j - 1]][j - 1];
				db(i, j, root[i][j]);
			}
	}
	int lca(int a, int b)
	{
		if (lvl[a] < lvl[b])
			swap(a, b);
		int stp;
		for (stp = 1; (1 << stp) <= lvl[a]; ++stp)
			;
		--stp;
		for (int i = stp; i >= 0; --i)
			if (lvl[a] - (1 << i) >= lvl[b])
				a = root[a][i];
		if (a == b)
			return a;
		for (int i = stp; i >= 0; --i)
			if (root[a][i] != -1 && root[a][i] != root[b][i])
				a = root[a][i], b = root[b][i];
		return pi[a];
	}
	int find(int p, int t)
	{
		int stp;
		for (stp = 1; 1 << stp <= lvl[p]; ++stp)
			;
		stp--;
		for (stp; stp >= 0; --stp)
			if (lvl[p] - (1 << stp) >= t)
				p = root[p][stp];
		return p;
	}

public:
	void Solve()
	{
		cin >> n;
		n++;
		G.resize(n);
		pi.resize(n, -1);
		dist.resize(n, 0);
		lvl.resize(n, 0);
		root.resize(1 << 14, vector<int>(14, -1));
		--n;
		for (int i = 1; i < n; ++i)
		{
			cin >> u >> v >> w;
			G[u].pb({v, w});
			G[v].pb({u, w});
		}
		dist[1] = 0;
		// db("Dfs");
		dfs(1, 0, 0);
		// db("Calcroot");
		calcRoot();
		string q;
		int st, en;
		// db("Start1");
		while (true)
		{
			cin >> q;
			// db("Start", q);
			if (q[1] == 'O')
				break;
			cin >> st >> en;
			int anc = lca(st, en), k;
			db(anc, st, en);
			if (q[1] == 'I')
				cout << dist[st] + dist[en] - 2 * dist[anc] << '\n';
			else
			{
				cin >> k;
				if (lvl[st] - lvl[anc] + 1 >= k)
					k = find(st, lvl[st] - k + 1);
				else
					k = find(en, 2 * lvl[anc] + k - lvl[st] - 1);
				cout << k << '\n';
			}
		}
		cout << '\n';
	}
};

void solve()
{
	Solver S;
	S.Solve();
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