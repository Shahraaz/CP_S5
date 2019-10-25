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
vector<pair<int, int>> v;
int n;
ll L;

bool solve(ll mid, int zz)
{
	priority_queue<int> Q;
	for (int i = 0; i < n; ++i)
		if (v[i].s >= mid)
			Q.push(v[i].f);
	if (Q.size() >= (n + 1) / 2)
	{
		ll cost = 0, k = n + 1;
		k /= 2;
		while (k--)
		{
			auto top = Q.top();
			Q.pop();
			cost += max(0LL, mid - top);
		}
		if (cost <= L)
			return true;
	}
	return false;
}

void solve(int caseNo)
{
	cin >> n >> L;
	v.resize(n);
	for (auto &s : v)
	{
		cin >> s.f >> s.s;
		L -= s.f;
	}
	ll res = 0, low = 0, high = 1e15;
	while (low <= high)
	{
		ll mid = (low + high) / 2;
		if (solve(mid, 0))
		{
			low = mid + 1;
			res = mid;
		}
		else
			high = mid - 1;
	}
	cout << res << '\n';
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
#ifdef TIME
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}