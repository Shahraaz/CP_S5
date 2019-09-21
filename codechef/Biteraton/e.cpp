//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
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

int query(int i)
{
	cout << 1 << ' ' << i << endl;
	cin >> i;
	return i;
}

void report(int n)
{
	cout << 2 << ' ' << n << endl;
	string s;
	cin >> s;
	if (s == "No")
		exit(0);
}

void solve()
{
	int n, x;
	cin >> n >> x;
	int left = 1, right = 1e6;
	int mid, ret;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (left == right)
		{
			if (left % 2 == 0)
				mid = left - 1;
			else
				mid = left;
			break;
		}
		if (mid % 2 == 0)
		{
			mid++;
			if (left <= mid && mid <= right)
				;
			else
				mid -= 2;
		}
		ret = query(mid);
		if (ret == 0)
			right = mid - 1;
		else if (ret == x)
		{
			report(mid);
			return;
		}
		else if (ret < x)
		{
			left = mid + 1;
		}
		else
			right = mid - 1;
	}
	db(mid);
	if (ret < x)
		;
	else
		mid -= 2;
	if (mid < 1)
	{
		report(-1);
		return;
	}
	int rett = query(mid + 2);
	if (rett == x)
	{
		report(mid + 2);
		return;
	}
	int index = mid + 1;
	ll num = query(index);
	int cnt = 1, xx = mid + 1;
	while (xx % 2 == 0)
	{
		xx /= 2;
		cnt *= 2;
	}
	cnt--;
	int next = index + 1;
	while (cnt >= 0)
	{
		num -= query(next);
		int ccnt = 1;
		xx = next;
		while (xx % 2 == 0)
		{
			xx /= 2;
			ccnt *= 2;
		}
		cnt -= ccnt;
		next += ccnt;
	}
	if (num == x)
		report(mid + 1);
	else
		report(-1);
}

int main()
{
	// ios_base::sync_with_stdio(0);
	// cin.tie(0);
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