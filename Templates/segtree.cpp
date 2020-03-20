#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

struct Node
{
	long long val;
	Node(long long one = 0) : val(one) {}
	Node operator+(const Node &rhs)
	{
		Node a = *this;
		a.val = max(a.val, rhs.val);
		return a;
	}
	Node lazylazyMerge(const Node &rhs)
	{
		Node a = *this;
		a.val = max(a.val, rhs.val);
		return a;
	}
	Node seglazyMerge(const Node &rhs)
	{
		Node a = *this;
		a.val = max(a.val, rhs.val);
		return a;
	}
	Node segSegMerge(const Node &rhs)
	{
		Node a = *this;
		a.val = max(a.val, rhs.val);
		return a;
	}
};

template <typename segNode>
struct Segtree
{
	vector<segNode> Seg, Lazy;
	vector<segNode> Base;
	vector<segNode> isLazy;
	int n;
	Segtree(int _n = 2e5)
	{
		this->n = _n;
		Seg.resize(4 * _n + 10);
		Lazy.resize(4 * _n + 10);
		isLazy.resize(4 * _n + 10);
	}
	void merge(segNode &curr, segNode &l, segNode &r)
	{
		curr = l + r;
	}
	void propagate(int node, int L, int R)
	{
		if (isLazy[node])
		{
			isLazy[node] = false;
			Seg[node] = Seg[node].seglazyMerge(Lazy[node]);
			if (L != R)
			{
				Lazy[2 * node] = Lazy[2 * node].lazylazyMerge(Lazy[node]);
				Lazy[2 * node + 1] = Lazy[2 * node + 1].lazylazyMerge(Lazy[node]);
				isLazy[2 * node] = true;
				isLazy[2 * node + 1] = true;
			}
			Lazy[node] = segNode();
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
		Seg[node] = Seg[2 * node].segSegMerge(Seg[2 * node + 1]);
	}
	void build(vector<segNode> &Arr)
	{
		Base = Arr;
		n = Arr.size();
		Seg.resize(4 * n + 10);
		Lazy.resize(4 * n + 10);
		isLazy.resize(4 * n + 10);
		build(1, 0, n - 1);
	}
	segNode Query(int node, int start, int end, int qstart, int qend)
	{
		propagate(node, start, end);
		if (qend < start || qstart > end || start > end)
			return segNode();
		if (qstart <= start && end <= qend)
			return Seg[node];
		int mid = (start + end) / 2;
		segNode l = Query(2 * node, start, mid, qstart, qend);
		segNode r = Query(2 * node + 1, mid + 1, end, qstart, qend);
		return l.segSegMerge(r);
	}
	segNode qQuery(int node, int start, int end, int pos)
	{
		propagate(node, start, end);
		if (start == end)
			return Seg[node];
		int mid = (start + end) / 2;
		if (pos <= mid)
			return qQuery(2 * node, start, mid, pos);
		return qQuery(2 * node + 1, mid + 1, end, pos);
	}
	void Update(int node, int start, int end, int qstart, int qend, segNode val)
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
		Seg[node] = Seg[2 * node].segSegMerge(Seg[2 * node + 1]);
	}
	void pUpdate(int node, int start, int end, int pos, segNode val)
	{
		propagate(node, start, end);
		if (start == end)
		{
			isLazy[node] = true;
			Lazy[node] = val;
			propagate(node, start, end);
			return;
		}
		int mid = (start + end) / 2;
		if (pos <= mid)
			pUpdate(2 * node, start, mid, pos, val);
		else
			pUpdate(2 * node + 1, mid + 1, end, pos, val);
		Seg[node] = Seg[2 * node].segSegMerge(Seg[2 * node + 1]);
	}
	segNode query(int pos)
	{
		return qQuery(1, 0, n - 1, pos);
	}
	segNode query(int left, int right)
	{
		return Query(1, 0, n - 1, left, right);
	}
	void update(int pos, segNode val)
	{
		pUpdate(1, 0, n - 1, pos, val);
	}
	void update(int start, int end, segNode val)
	{
		Update(1, 0, n - 1, start, end, val);
	}
};

int main()
{
	Segtree<Node> S(1e5);
	return 0;
}