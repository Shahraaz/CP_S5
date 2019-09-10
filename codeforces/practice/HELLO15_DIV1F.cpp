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
int n, sizeOfSubTree[nax], currentSize;
map<pair<int, int>, int> Wt;

void dfs1(int node, int par)
{
	currentSize++;
	sizeOfSubTree[node] = 1;
	// db(node);
	// pc(Adj[node]);
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
			if (sizeOfSubTree[child] > currentSize / 2)
				return getCentroid(child, node);
	return node;
}

int root, centroidPar[nax];
map<int, ll> Dist[nax];
vector<ll> Search[nax];
void decompose(int node, int par)
{
	currentSize = 0;
	dfs1(node, node);
	int centroid = getCentroid(node, par);
	// db(node, centroid, currentSize);
	centroidPar[centroid] = par;
	if (par == -1)
	{
		centroidPar[centroid] = centroid;
		root = centroid;
	}
	Search[centroid].pb(0);
	Dist[centroid][centroid] = 0;
	for (auto child : Adj[centroid])
		if (child != par)
		{
			Adj[child].erase(centroid);
			decompose(child, centroid);
			ll temp = Wt[{child, centroid}];
			for (auto dist : Dist[child])
			{
				Dist[centroid][dist.f] = dist.s + temp;
				Dist[dist.f][centroid] = dist.s + temp;
				Search[centroid].pb({dist.s + temp});
			}
		}
	sort(Search[centroid].begin(), Search[centroid].end());
}

ll query(int node, ll length)
{
	int curr = node, prev = -1;
	ll ret = 0, dist, prevtemp;
	db("Query", node);
	while (true)
	{
		dist = Dist[curr][node];
		ll temp = length - dist;
		db(curr, dist, temp, length);
		// pc(Search[curr]);
		if (temp < 0)
			break;
		ret += upper_bound(Search[curr].begin(), Search[curr].end(), temp) - Search[curr].begin();
		// ret--;
		// Decrease the overcount
		// ??????? How ????????????????????????????
		// dont know ?
		// Have to figure it out
		// ll diff = temp - prevtemp;
		// db(diff, prevtemp, temp);
		db(ret);
		if (prev != -1)
			ret -= upper_bound(Search[prev].begin(), Search[prev].end(), temp - Dist[curr][prev]) - Search[prev].begin();
		db(ret);
		int par = centroidPar[curr];
		if (par == curr)
			break;
		prev = curr;
		// prevtemp = temp;
		curr = par;
	}
	return ret;
}

void solve()
{
	int u, v, w, q;
	cin >> n >> q;
	for (int i = 1; i < n; ++i)
	{
		cin >> u >> v >> w;
		--u;
		--v;
		Wt[{u, v}] = w;
		Wt[{v, u}] = w;
		// db(u, v);
		Adj[u].insert(v);
		Adj[v].insert(u);
	}
	decompose(0, -1);

	ll l;
	while (q--)
	{
		cin >> u >> l;
		cout << query(u - 1, l) << '\n';
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