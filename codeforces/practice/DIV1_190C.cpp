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
set<int> Adj[nax];
int n, u, v;
char ans[nax];
int sizeOfSubTree[nax], currentTreeSize;

void dfs1(int node, int par)
{
	currentTreeSize++;
	sizeOfSubTree[node] = 1;
	for (auto child : Adj[node])
		if (child != par)
		{
			dfs1(child, node);
			sizeOfSubTree[node] += sizeOfSubTree[child];
		}
}

int getCentroid(int node, int par)
{
	for (auto child : Adj[node])
		if (child != par)
			if (sizeOfSubTree[child] > currentTreeSize / 2)
				return getCentroid(child, node);
	return node;
}

void decompose(int node, char rank)
{
	if (rank > 'Z')
	{
		cout << "Impossible\n";
		exit(0);
	}
	currentTreeSize = 0;
	dfs1(node, node);
	int centroid = getCentroid(node, node);
	db(node, centroid, rank);
	ans[centroid] = rank;
	for (auto child : Adj[centroid])
	{
		Adj[child].erase(centroid);
		decompose(child, rank + 1);
	}
}

void solve()
{
	cin >> n;
	for (int i = 1; i < n; ++i)
	{
		cin >> u >> v;
		--u;
		--v;
		Adj[u].insert(v);
		Adj[v].insert(u);
	}
	decompose(0, 'A');
	for (int i = 0; i < n; ++i)
		cout << ans[i] << ' ';
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