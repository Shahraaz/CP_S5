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

const int nax = 2e5 + 10;
int Cnt[nax];

vector<int> factors(int x)
{
	vector<int> ret;
	for (int i = 1; i * i <= x; ++i)
		if (x % i == 0)
		{
			if (x != 1)
				ret.pb(i);
			if (x / i != i)
				ret.pb(x / i);
		}
	sort(ret.begin(), ret.end());
	// db(x);
	// pc(ret);
	// ret.pop_back();
	return ret;
}

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

void solve()
{
	int n, x;
	cin >> n;
	vector<int> b(n), a(n);
	map<int, int> hash;
	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		a[i] = x;
		auto ret = factors(x);
		for (auto fact : ret)
			Cnt[fact]++;
	}
	ll output = 0, gar = 0;
	sort(a.begin(), a.end());
	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		b[i] = x;
		// output += n - Count[x];
		int out = 0;
		auto ret = factors(x);
		// ret.pop_back();
		for (auto fact : ret)
			out += upper_bound(a.begin(), a.end(), fact) - lower_bound(a.begin(), a.end(), fact);
		db(b[i], out);
		out += Cnt[x];
		db(out, n - out);
		output += n - out;
	}
	cout << output << '\n';
	output = 0;
	for (int i = 0; i < n; ++i)
	{
		int out = 0;
		for (int j = 0; j < n; ++j)
			if (gcd(a[j], b[i]) <= 1)
				output++, out++;
		db(b[i], out);
	}
	cout << output << '\n';
	// factors(20);
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