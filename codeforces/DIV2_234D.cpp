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
int n, m, k, u, v, w;
vector<int> Comp, Iden[510];
vector<pair<int, int>> Adj[nax];
ll Final[510][510];

struct Matrix
{
	vector<vector<ll>> M;
	int k;
	Matrix(int k = 500, bool unit = false) : k(k)
	{
		if (unit)
			M = vector<vector<ll>>(k, vector<ll>(k, 1e18));
		else
			M = vector<vector<ll>>(k, vector<ll>(k));
	}
	Matrix operator*(Matrix &c)
	{
		Matrix res(k, true);
		for (int i = 0; i < k; ++i)
			for (int j = 0; j < k; ++j)
			{
				// res.M[i][j] = 1e18;
				for (int k = 0; k < this->k; ++k)
					res.M[j][k] = min(res.M[j][k], M[j][i] + c.M[i][k]);
			}
		return res;
	}
};
vector<int> parent(nax), ran(nax);
void init()
{
	for (int i = 0; i < nax; ++i)
		parent[i] = i;
}

int find(int u)
{
	if (u == parent[u])
		return u;
	return parent[u] = find(parent[u]);
}

bool unite(int u, int v)
{
	u = find(u);
	v = find(v);
	if (u != v)
	{
		if (ran[u] < ran[v])
			swap(u, v);
		parent[v] = u;
		if (ran[u] == ran[v])
			ran[u]++;
		return true;
	}
	return false;
}

Matrix pow(Matrix &base, int index)
{
	if (index == 0)
		return Matrix(base.k, true);
	if (index == 1)
		return base;
	Matrix temp = pow(base, index / 2);
	temp = temp * temp;
	if (index & 1)
		temp = temp * base;
	return temp;
}

void solve()
{
	cin >> n >> m >> k;
	Comp = vector<int>(n + 1);
	int idx = 1;
	// db("Here1");
	for (int i = 0; i < k; ++i)
	{
		int n;
		cin >> n;
		while (n--)
		{
			Comp[idx] = i;
			Iden[i].pb(idx);
			++idx;
		}
	}
	// db("Here2");
	init();
	for (int i = 0; i <= k; ++i)
		for (int j = 0; j <= k; ++j)
			Final[i][j] = 1e17;
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v >> w;
		Adj[u].pb({v, w});
		Adj[v].pb({u, w});
		if (w == 0)
			unite(u, v);
		u = Comp[u];
		v = Comp[v];
		Final[u][v] = min((ll)w, Final[u][v]);
		Final[v][u] = min((ll)w, Final[v][u]);
	}
	// db("Here3");
	// db(n);
	for (int i = 0; i < k; ++i)
	{
		Final[i][i] = 0;
		for (auto id : Iden[i])
			if (find(id) != find(Iden[i][0]))
			{
				cout << "No";
				return;
			}
	}
	cout << "Yes\n";
	// db("May Be yes");
	Matrix res(k);
	for (int mid = 0; mid < k; mid++)
		for (int i = 0; i < k; i++)
			for (int j = 0; j < k; j++)
				Final[i][j] = min(Final[i][j], Final[i][mid] + Final[mid][j]);

	// db(k);
	// res = pow(res, k + 1);
	// for (int i = 0; i < k; ++i)
	// {
	// 	for (int j = 0; j < k; ++j)
	// 		cout << (res.M[i][j] > 1e14 ? -1 : res.M[i][j]) << ' ';
	// 	cout << '\n';
	// }
	// cout << '\n';
	res = res * res;
	for (int i = 0; i < k; ++i)
	{
		for (int j = 0; j < k; ++j)
			cout << (Final[i][j] > 1e14 ? -1 : Final[i][j]) << ' ';
		cout << '\n';
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