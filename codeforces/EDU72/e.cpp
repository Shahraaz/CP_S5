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

vector<vector<multiset<int>>> Seg(4 * nax);

void update(int node, int start, int end, int pos, int val)
{
	db(node, start, end, pos);
	if (start == end)
	{
		db("Clear")
			Seg[node]
				.clear();
		auto str = to_string(val);
		while (str.length() < 10)
			str = "0" + str;
		db("Clear");
		Seg[node] = vector<multiset<int>>(10);
		db("Clear", str.length(), str);
		for (int j = 0; j < 10; ++j)
			if (str[j] != '0')
				Seg[node][j].insert(val);
		db("After");
		return;
	}
	int mid = (start + end) / 2;
	if (pos <= mid)
		update(2 * node, start, mid, pos, val);
	else
		update(2 * node + 1, mid + 1, end, pos, val);
	db(Seg)
	Seg[node] = Seg[2 * node];
	Seg[node].resize(10);
	for (int j = 0; j < 10; ++j)
	{
		for (auto x : Seg[2 * node + 1][j])
			Seg[node][j].insert(x);
	}
}

vector<multiset<int>> query(int node, int start, int end, int qstart, int qend)
{
	vector<multiset<int>> ret(10);
	if (qend < start || qstart > end || start > end)
		return ret;
	if (qstart <= start && end <= qend)
		return Seg[node];
	int mid = (start + mid) / 2;
	ret = query(2 * node, start, mid, qstart, qend);
	auto r = query(2 * node + 1, mid + 1, end, qstart, qend);
	for (int j = 0; j < 10; ++j)
		for (auto x : r[j])
			ret[j].insert(x);
	return ret;
}

void solve()
{
	int n, m, x;
	cin >> n >> m;
	vector<string> SS;
	db("Start");
	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		update(1, 0, n - 1, i, x);
	}
	db("End");
	int q, u, v;
	while (m--)
	{
		cin >> q >> u >> v;
		if (q == 1)
		{
			update(1, 0, n - 1, u, v);
		}
		else
		{
			int r;
			cin >> r;
			auto q = query(1, 0, n - 1, v - 1, r - 1);
			int ans = INT_MAX;
			for (int i = 0; i < 10; ++i)
				if (q[i].size() > 2)
					ans = min(ans, *q[i].begin() + *(++q[i].begin()));
			if (ans == INT_MAX)
				cout << -1 << '\n';
			else
				cout << ans << '\n';
		}
	}
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