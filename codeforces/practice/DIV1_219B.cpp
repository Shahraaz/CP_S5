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

const int nax = 50, mod = 1000000007;

int dp[50][50][50][50], A[nax][nax];

void solve(int caseNo)
{
	int n, m, q;
	cin >> n >> m >> q;
	string str;
	for (int i = 1; i <= n; ++i)
	{
		cin >> str;
		str = '$' + str;
		for (int j = 1; j <= m; ++j)
			A[i][j] = (A[i][j - 1] + 1) * (str[j] == '0');
	}
	for (int h = 1; h <= n; ++h)
		for (int w = 1; w <= m; ++w)
			for (int i = 1; i <= n - h + 1; ++i)
				for (int j = 1; j <= m - w + 1; ++j)
				{
					dp[i][i + h - 1][j][j + w - 1] = dp[i][i + h - 2][j][j + w - 1]
												   + dp[i][i + h - 1][j][j + w - 2]
												   - dp[i][i + h - 2][j][j + w - 2];
					for (int k = i + h - 1, C = w; k >= i; --k)
					{
						C = min(C, A[k][j + w - 1]);
						dp[i][i + h - 1][j][j + w - 1] += C;
					}
				}
	int a, b, c, d;
	while (q--)
	{
		cin >> a >> b >> c >> d;
		cout << dp[a][c][b][d] << '\n';
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
#ifdef WIN32
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}