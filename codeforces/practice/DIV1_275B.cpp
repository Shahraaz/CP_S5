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

const int nax = 1e5 + 10, mod = 1000000007;

vector<int> tree(4 * nax, (1 << 30) - 1);

void update(int node, int start, int end, int pos, int val)
{
	if (start == end)
	{
		tree[node] = val;
		db(start, end, pos, val, node, tree[node]);
		return;
	}
	int mid = (start + end) / 2;
	if (mid <= pos)
		update(2 * node, start, mid, pos, val);
	else
		update(2 * node + 1, mid + 1, end, pos, val);
	tree[node] = tree[2 * node] & tree[2 * node + 1];
	db(start, end, pos, val, node, tree[node]);
}

void build(int node, int start, int end, vector<int> &a)
{
	if (start == end)
	{
		tree[node] = a[start];
		return;
	}
	int mid = (start + end) / 2;
	build(2 * node, start, mid, a);
	build(2 * node + 1, mid + 1, end, a);
	tree[node] = tree[2 * node] & tree[2 * node + 1];
	db(start, end, node, tree[node]);
}

int query(int node, int start, int end, int left, int right)
{
	if (start > end || start > right || end < left)
		return (1 << 30) - 1;
	if (left <= start && end <= right)
	{
		db(start, end, left, right, tree[node]);
		return tree[node];
	}
	int ret = (1 << 30) - 1;
	int mid = (start + end) / 2;
	ret = ret & query(2 * node, start, mid, left, right);
	ret = ret & query(2 * node + 1, mid + 1, end, left, right);
	db(start, end, left, right, ret);
	return ret;
}

void solve(int caseNo)
{
	int n, m, l, r, q;
	cin >> n >> m;
	// vector<Segtree> tree(32, Segtree(n));
	vector<vector<int>> tree(32, vector<int>(n + 1));
	vector<int> x, y, z;
	for (int i = 0; i < m; ++i)
	{
		cin >> l >> r >> q;
		--l, --r;
		x.pb(l);
		y.pb(r);
		z.pb(q);
		for (int j = 0; j <= 30; ++j)
			if (q & (1 << j))
			{
				tree[j][l]++;
				tree[j][r + 1]--;
			}
	}
	for (int i = 1; i < n; ++i)
		for (int j = 0; j <= 30; ++j)
			tree[j][i] += tree[j][i - 1];
	vector<int> Ok(n);
	for (int i = 0; i < n; ++i)
	{
		int res = 0;
		for (int j = 0; j <= 30; ++j)
			if (tree[j][i] > 0)
				res += 1 << j;
		Ok[i] = res;
	}
	build(1, 0, n - 1, Ok);
	pc(Ok);
	for (int i = 0; i < m; ++i)
	{
		l = x[i];
		r = y[i];
		q = z[i];
		int res = query(1, 0, n - 1, l, r);
		db(l, r, q, res);
		if (res != q)
		{
			cout << "NO\n";
			return;
		}
	}
	cout << "YES\n";
	for (int i = 0; i < n; ++i)
		cout << Ok[i] << ' ';
	cout << '\n';
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