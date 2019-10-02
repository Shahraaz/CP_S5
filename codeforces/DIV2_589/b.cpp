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
int status[1001][10001];
int status2[1001][10001];
void solve()
{
	int h, w;
	cin >> h >> w;
	for (int i = 0; i < h; ++i)
	{
		int x;
		cin >> x;
		for (int j = 0; j < x; ++j)
			status[i][j] = 1; // Filled
		status[i][x] = 2;
	}
	for (int i = 0; i < w; ++i)
	{
		int x;
		cin >> x;
		for (int j = 0; j < x; ++j)
			status2[j][i] = 1; // Filled
		status2[x][i] = 2;
	}
	ll res = 1;
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			if (status[i][j] == 0)
			{
				if (status2[i][j] == 0)
				{
					res = (res * 2) % mod;
				}
			}
			else if (status[i][j] == 1)
			{
				if (status2[i][j] == 0)
				{
					// res = (res * 2) % mod;
				}
				else if (status2[i][j] == 2)
					res = 0;
			}
			else
			{
				if (status2[i][j] == 0)
				{
					// res = (res * 2) % mod;
				}
				else if (status2[i][j] == 1)
					res = 0;
			}
		}
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
	flush(cout);
#endif
	return 0;
}