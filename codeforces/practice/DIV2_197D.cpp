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

const int nax = (1 << 17) + 10, mod = 1000000007;
int n, m;
int base[nax], tree[4 * nax], isOr[20];
bool done = false;

void build(int node, int start, int end, int level)
{
	if (start == end)
	{
		tree[node] = base[start];
		if (!done)
		{
			done = true;
			bool a = true;
			for (int i = level - 1; i >= 0; --i)
			{
				isOr[i] = a;
				a = !a;
			}
		}
		return;
	}
	int mid = (start + end) / 2;
	build(2 * node, start, mid, level + 1);
	build(2 * node + 1, mid + 1, end, level + 1);
	if (isOr[level])
		tree[node] = tree[2 * node] | tree[2 * node + 1];
	else
		tree[node] = tree[2 * node] ^ tree[2 * node + 1];
}

void update(int node, int start, int end, int pos, int val, int level)
{
	if (start == end)
	{
		tree[node] = val;
		return;
	}
	int mid = (start + end) / 2;
	if (pos <= mid)
		update(2 * node, start, mid, pos, val, level + 1);
	else
		update(2 * node + 1, mid + 1, end, pos, val, level + 1);
	if (isOr[level])
		tree[node] = tree[2 * node] | tree[2 * node + 1];
	else
		tree[node] = tree[2 * node] ^ tree[2 * node + 1];
}

void solve(int caseNo)
{
	cin >> n >> m;
	n = 1 << n;
	for (int i = 0; i < n; ++i)
		cin >> base[i];
	int pos, val;
	build(1, 0, n - 1, 0);
	while (m--)
	{
		cin >> pos >> val;
		pos--;
		update(1, 0, n - 1, pos, val, 0);
		cout << tree[1] << '\n';
	}
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