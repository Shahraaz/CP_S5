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
	while (*name == ',' || *name == ' ')
		name++;
	std::cerr << name << " { ";
	for (const auto &v : arg)
		cerr << v << ' ';
	cerr << " }\n";
}
template <typename Arg1, typename... Args>
void PC(const char *names, Arg1 &&arg1, Args &&... args)
{
	while (*names == ',' || *names == ' ')
		names++;
	const char *comma = strchr(names, ',');
	std::cerr.write(names, comma - names) << " { ";
	for (const auto &v : arg1)
		cerr << v << ' ';
	cerr << " }\n";
	PC(comma, args...);
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
auto TimeStart = chrono::steady_clock::now();

const int nax = 2e5 + 10, mod = 1000000007;
int n, m, a[nax], st[nax], en[nax], depth[nax], t;
vector<int> G[nax];

void dfs(int node, int par)
{
	st[node] = ++t;
	depth[node] = depth[par] + 1;
	for (auto child : G[node])
		if (child != par)
			dfs(child, node);
	en[node] = t;
}

ll Query(ll *ft, int b)
{
	ll sum = 0;
	for (; b; b -= (b & (-b)))
		sum += ft[b];
	return sum;
}

void Update(ll *ft, int k, ll v)
{
	for (; k < nax; k += (k & (-k)))
		ft[k] += v;
}

struct range_bit
{
	ll B1[nax], B2[nax];
	ll query(int b)
	{
		return Query(B1, b) * b - Query(B2, b);
	}
	ll rangeQuery(int i, int j)
	{
		return query(j) - query(i - 1);
	}
	void range_update(int i, int j, ll val)
	{
		Update(B1, i, val);
		Update(B1, j + 1, -val);
		Update(B2, i, val * (i - 1));
		Update(B2, j + 1, -val * j);
	}
} odd, even;

void update(int x, int val)
{
	if (depth[x] % 2 == 0)
		val *= -1;
	odd.range_update(st[x], en[x], val);
	even.range_update(st[x], en[x], -val);
}

int get(int x)
{
	if (depth[x] & 1)
		return odd.rangeQuery(st[x], st[x]);
	return even.rangeQuery(st[x], st[x]);
}

void solve(int caseNo)
{
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	int u, v;
	for (int i = 0; i < n - 1; ++i)
	{
		cin >> u >> v;
		G[u].pb(v);
		G[v].pb(u);
	}
	dfs(1, 1);
	while (m--)
	{
		int type;
		cin >> type;
		switch (type)
		{
		case 1:
			int x, val;
			cin >> x >> val;
			update(x, val);
			break;

		default:
			cin >> x;
			cout << a[x] + get(x) << '\n';
			break;
		}
	}
}

int main()
{
#ifndef WIN32
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#endif
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	for (int i = 0; i < t; ++i)
		solve(i);
#ifdef TIME
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}