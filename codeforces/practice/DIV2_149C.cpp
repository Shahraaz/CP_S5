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
using pii = pair<int, int>;
int f[] = {0, 0, 0, 1, 1, 1, -1, -1, -1};
int s[] = {1, -1, 0, 1, -1, 0, 1, -1, 0};

void solve(int caseNo)
{
	pair<int, int> src, dest;
	cin >> src.f >> src.s;
	cin >> dest.f >> dest.s;
	int n, r, a, b;
	cin >> n;
	set<pii> unBlocked, vis;
	map<pii, int> dist;
	while (n--)
	{
		cin >> r >> a >> b;
		for (int i = a; i <= b; ++i)
			unBlocked.insert({r, i});
	}
	dist[dest] = -1;
	dist[src] = 0;
	queue<pii> Q;
	Q.push(src);
	vis.insert(src);
	while (!Q.empty())
	{
		auto top = Q.front();
		Q.pop();
		for (int i = 0; i < 9; ++i)
		{
			pii pp = {top.f + f[i], top.s + s[i]};
			if (unBlocked.count(pp) && !vis.count(pp))
			{
				vis.insert(pp);
				dist[pp] = dist[top] + 1;
				Q.push(pp);
			}
		}
	}
	cout << dist[dest] << '\n';
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