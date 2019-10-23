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

struct Line
{
	mutable long long k, m;
	mutable function<const Line *()> succ;
	bool operator<(const Line &o) const
	{
		return k > o.k;
	}
	bool operator<(const long long &_p) const
	{
		const Line *s = succ();
		if (s == nullptr)
			return false;
		return (m + k * _p) < (s->m + s->k * _p);
	}
};

ostream &operator<<(ostream &out, const Line &p)
{
	out << "slope " << p.k << " constant " << p.m << ' ';
	return out;
}
//Max Query

struct lineContainer : multiset<Line, less<>>
{
	bool bad(iterator y)
	{
		auto z = next(y);
		if (y == begin())
		{
			if (z == end())
				return false;
			return y->k == z->k && y->m <= z->m;
		}
		auto x = prev(y);
		if (z == end())
			return y->k == x->k && y->m <= x->m;
		return 1.0L * (x->m - y->m) * (y->k - z->k) >= 1.0L * (y->k - x->k) * (z->m - y->m);
	}
	void add(long long k, long long m)
	{
		db("add", k, m);
		auto y = insert({k, m});
		y->succ = [=] { return next(y) == end() ? nullptr : &*(next(y)); };
		if (bad(y))
		{
			erase(y);
			return;
		}
		while (next(y) != end() && bad(next(y)))
			erase(next(y));
		while (y != begin() && bad(prev(y)))
			erase(prev(y));
	}
	long long query(long long x)
	{
		db("Query", x);
		auto l = lower_bound(x);
		return l->k * x + l->m;
	}
};

void solve(int caseNo)
{
	int n;
	cin >> n;
	// db("Here");
	lineContainer L;
	vector<pair<ll, pair<ll, ll>>> V(n);
	// db("Here");
	for (int i = 0; i < n; ++i)
		cin >> V[i].f >> V[i].s.f >> V[i].s.s;
	// db("Here");
	sort(V.begin(), V.end());
	L.add(0, 0);
	// db("Here");
	ll ans = 0;
	// db("Here");
	for (int i = 0; i < n; ++i)
	{
		ll x = V[i].f;
		ll y = V[i].s.f;
		ll a = V[i].s.s;
		ll f = L.query(y) + x * y - a;
		L.add(-x, f);
		ans = max(ans, f);
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
	for (int i = 0; i < t; ++i)
		solve(i);
#ifdef WIN32
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}