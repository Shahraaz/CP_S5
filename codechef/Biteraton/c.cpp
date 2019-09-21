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

int _n = 1e6 + 10;
vector<int> Fact(_n), Inv(_n);
const int kmod = 1000000007;

int mul(int a, int b, int mod = kmod)
{
	return (long long)a * b % mod;
}

int power(int base, int index, int mod = kmod)
{
	if (index == 0)
		return 1;
	int temp = power(base, index / 2, mod);
	temp = mul(temp, temp, mod);
	if (index & 1)
		temp = mul(temp, base, mod);
	return temp;
}

void pre()
{
	Fact[0] = 1;
	for (int i = 1; i < _n; ++i)
		Fact[i] = mul(Fact[i - 1], i);
	Inv[0] = 1;
	for (int i = 1; i < _n; ++i)
		Inv[i] = mul(Inv[i - 1], Fact[i]);
}

int ncr(int n, int r)
{
	if (n < 0 || r < 0 || n - r < 0)
		return 0;
	return mul(Fact[n], mul(Inv[r], Inv[n - r]));
}

void solve()
{
	int n;
	cin >> n;
	int res = Inv[n];
	cout << res << '\n';
	// cout << mul(res, power(Inv[n], mod - 2)) << '\n';
}

int main()
{
	pre();
	ios_base::sync_with_stdio(0);
	cin.tie(0);
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