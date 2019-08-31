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

const int nax = 2e5 + 10;

class UnionFind
{ // OOP style
private:
	vector<ll> p, rank, setSize; // remember: vi is vector<int>
	ll numSets;
	ll res;

public:
	UnionFind(int N)
	{
		res = 0;
		setSize.assign(N, 1);
		numSets = N;
		rank.assign(N, 0);
		p.assign(N, 0);
		for (int i = 0; i < N; i++)
			p[i] = i;
	}
	int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
	bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
	ll cla(int i)
	{
		return setSize[i] * (setSize[i] - 1) / 2;
	}
	bool unionSet(int i, int j)
	{
		if (!isSameSet(i, j))
		{
			numSets--;
			int x = findSet(i), y = findSet(j);
			// rank is used to keep the tree short
			res -= cla(x);
			res -= cla(y);
			if (rank[x] > rank[y])
			{
				p[y] = x;
				setSize[x] += setSize[y];
				res += cla(x);
			}
			else
			{
				p[x] = y;
				setSize[y] += setSize[x];
				if (rank[x] == rank[y])
					rank[y]++;
				res += cla(y);
			}
			return true;
		}
		return false;
	}
	int numDisjointSets() { return numSets; }
	int sizeOfSet(int i) { return setSize[findSet(i)]; }
	ll ret()
	{
		return res;
	}
};

void solve()
{
	int n, m, u, v, w;
	cin >> n >> m;
	map<int, vector<pair<int, int>>> Edges;
	vector<bool> Exist(2e5 + 10);
	for (int i = 0; i < n - 1; ++i)
	{
		cin >> u >> v >> w;
		--u;
		--v;
		Edges[w].pb({u, v});
		Exist[w] = true;
	}
	UnionFind uf(n);
	vector<pair<int, ll>> Q;
	Q.pb({-1, 0});
	// int xxx = 2e5;
	// db(xxx * xxx, (xxx * xxx) / xxx);
	for (auto Edge : Edges)
	{
		db(Edge.f);
		pc(Edge.s);
		for (auto pp : Edge.s)
			uf.unionSet(pp.f, pp.s);
		Q.pb({Edge.f, uf.ret()});
	}
	Q.pb({mod, uf.ret()});
	pc(Q);
	while (m--)
	{
		cin >> w;
		auto it = lower_bound(Q.begin(), Q.end(), make_pair(w, 0LL));
		if (!Exist[w])
			--it;
		cout << (it->s) << ' ';
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