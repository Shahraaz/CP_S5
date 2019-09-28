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

int w[nax], p[nax], v[nax];
int n;
map<int, ll> Dp[nax];

ll solve(int index, int time)
{
	if (index == n)
		return 0;
	int CustLeaveTime = w[index];
	if (time > CustLeaveTime) // He Leaves
	{
		return solve(index + 1, time);
	}
	ll ret = solve(index + 1, time); // he leaves
	ret = max(ret, v[index] + solve(index + 1, time + p[index]));
	auto ti = Dp[index].lower_bound(time);
	if (ti != Dp[index].end())
		ret = max(ret, ti->s);
	return Dp[index][time] = ret;
}

void solve()
{
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> w[i] >> p[i] >> v[i];
		Dp[i].clear();
	}
	cout << solve(0, 0) << '\n';
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