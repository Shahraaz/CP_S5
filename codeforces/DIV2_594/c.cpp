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
int a[20][20];
int res = 0;
vector<string> tot;
void solve(int i, int j, int n, int m)
{
	if (i >= n + 2)
		return;
	if (i == n + 1)
	{
		for (int i1 = 1; i1 <= n; ++i1)
			for (int j1 = 1; j1 <= m; ++j1)
			{
				int cnt = 0;
				if (i1 > 1)
					if (a[i1][j1] == a[i1 - 1][j1])
						cnt += 1;
				if (j1 > 1)
					if (a[i1][j1] == a[i1][j1 - 1])
						cnt += 1;
				if (i1 < n)
					if (a[i1][j1] == a[i1 + 1][j1])
						cnt += 1;
				if (j1 < m)
					if (a[i1][j1] == a[i1][j1 + 1])
						cnt += 1;
				if (cnt > 1)
					return;
			}
		res++;
		string s;
		for (int i1 = 1; i1 <= n; ++i1)
		{
			for (int j1 = 1; j1 <= m; ++j1)
			{
				s += a[i1][j1] + '0';
			}
			s += ' ';
		}
		s += '\n';
		tot.pb(s);
	}
	if (j == m)
	{
		a[i][j] = 0;
		solve(i + 1, 1, n, m);
		a[i][j] = 1;
		solve(i + 1, 1, n, m);
		return;
	}
	a[i][j] = 0;
	solve(i, j + 1, n, m);
	a[i][j] = 1;
	solve(i, j + 1, n, m);
}

void solve()
{
	int n, m;
	cin >> n >> m;
	for (int i = 0; i <= n; ++i)
		a[i][0] = -1;
	for (int i = 0; i <= m; ++i)
		a[0][i] = -1;
	solve(1, 1, n, m);
	sort(tot.begin(), tot.end());
	tot.erase(unique(tot.begin(), tot.end()), tot.end());
	// pc(tot);
	cout << tot.size() << '\n';
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