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
int n, m;
vector<int> G[nax];
int Color[nax], visited, one, two, three;

void Exit()
{
	cout << -1 << '\n';
	exit(0);
}

void dfs(int node, int clr)
{
	visited++;
	Color[node] = clr;
	switch (clr)
	{
	case 1:
		one++;
		break;
	case 2:
		two++;
		break;
	case 3:
		three++;
		break;
	default:
		db("I am doing it");
		Exit();
		break;
	}
	for (auto child : G[node])
		if (Color[child] == 0) // Already Coloured
		{
			int takenClr[4];
			memset(takenClr, 0, sizeof(takenClr));
			for (auto grandChild : G[child])
				if (Color[grandChild] > 0)
					takenClr[Color[grandChild]] = 1;
			int val = -1;
			for (int i = 1; i <= 3; ++i)
				if (takenClr[i] == 0)
				{
					val = i;
					break;
				}
			dfs(child, val);
		}
}

void solve()
{
	cin >> n >> m;
	int u, v;
	for (size_t i = 0; i < m; i++)
	{
		cin >> u >> v;
		G[u].pb(v);
		G[v].pb(u);
	}
	dfs(1, 1);
	if (visited != n)
	{
		db("Visited",visited)
			Exit();
	}
	if (one == 0 || two == 0 || three == 0)
	{
		db("Cnt")
			Exit();
	}
	if (m != (one * two + two * three + one * three))
	{
		db("EDge")
			Exit();
	}
	for (int i = 1; i <= n; ++i)
		cout << Color[i] << ' ';
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
	flush(cout);
#endif
	return 0;
}