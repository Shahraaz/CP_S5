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

vector<ll> a;
ll tree[4 * nax];
int n, m, l;

void build(int node, int left, int right)
{
	if (left == right)
	{
		tree[node] = a[left] > l;
		db(node, tree[node], a[left]);
		return;
	}
	int mid = (left + right) / 2;
	build(2 * node, left, mid);
	build(2 * node + 1, mid + 1, right);
	tree[node] = tree[2 * node] + tree[2 * node + 1];
	if (mid + 1 < n)
		if (a[mid] > l && a[mid + 1] > l)
			tree[node]--;
	db(node, tree[node]);
}

void update(int node, int left, int right, int pos, int dx)
{
	if (left == right)
	{
		a[left] += dx;
		tree[node] = a[left] > l;
		pc(a);
		return;
	}
	int mid = (left + right) / 2;
	if (mid >= pos)
		update(2 * node, left, mid, pos, dx);
	else
		update(2 * node + 1, mid + 1, right, pos, dx);
	tree[node] = tree[2 * node] + tree[2 * node + 1];
	if (mid + 1 < n)
		if (a[mid] > l && a[mid + 1] > l)
			tree[node]--;
	db(left, right, node, tree[node]);
}

void solve(int caseNo)
{
	cin >> n >> m >> l;
	a.resize(n);
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	build(1, 0, n - 1);
	while (m--)
	{
		int q;
		cin >> q;
		if (q == 0)
		{
			cout << tree[1] << '\n';
		}
		else
		{
			int p, dx;
			cin >> p >> dx;
			--p;
			update(1, 0, n - 1, p, dx);
		}
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
#ifdef TIME
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}