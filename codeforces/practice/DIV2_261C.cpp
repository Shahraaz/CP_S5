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
const long long mod = 1000000007;
auto TimeStart = chrono::steady_clock::now();

const int nax = 1e3 + 10;

int ans[nax][nax];

void solve()
{
	int n, k, d;
	cin >> n >> k >> d;
	// vector<int> N(n, n), L(k, k), D(d, d);
	// pc(N, L, D);
	ll temp = 1;
	bool check = false;
	for (int i = 0; i < d; ++i)
	{
		temp *= k;
		if (temp >= n)
		{
			check = true;
			break;
		}
	}
	if (!check)
	{
		cout << "-1\n";
		return;
	}
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 0; j < d; ++j)
			ans[i][j] = ans[i - 1][j];
		for (int j = d - 1; j >= 0; --j)
		{
			ans[i][j] = (ans[i][j] + 1) % k;
			if (ans[i][j] == 0)
				break;
		}
	}
	for (int i = 0; i < d; ++i)
	{
		for (int j = 0; j < n; ++j)
			cout << ans[j][i] + 1 << ' ';
		cout << '\n';
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
	while (t--)
		solve();
#ifdef WIN32
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}