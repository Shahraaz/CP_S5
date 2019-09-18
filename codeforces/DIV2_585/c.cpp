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
	int n;
	cin >> n;
	string s, t;
	cin >> s >> t;
	deque<int> ab, ba;
	for (int i = 0; i < n; ++i)
		if (s[i] == 'a' && t[i] == 'b')
			ab.pb(i);
		else if (s[i] == 'b' && t[i] == 'a')
			ba.pb(i);
	if (n == 1)
	{
		if (ab.size() || ba.size())
			cout << -1 << '\n';
		else
			cout << "0\n";
		return;
	}
	vector<pair<int, int>> ret;
	pc(ab);
	pc(ba);
	while (ab.size() > 1)
	{
		auto one = ab.front();
		ab.pop_front();
		auto two = ab.front();
		ab.pop_front();
		ret.push_back({one, two});
	}
	while (ba.size() > 1)
	{
		auto one = ba.front();
		ba.pop_front();
		auto two = ba.front();
		ba.pop_front();
		ret.push_back({one, two});
	}
	if (ab.size())
	{
		auto one = ab.front();
		ab.pop_front();
		ret.push_back({one, one});
		if (ba.size())
		{
			auto two = ba.front();
			ba.pop_front();
			ret.push_back({one, two});
		}
		else
		{
			cout << -1 << '\n';
			return;
		}
	}
	if (ba.size())
	{
		cout << -1 << '\n';
		return;
	}
	cout << ret.size() << '\n';
	for (auto p : ret)
		cout << p.f + 1 << ' ' << p.s + 1 << '\n';
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
	cin >> t;
	flush(cout);
#endif
	return 0;
}