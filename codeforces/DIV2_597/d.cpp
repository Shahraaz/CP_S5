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

const int nax = 2e3 + 10, mod = 1000000007;
vector<pair<int, long long>> G[nax];
int x[nax], y[nax], c[nax];
ll k[nax];
int n;
bool vis[nax], Shine[nax];
using elem = pair<ll, pair<int, int>>;
ll dist[nax];

void solve(int caseNo)
{
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> x[i] >> y[i];
	for (int i = 0; i < n; ++i)
		cin >> c[i];
	for (int i = 0; i < n; ++i)
		cin >> k[i];
	priority_queue<elem, vector<elem>, greater<elem>> Q;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (i == j)
			{
				Q.push({c[i], {i, i}});
				dist[i] = c[i];
			}
			else
				G[i].pb({j, (k[i] + k[j]) * (abs(x[i] - x[j]) + abs(y[i] - y[j]))});
	int a, b;
	a = b = 0;
	ll res = 0;
	vector<pair<int, int>> Conn;
	while (!Q.empty())
	{
		auto top = Q.top();
		Q.pop();
		if (vis[top.s.f])
			continue;
		vis[top.s.f] = true;
		res += top.f;
		if (top.s.f == top.s.s)
		{
			a++;
			Shine[top.s.f] = true;
		}
		else
		{
			b++;
			Conn.pb({top.s.f, top.s.s});
		}
		for (auto child : G[top.s.f])
		{
			if (vis[child.f])
				continue;
			if (dist[child.f] > child.s)
			{
				dist[child.f] = child.s;
				Q.push({child.s, {child.f, top.s.f}});
			}
		}
	}
	cout << res << '\n';
	cout << a << '\n';
	for (int i = 0; i < n; ++i)
		if (Shine[i])
			cout << i + 1 << ' ';
	cout << '\n';
	cout << b << '\n';
	for (auto Elem : Conn)
		cout << Elem.f + 1 << ' ' << Elem.s + 1 << '\n';
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