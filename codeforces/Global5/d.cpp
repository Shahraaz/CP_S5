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

const int nax = 4e5 + 10, mod = 1000000007;
int a[nax];

bool Listen(int start, int len)
{
	int maxCool = a[start];
	for (int i = start + 1; i < start + len; ++i)
	{
		if (2 * a[i] < maxCool)
			return false;
		maxCool = max(maxCool, a[i]);
	}
	return true;
}
int dp[nax];

void solve()
{
	int n, x;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		a[i] = a[i + n] = a[i + 2 * n] = a[i + 3 * n] = x;
	}
	// db(ans);
	for (int i = n - 1; i >= 0; --i)
	{
		int start = 2, end = 2 * n + 1;
		if (i != n - 1)
			if (2 * a[i + 1] < a[i])
			{
				dp[i] = 1;
				continue;
			}
			else
			{
				end = dp[i + 1] + 1;
			}
		int ans = 1;
		while (start <= end)
		{
			int mid = (start + end) / 2;
			if (Listen(i, mid))
			{
				start = mid + 1;
				ans = mid;
			}
			else
				end = mid - 1;
		}
		dp[i] = ans;
		if (ans == (2 * n + 1))
			dp[i] = -1;
	}
	for (int i = 0; i < n; ++i)
		cout << dp[i] << ' ';
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