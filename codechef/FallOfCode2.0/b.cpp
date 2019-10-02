//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
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
ll Val[nax];

int mul(int a, int b)
{
	return (ll)a * b % mod;
}

void add_self(ll &a, int b)
{
	a += b;
	if (a >= mod)
		a -= mod;
}

void pre()
{
	int a[4];
	a[0] = 1;
	a[1] = 2;
	a[2] = 3;
	a[3] = 4;
	for (int i = 1; i < nax; ++i)
	{
		Val[i] = 1;
		for (int j = 0; j < 4; ++j)
			Val[i] = mul(Val[i], a[j]);
		for (int j = 0; j < 4; ++j)
			a[j]++;
		add_self(Val[i], Val[i - 1]);
	}
}

void solve()
{
	int l, r;
	cin >> l >> r;
	cout << (Val[r] - Val[l - 1] + mod) % mod << '\n';
}

int main()
{
	pre();
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