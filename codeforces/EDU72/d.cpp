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

const int nax = 5e3 + 10;

typedef vector<int> _vi;
typedef vector<_vi> _graph;
#define mp make_pair

class SCC
{
public:
	int _n, _m, CompC;
	_graph G, RevG, SccG;
	stack<int> St;
	_vi Vis, Comp;
	SCC()
	{
	}
	void fillOrder(int i)
	{
		Vis[i] = true;
		for (int x : G[i])
			if (!Vis[x])
				fillOrder(x);
		St.push(i);
	}
	void Dfs(int u, int c)
	{
		Vis[u] = true;
		Comp[u] = c;
		for (int x : RevG[u])
			if (!Vis[x])
				Dfs(x, c);
	}
	void MakeScc()
	{
		for (int i = 0; i < _n; ++i)
			if (!Vis[i])
				fillOrder(i);
		fill(Vis.begin(), Vis.end(), false);
		CompC = 0;
		while (!St.empty())
		{
			auto v = St.top();
			St.pop();
			if (!Vis[v])
				Dfs(v, CompC++);
		}
		SccG.resize(CompC);
		for (int i = 0; i < _n; ++i)
			for (auto y : G[i])
				if (Comp[i] != Comp[y])
					SccG[Comp[i]].pb(Comp[y]);
		for (int i = 0; i < CompC; ++i)
		{
			sort(SccG[i].begin(), SccG[i].end());
			SccG[i].erase(unique(SccG[i].begin(), SccG[i].end()), SccG[i].end());
		}
	}
	SCC(_graph _G)
	{
		G = _G;
		_n = G.size();
		_m = 0;
		Vis.resize(_n);
		Comp.resize(_n);
		RevG.resize(_n);
		for (int i = 0; i < _n; ++i)
			for (auto y : G[i])
			{
				_m++;
				RevG[y].pb(i);
			}
		MakeScc();
	}
	pair<_graph, _vi> GetScc()
	{
		return mp(SccG, Comp);
	}
};

void solve()
{
	int u, v, n, m;
	cin >> n >> m;
	vector<vector<int>> Adj(n);
	vector<vector<int>> AdjNew(n);
	map<pair<int, int>, int> index;
	map<pair<int, int>, int> Clr;
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v;
		--u;
		--v;
		Adj[u].pb(v);
		index[{u, v}] = i;
	}
	SCC s(Adj);
	auto CompDet = s.GetScc();
	int cnt = s.CompC;
	db(cnt);
	for (int i = 0; i < n; ++i)
		for (auto y : Adj[i])
			if (s.Comp[i] == s.Comp[y])
				AdjNew[i].pb(y);
			else
				Clr[{i, y}] = 1;
	for (int i = 0; i < n; ++i)
		pc(AdjNew[i]);
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