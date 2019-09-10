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
int n, u, v, w;
vector<pair<int, int>> Adj[nax];
int subTreeSize[nax];
bool computed[nax];
int curreNode;
vector<int> centroidParent;
map<int, ll> Dist[nax];

void dfs1(int node, int p)
{
	curreNode++;
	subTreeSize[node] = 1;
	for (auto child : Adj[node])
		if (child.f != p && !computed[child.f])
		{
			dfs1(child.f, node);
			subTreeSize[node] += subTreeSize[child.f];
		}
}

int getCentroid(int node, int p)
{
	for (auto child : Adj[node])
		if (child.f != p && !computed[child.f])
			if (subTreeSize[child.f] > curreNode / 2)
				return getCentroid(child.f, node);
	return node;
}

void decompose(int node, int p)
{
	db("Decompose", node);
	curreNode = 0;
	dfs1(node, p);
	int centroid = getCentroid(node, node);
	centroidParent[centroid] = p;
	if (p == -1)
		centroidParent[centroid] = centroid;
	queue<pair<int, ll>> Q;
	Q.push({centroid, 0});
	set<int> S;
	computed[centroid] = true;
	while (!Q.empty())
	{
		auto top = Q.front();
		Q.pop();
		if (S.count(top.f))
			continue;
		Dist[centroid][top.f] = top.s;
		S.insert(top.f);
		for (auto child : Adj[centroid])
			if (!computed[child.f])
				Q.push({child.f, top.s + child.s});
	}
	db(centroid);
	pc(Dist[centroid]);
	for (auto child : Adj[centroid])
		if (!computed[child.f])
			decompose(child.f, centroid);
}

int white[nax];
ll ans = 0;

priority_queue<pair<ll, int>> Q[nax];

void update(int node)
{
	white[node] = 1 - white[node];
	if (white[node])
	{
		int curr = node;
		while (true)
		{
			Q[curr].push({Dist[curr][node], node});
			if(Q[curr].size() > 1)
			{
				auto top = Q[curr].top();
				Q[curr].pop();
				ans = max(ans,Q[curr].top().f + top.f);
				Q[curr].push(top);
			}
			int par = centroidParent[curr];
			if (par == curr)
				break;
			curr = par;
		}
	}
	else
	{
		
	}
}

void solve()
{
	cin >> n;
	centroidParent = vector<int>(n);
	for (int i = 1; i < n; ++i)
	{
		cin >> u >> v >> w;
		--u;
		--v;
		Adj[u].pb({v, w});
		Adj[v].pb({u, w});
	}
	decompose(0, -1);
	pc(centroidParent);
	for (int i = 0; i < n; ++i)
		update(i);
	
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