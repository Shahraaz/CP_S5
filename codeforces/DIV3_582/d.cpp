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

void solve()
{
	int n, k;
	cin >> n >> k;
	vector<int> Level(n);
	map<int, vector<int>> Step;
	set<int> SSSS;
	for (int i = 0; i < n; ++i)
	{
		cin >> Level[i];
		Step[Level[i]].pb(0);
	}
	vector<bool> SS(n);
	auto oper = Level;
	for (int j = 1; j < 30; ++j)
		for (int i = 0; i < n; ++i)
		{
			oper[i] /= 2;
			if (oper[i] == 0)
			{
				if (!SS[i])
					Step[oper[i]].pb(j);
				SS[i] = 1;
			}
			else
			{
				Step[oper[i]].pb(j);
			}
		}
	ll ans = LLONG_MAX;
	for (auto V : Step)
	{
		db(V.f);
		pc(V.s);
		if (V.s.size() >= k)
		{
			ll temp = 0;
			sort(V.s.begin(), V.s.end());
			for (int i = 0; i < k; ++i)
				temp += V.s[i];
			ans = min(ans, temp);
		}
	}
	cout << ans;
}

int main()
{
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
#endif
	return 0;
}