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

const int nax = 3e5 + 10;
vector<ll> a(nax);
int n;
vector<ll> Gcd(4 * nax), Min(4 * nax);

ll gcd(ll a, ll b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

ll buildGcd(int node, int star, int end)
{
	if (star == end)
		return Gcd[node] = a[star];
	int mid = (star + end) / 2;
	return Gcd[node] = gcd(buildGcd(2 * node, star, mid), buildGcd(2 * node + 1, mid + 1, end));
}

ll buildMin(int node, int star, int end)
{
	if (star == end)
		return Min[node] = a[star];
	int mid = (star + end) / 2;
	return Min[node] = min(buildMin(2 * node, star, mid), buildMin(2 * node + 1, mid + 1, end));
}

ll queryGcd(int node, int start, int end, int qstart, int qend)
{
	if (start > end || qstart > end || qend < start)
		return 0;
	if (qstart <= start && end <= qend)
		return Gcd[node];
	int mid = (start + end) / 2;
	ll left = queryGcd(2 * node, start, mid, qstart, qend);
	ll right = queryGcd(2 * node + 1, mid + 1, end, qstart, qend);
	return gcd(left, right);
}

ll queryMin(int node, int start, int end, int qstart, int qend)
{
	if (start > end || qstart > end || qend < start)
		return mod;
	if (qstart <= start && end <= qend)
		return Min[node];
	int mid = (start + end) / 2;
	ll left = queryMin(2 * node, start, mid, qstart, qend);
	ll right = queryMin(2 * node + 1, mid + 1, end, qstart, qend);
	return min(left, right);
}

bool solve(int len)
{
	for (int i = 0; i < n; ++i)
	{
		int j = i + len - 1;
		if (j < n)
		{
			int gcd = queryGcd(1, 0, n - 1, i, j);
			int min = queryMin(1, 0, n - 1, i, j);
			if (gcd == min)
				return true;
		}
		else
			return false;
	}
	return false;
}

void solvePrint(int len)
{
	vector<int> ans;
	for (int i = 0; i < n; ++i)
	{
		int j = i + len - 1;
		if (j < n)
		{
			int gcd = queryGcd(1, 0, n - 1, i, j);
			int min = queryMin(1, 0, n - 1, i, j);
			// db(gcd, min);
			if (gcd == min)
				ans.pb(i);
		}
	}
	cout << ans.size() << ' ' << len - 1 << '\n';
	for (auto x : ans)
		cout << x + 1 << ' ';
}

void solve()
{
	// int a1 = gcd(10, 0);
	// int b1 = gcd(0, 10);
	// db(a1, b1);
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	buildGcd(1, 0, n - 1);
	buildMin(1, 0, n - 1);
	int low = 1, high = n, ans = 0;
	while (low <= high)
	{
		int mid = (low + high) / 2;
		if (solve(mid))
		{
			low = mid + 1;
			ans = mid;
		}
		else
			high = mid - 1;
	}
	solvePrint(ans);
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