//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
#ifdef Debug
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
vector<int> Lazy(4 * nax), St(4 * nax), a(nax);
int n;
vector<bool> isLazy(4 * nax);

int build(int node, int start, int end)
{
	if (start == end)
		return St[node] = a[start];
	int mid = (start + end) / 2;
	return St[node] = max(build(2 * node, start, mid), build(2 * node + 1, mid + 1, end));
}

void prop(int node, int start, int end)
{
	if (isLazy[node])
	{
		isLazy[node] = false;
		St[node] = max(St[node], Lazy[node]);
		if (start != end)
		{
			Lazy[2 * node] = max(Lazy[2 * node], Lazy[node]);
			Lazy[2 * node + 1] = max(Lazy[2 * node + 1], Lazy[node]);
			isLazy[2 * node] = true;
			isLazy[2 * node + 1] = true;
		}
		Lazy[node] = 0;
	}
}

void pupdate(int node, int start, int end, int pos, int nVal)
{
	if (start > end)
		return;
	prop(node, start, end);
	if (start == end)
	{
		St[node] = nVal;
		return;
	}
	int mid = (start + end) / 2;
	if (pos <= mid)
		pupdate(2 * node, start, mid, pos, nVal);
	else
		pupdate(2 * node + 1, mid + 1, end, pos, nVal);
	St[node] = max(St[2 * node], St[2 * node + 1]);
}

void rupdate(int node, int start, int end, int x)
{
	isLazy[node] = true;
	Lazy[node] = x;
}

int query(int node, int start, int end, int pos)
{
	if (start > end)
		return 0;
	prop(node, start, end);
	if (start == end)
		return St[node];
	int mid = (start + end) / 2;
	if (pos <= mid)
		return query(2 * node, start, mid, pos);
	return query(2 * node + 1, mid + 1, end, pos);
}

void solve()
{
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	build(1, 0, n - 1);
	int q, ch, p, x;
	cin >> q;
	while (q--)
	{
		cin >> ch;
		if (ch == 1)
		{
			cin >> p >> x;
			--p;
			pupdate(1, 0, n - 1, p, x);
		}
		else
		{
			cin >> x;
			rupdate(1, 0, n - 1, x);
		}
	}
	for (int i = 0; i < n; ++i)
		cout << query(1, 0, n - 1, i) << ' ';
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
#ifdef TIME
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}