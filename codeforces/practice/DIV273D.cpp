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

const int nax = 1e6 + 10;

int f[nax], f1[nax];

int add(int a, int b)
{
	a += b;
	if (a >= mod)
		a -= mod;
	return a;
}

void solve()
{
	int r, g, sum, level;
	cin >> r >> g;
	f[0] = 1;
	for (level = 1, sum = 1; sum <= r + g; sum += ++level)
	{
		for (int i = 0; i <= sum; ++i)
		{
			f1[i] = f[i];
			if (i >= level)
				f1[i] = add(f1[i], f[i - level]);
		}
		for (int i = 0; i <= sum; ++i)
		{
			f[i] = f1[i];
			db(level, i, f[i]);
		}
	}
	int ans = 0;
	sum -= level;
	db(sum);
	for (int i = 0; i <= sum; ++i)
	{
		db(i, r, sum - i, g, f[i]);
		if (i <= r && (sum - i) <= g)
		{
			ans = add(ans, f[i]);
		}
	}
	cout << ans << '\n';
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