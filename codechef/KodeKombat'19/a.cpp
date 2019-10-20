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

int cnt = 0;
void solve()
{
	// cout << cnt++ << '\n';
	// srand(time(NULL));
	int n;
	cin >> n;
	// n = rand() % int(10) + 1;

	vector<int> a(n);
	set<pair<int, int>> right;
	for (auto &x : a)
	{
		cin >> x;
		// x = rand() % int(1e6) + 1;
		right.insert({x, cnt++});
	}
	ll val = LLONG_MAX;
	int lmin = INT_MAX;
	for (int i = 0; i < n; ++i)
	{
		right.erase({a[i], i});
		if (i != 0)
		{
			auto it1 = lmin;
			if (it1 < a[i])
			{
				auto it2 = right.upper_bound({a[i], INT_MAX});
				if (it2 != right.end())
				{
					// db(it1, a[i], *it2, val);
					val = min(val, (ll)it1 * a[i] * (it2->f));
					// db(it1, a[i], *it2, val);
				}
			}
		}
		// left.insert(a[i]);
		lmin = min(lmin, a[i]);
	}
	if (val == LLONG_MAX)
		val = -1;
	cout << val << '\n';
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