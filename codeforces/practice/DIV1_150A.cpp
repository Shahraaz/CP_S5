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

const int nax = 1e5 + 10, mod = 1000000007, m = 1 << 20;
int a[nax], nxt[20][nax], ans;
int n;
bool f[m];

void work(int k)
{
	if (f[a[k]] == 0)
		ans++;
	f[a[k]] = 1;
	int cur = a[k], idx = k;
	while (true)
	{
		int next = n + 1, store = 0;
		for (int j = 0; j < 20; ++j)
			if (cur & (1 << j))
				;
			else
			{
				if (nxt[j][idx] < next)
				{
					next = nxt[j][idx];
					store = a[next];
				}
			}
		if (next == n + 1)
			break;
		idx = next;
		cur = cur | store;
		if (f[cur] == 0)
			ans++;
		f[cur] = 1;
	}
}

void solve(int caseNo)
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	for (int i = n; i > 0; --i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (a[i] & (1 << j))
				nxt[j][i] = i;
			else
				nxt[j][i] = nxt[j][i + 1];
			if (nxt[j][i] == 0)
				nxt[j][i] = n + 1;
		}
	}
	for (int i = 1; i <= n; ++i)
		work(i);
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