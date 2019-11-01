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

const int nax = 2e5 + 10, mod = 100000000;
int k1, k2;
ll dp[101][101][2];

ll solve(int n1, int n2, bool way)
{
	if (n1 == 0 && n2 == 0)
		return 1;
	if (n1 == 0)
	{
		db(n1, n2, way, n2 <= k2 && !way);
		return n2 <= k2 && !way;
	}
	if (n2 == 0)
	{
		db(n1, n2, way, n1 <= k1 && way);
		return n1 <= k1 && way;
	}
	ll &ret = dp[n1][n2][way];
	if (ret >= 0)
		return ret;
	ret = 0;
	if (way)
	{
		int extra = min(n1, k1);
		for (int i = 1; i <= extra; ++i)
		{
			ret += solve(n1 - i, n2, 0);
			ret %= mod;
		}
	}
	else
	{
		int extra = min(n2, k2);
		for (int i = 1; i <= extra; ++i)
		{
			ret += solve(n1, n2 - i, 1);
			ret %= mod;
		}
	}
	db(n1, n2, way, ret);
	return ret;
}

void solve(int caseNo)
{
	int n1, n2;
	cin >> n1 >> n2 >> k1 >> k2;
	memset(dp, -1, sizeof dp);
	dp[0][0][0] = dp[0][0][1] = 1;
	cout << (solve(n1, n2, 0) + solve(n1, n2, 1)) % mod << '\n';
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