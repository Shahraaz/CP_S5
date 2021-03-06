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

const int nax = 3e5 + 10, mod = 1000000007, LOG = 20;
int LogBase[nax], a[LOG][nax], ans[nax];

int getMin(int l, int r)
{
	int k = LogBase[r - l];
	return min(a[k][l], a[k][r - (1 << k)]);
}

void solve(int caseNo)
{
	int n;
	cin >> n;
	db("here");
	for (int i = 2; i <= n; ++i)
		LogBase[i] = LogBase[i / 2] + 1;
	db("here");
	for (int i = 0; i < n; ++i)
	{
		cin >> a[0][i];
		a[0][i + n + n] = a[0][i + n] = a[0][i];
	}
	db("here");
	for (int k = 0; k < LOG - 1; ++k)
		for (int i = 0; i + (1 << k) <= 3 * n; ++i)
			a[k + 1][i] = min(a[k][i], a[k][i + (1 << k)]);
	db("here");
	int mx = a[0][n - 1];
	ans[n - 1] = -1;
	for (int i = n; i < 3 * n; ++i)
	{
		if (2 * a[0][i] < mx)
		{
			ans[n - 1] = i - n + 1;
			break;
		}
		mx = max(mx, a[0][i]);
	}
	if (ans[n - 1] == -1)
	{
		for (int i = 0; i < n; ++i)
			cout << -1 << ' ';
		return;
	}
	for (int i = n - 2; i >= 0; --i)
	{
		int low = 1, high = ans[i + 1] + 1, Ans = 1;
		db(i, low, high);
		while (low <= high)
		{
			int mid = (low + high) / 2;
			int temp = getMin(i, i + mid);
			db(i, i + mid, temp);
			if (a[0][i] > 2 * temp)
				high = mid - 1;
			else
			{
				low = mid + 1;
				Ans = mid;
			}
		}
		ans[i] = Ans;
	}
	for (int i = 0; i < n; ++i)
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
	for (int i = 0; i < t; ++i)
		solve(i);
#ifdef WIN32
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}