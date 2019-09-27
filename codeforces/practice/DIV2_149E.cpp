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

struct Node
{
	long long val;
	Node(int one = 0) : val(one) {}
	Node operator+(const Node &rhs)
	{
		Node a = *this;
		a.val = a.val + rhs.val;
		return a;
	}
	Node operator-(const Node &rhs)
	{
		Node a = *this;
		a.val -= rhs.val;
		return a;
	}
};

ostream &operator<<(ostream &out, const Node &p)
{
	out << p.val;
	return out;
}
istream &operator>>(istream &in, Node &p)
{
	in >> p.val;
	return in;
}

struct Segtree
{
	vector<Node> Seg, Lazy;
	vector<Node> Base;
	vector<bool> isLazy;
	int n;
	Segtree(int n = 2e5)
	{
		this->n = n;
		Seg.resize(4 * n + 10);
		Lazy.resize(4 * n + 10);
		isLazy.resize(4 * n + 10);
	}
	void merge(Node &curr, Node &l, Node &r)
	{
		curr = l + r;
	}
	void propagate(int node, int L, int R)
	{
		if (isLazy[node])
		{
			isLazy[node] = false;
			Seg[node] = Node(R - L + 1) - Seg[node];
			if (L != R)
			{
				isLazy[2 * node] = !isLazy[2 * node];
				isLazy[2 * node + 1] = !isLazy[2 * node + 1];
			}
			// Lazy[node] = Node();
			isLazy[node] = false;
		}
	}
	void build(int node, int start, int end)
	{
		if (start == end)
		{
			Seg[node] = Base[start];
			return;
		}
		int mid = (start + end) / 2;
		build(2 * node, start, mid);
		build(2 * node + 1, mid + 1, end);
		merge(Seg[node], Seg[2 * node], Seg[2 * node + 1]);
	}
	void build(vector<Node> &Arr)
	{
		Base = Arr;
		n = Arr.size();
		Seg.resize(4 * n + 10);
		Lazy.resize(4 * n + 10);
		isLazy.resize(4 * n + 10);
		build(1, 0, n - 1);
	}
	Node Query(int node, int start, int end, int qstart, int qend)
	{
		propagate(node, start, end);
		if (qend < start || qstart > end || start > end)
			return Node();
		if (qstart <= start && end <= qend)
			return Seg[node];
		int mid = (start + end) / 2;
		Node l = Query(2 * node, start, mid, qstart, qend);
		Node r = Query(2 * node + 1, mid + 1, end, qstart, qend);
		Node ret;
		merge(ret, l, r);
		return ret;
	}
	Node qQuery(int node, int start, int end, int pos)
	{
		propagate(node, start, end);
		if (start == end)
			return Seg[node];
		int mid = (start + end) / 2;
		if (pos <= mid)
			return qQuery(2 * node, start, mid, pos);
		return qQuery(2 * node + 1, mid + 1, end, pos);
	}
	void Update(int node, int start, int end, int qstart, int qend, Node val)
	{
		propagate(node, start, end);
		if (qend < start || qstart > end || start > end)
			return;
		if (qstart <= start && end <= qend)
		{
			isLazy[node] = true;
			Lazy[node] = val;
			propagate(node, start, end);
			return;
		}
		int mid = (start + end) / 2;
		Update(2 * node, start, mid, qstart, qend, val);
		Update(2 * node + 1, mid + 1, end, qstart, qend, val);
		merge(Seg[node], Seg[2 * node], Seg[2 * node + 1]);
	}
	void pUpdate(int node, int start, int end, int pos, Node val)
	{
		propagate(node, start, end);
		if (start == end)
		{
			isLazy[node] = true;
			Seg[node] = Node();
			Lazy[node] = val;
			propagate(node, start, end);
			return;
		}
		int mid = (start + end) / 2;
		if (pos <= mid)
			pUpdate(2 * node, start, mid, pos, val);
		else
			pUpdate(2 * node + 1, mid + 1, end, pos, val);
		merge(Seg[node], Seg[2 * node], Seg[2 * node + 1]);
	}
	Node query(int pos)
	{
		return qQuery(1, 0, n - 1, pos);
	}
	Node query(int left, int right)
	{
		return Query(1, 0, n - 1, left, right);
	}
	void update(int pos, Node val)
	{
		pUpdate(1, 0, n - 1, pos, val);
	}
	void update(int start, int end, Node val)
	{
		Update(1, 0, n - 1, start, end, val);
	}
};

void solve()
{
	int n, x;
	cin >> n;
	// vector<int> a(n);
	vector<Segtree> Tree(20, Segtree(n));
	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		for (int j = 0; j < 20; ++j)
			if (x & (1 << j))
				Tree[j].update(i, Node());
	}
	int m, ch, l, r;
	cin >> m;
	while (m--)
	{
		cin >> ch >> l >> r;
		--l;
		--r;
		if (ch == 1)
		{
			ll res = 0;
			for (int j = 0; j < 20; ++j)
				res = res + (1 << j) * (ll)Tree[j].query(l, r).val;
			cout << res << '\n';
		}
		else
		{
			// int x;
			cin >> x;
			for (int j = 0; j < 20; ++j)
				if (x & (1 << j))
					Tree[j].update(l, r, Node());
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
	while (t--)
		solve();
#ifdef WIN32
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
	flush(cout);
#endif
	return 0;
}