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
vector<int> b, p;
int n, m, a;

bool solve(int len, ll &cost)
{
	ll bud = 0;
	cost = 0;
	for (int i = 0; i < len; ++i)
		if (p[i] > b[i + n - len])
			bud += p[i] - b[i + n - len];
	// db(bud, len, cost);
	return bud <= a;
}

void solve(int caseNo)
{
	cin >> n >> m >> a;
	b.resize(n);
	p.resize(m);
	for (auto &x : b)
		cin >> x;
	for (auto &x : p)
		cin >> x;
	sort(b.begin(), b.end());
	sort(p.begin(), p.end());
	pc(b, p);
	int low = 0, high = min(n, m);
	long long r, s;
	r = s = 0;
	while (low <= high)
	{
		int mid = (low + high) / 2;
		ll cost;
		if (solve(mid, cost))
		{
			low = mid + 1;
			r = mid;
			s = cost;
		}
		else
			high = mid - 1;
	}
	s = 0;
	for (int i = 0; i < r; ++i)
		s += p[i];
	cout << r << ' ' << max(0LL, s - a) << '\n';
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