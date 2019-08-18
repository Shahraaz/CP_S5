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

const int nax = 2e5 + 10;

int powmod(int base, ll index, int mod)
{
	if (index == 0)
		return 1;
	int temp = powmod(base, index / 2, mod);
	temp = ((ll)temp * temp) % mod;
	if (index & 1)
		temp = ((ll)temp * base) % mod;
	return temp;
}

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int solve(int a, int m, int b)
{
	a %= m;
	b %= m;
	if (b == 1)
		return 0;
	ll t = 1, cnt = 0;
	db("Point1");
	for (int g = gcd(a, m); g != 1; g = gcd(a, m))
	{
		if (b % g)
			return -1;
		m /= g;
		b /= g;
		t = t * a / g % m;
		++cnt;
		if (b == t)
			return cnt;
	}
	db("Point2");
	map<int, int> hash;
	int n = sqrt(m) + 1;
	ll base = b;
	for (int i = 0; i < m; ++i)
	{
		hash[base] = i;
		base = base * a % m;
	}
	base = powmod(a, n, mod);
	ll now = t;
	db("Point3");
	for (int i = 0; i <= m + 1; ++i)
	{
		now = now * base % mod;
		if (hash.count(now))
			return i * n - hash[now] + cnt;
	}
	return -1;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	int x, z, k;
	while (cin >> x >> z >> k)
	{
		int ans = solve(x, z, k);
		if (x == 0 && k == 0 && z == 0)
			break;
		if (ans == -1)
			cout << "No Solution\n";
		else
			cout << ans << '\n';
	}
#ifdef WIN32
	cerr
		<< "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}