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

const int nax = 3e5 + 10, mod = 1000000007;
int n, m;
using edge = pair<int, pair<int, int>>;
vector<edge> Edges;
map<int, int> dpSofar[nax];

void solve()
{
	cin >> n >> m;
	int u, v, w;
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v >> w;
		Edges.pb({w, {u, v}});
		// Edges.pb({w, {v, u}});
	}
	int res = 0;
	sort(Edges.begin(), Edges.end());
	pc(Edges);
	for (int i = m - 1; i >= 0; --i)
	{
		int start = Edges[i].s.f, End = Edges[i].s.s;
		int wr = Edges[i].f;
		auto it = dpSofar[End].upper_bound(wr);
		if (it != dpSofar[End].end())
			dpSofar[start][wr] = max(dpSofar[start][wr], it->s + 1);
		else
			dpSofar[start][wr] = max(1, dpSofar[start][wr]);
		it = dpSofar[start].upper_bound(wr);
		if (it != dpSofar[start].end())
			dpSofar[start][wr] = max(it->s, dpSofar[start][wr]);
		db(start, End, wr, dpSofar[start][wr]);
		res = max(res, dpSofar[start][wr]);
	}
	cout << res << '\n';
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
	while (t--)
		solve();
#ifdef WIN32
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}