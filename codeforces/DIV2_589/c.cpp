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

vector<ll> find_fact(ll n)
{
	vector<ll> ret;
	for (ll i = 2; i * i <= n; ++i)
	{
		if (n % i == 0)
		{
			ret.pb(i);
			while (n % i == 0)
			{
				n /= i;
			}
		}
	}
	if (n > 1)
		ret.pb(n);
	sort(ret.begin(), ret.end());
	return ret;
}

vector<ll> find_fact2(ll n)
{
	vector<ll> ret;
	for (ll i = 1; i * i <= n; ++i)
	{
		if (n % i == 0)
		{
			if (n == i * i)
				ret.pb(i);
			else
			{
				ret.pb(i);
				ret.pb(n / i);
			}
		}
	}
	// if (n > 1)
	// ret.pb(n);
	sort(ret.begin(), ret.end());
	return ret;
}
ll gcd(ll a, ll b)
{
	// db(a, b);
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

ll power(ll base, ll index)
{
	if (index == 0)
		return 1;
	ll temp = power(base, index / 2);
	temp *= temp;
	temp %= mod;
	if (index & 1)
		temp *= base;
	return temp % mod;
}

void solve()
{
	ll x, n;
	cin >> x >> n;
	// if(n==1)
	auto f = find_fact(x);
	// if (n < f[0])
	// {
	// 	cout << 0 << '\n';
	// 	return;
	// }
	pc(f);
	ll check = 1;
	for (auto &c : f)
	{
		db(c, check);
		// int cnt = logl(n) / logl(c);
		// if(cnt + 1e9 > )
		int cnt = 0;
		ll base = 1;
		while (base <= n / c)
		{
			base *= c;
			cnt++;
			/* code */
		}

		ll temp = c;
		cerr << fixed << setprecision(30);
		db(c, cnt, logl(n) / logl(c));
		for (ll i = 1; i <= cnt; i++)
		{
			ll temp2 = power(c % mod, n / temp);
			check = (check * temp2) % mod;
			temp *= c;
		}
		db(c, check);
	}
	cout << check;
	db(check);
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