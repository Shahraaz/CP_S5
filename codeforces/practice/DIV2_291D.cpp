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

const int nax = 2e5 + 10, LIMIT = 20;
int n, m, k;
int a[nax][5], sparse[5][nax][LIMIT];
int ans[5], Log[nax];

void build()
{
	Log[0] = Log[1] = 0;
	for (int i = 2; i < nax; ++i)
		Log[i] = Log[i / 2] + 1;
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
			sparse[i][j][0] = a[j][i];
		for (int K = 1; K < LIMIT; ++K)
			for (int l = 0; l + (1 << K) <= n; ++l)
				sparse[i][l][K] = max(sparse[i][l][K - 1], sparse[i][l + (1 << (K - 1))][K - 1]);
	}
}

int getMax(int idx, int left, int right)
{
	int K = Log[right - left];
	int ret = max(sparse[idx][left][K], sparse[idx][right - (1 << K)][K]);
	db(idx, left, right, ret, K);
	return ret;
}

bool check(int len)
{
	for (int i = 0; i + len <= n; ++i)
	{
		int l = i, r = i + len;
		ll cnt = 0;
		for (int j = 0; j < m; ++j)
			cnt += ans[j] = getMax(j, l, r);
		if (cnt <= k)
			return true;
	}
	return false;
}

void solve()
{
	cin >> n >> m >> k;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			cin >> a[i][j];
	build();
	int l, r, Ans = 0;
	l = 0;
	r = n;
	while (l <= r)
	{
		int mid = (l + r) / 2;
		if (check(mid))
		{
			l = mid + 1;
			Ans = max(Ans, mid);
		}
		else
		{
			r = mid - 1;
		}
	}
	check(Ans);
	db(Ans);
	if (Ans == 0)
		for (int i = 0; i < m; ++i)
			ans[i] = 0;
	for (int i = 0; i < m; ++i)
		cout << ans[i] << ' ';
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