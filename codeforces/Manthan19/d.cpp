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

vector<ll> Seg(4 * nax, 0);

void pUpdate(int node, int L, int R, int pos, int val)
{
	if (L == R)
	{
		Seg[node] = val;
		return;
	}
	int M = (L + R) / 2;
	if (pos <= M)
		pUpdate(node * 2, L, M, pos, val);
	else
		pUpdate(node * 2 + 1, M + 1, R, pos, val);
	Seg[node] = Seg[node * 2] + Seg[node * 2 + 1];
	// db(L, R, Seg[node]);
}

ll Query(int node, int L, int R, int i, int j)
{
	if (j < L || i > R)
		return 0;
	if (i <= L && R <= j)
		return Seg[node];
	int M = (L + R) / 2;
	ll left = Query(node * 2, L, M, i, j);
	ll right = Query(node * 2 + 1, M + 1, R, i, j);
	return left + right;
}

void solve()
{
	ll n, u;
	cin >> n;
	stack<ll> Q;
	for (int i = 1; i <= n; ++i)
	{
		cin >> u;
		Q.push(u);
		pUpdate(1, 0, n, i, i);
		int temp = Query(1, 0, n, 1, i);
		// db(i, temp);
	}
	stack<ll> Ans;
	for (int i = 1; i <= n; ++i)
	{
		u = Q.top();
		Q.pop();
		int left = 1, right = n, ans = 0;
		while (left <= right)
		{
			int mid = (left + right) / 2;
			auto q = Query(1, 0, n, 1, mid - 1);
			if (q == u)
			{
				ans = mid;
				left = mid + 1;
			}
			else if (q < u)
			{
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
			db(q, mid, i, ans);
		}
		db(ans);
		Ans.push(ans);
		pUpdate(1, 0, n, ans, 0);
	}
	while (!Ans.empty())
	{
		/* code */
		cout << Ans.top() << ' ';
		Ans.pop();
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