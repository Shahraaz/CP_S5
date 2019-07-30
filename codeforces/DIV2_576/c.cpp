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

const int nax = 4e5 + 10;
int n, i;
vector<int> a, b;

bool able(int start, int end)
{
	if (start < 0 || start >= n || start > end)
		return false;
	if (end < 0 || end >= n)
		return false;
	// db(start, end);
	start = a[start];
	end = a[end];
	int cnt = upper_bound(b.begin(), b.end(), end) - lower_bound(b.begin(), b.end(), start);
	int m = 0;
	// db(start, end, cnt);
	while ((1 << m) < cnt)
		m++;
	if (cnt == 1)
		m = 0;
	db(m, cnt);
	return (n * m) <= i;
}

void solve()
{
	cin >> n >> i;
	i *= 8;
	a = vector<int>(n);
	for (auto &x : a)
		cin >> x;
	sort(a.begin(), a.end());
	b = a;
	b.erase(unique(b.begin(), b.end()), b.end());
	int res = mod;
	for (int i = 0; i < n; ++i)
	{
		int low = i, high = n - 1;
		while (low <= high)
		{
			int mid = (low + high) / 2;
			bool b = able(i, mid);
			db(i, mid, b);
			if (b)
			{
				low = mid + 1;
				int less = i;
				int more = n - 1 - mid;
				res = min(res, less + more);
				// db(res, i, less, more);
			}
			else
			{
				high = mid - 1;
			}
		}
	}
	cout << res;
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