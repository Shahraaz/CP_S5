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

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	ll sum = 0;
	int posCnt = 0, NegCnt = 0;
	int odd = 0, even = 0;
	int cnt = 0;
	vector<pair<int, int>> A;
	for (auto &x : a)
	{
		cin >> x;
		if (x & 1)
			A.pb({x, cnt});
		cnt++;
		sum += x / 2;
		x /= 2;
	}
	// pc(A);
	// bool turn = false;
	for (auto Elem : A)
	{
		// db(a[Elem.s], Elem.s);
		if (Elem.f == 0)
			continue;
		if (sum > 0)
		{
			if (Elem.f > 0)
				;
			// a[Elem.s] = Elem.f / 2;
			else
				a[Elem.s] = Elem.f / 2 - 1, sum--;
		}
		else if (sum < 0)
		{
			if (Elem.f > 0)
				a[Elem.s] = Elem.f / 2 + 1, sum++;
			// a[Elem.s] = Elem.f / 2;
			// else
			// 	a[Elem.s] = Elem.f / 2 - 1, sum++;
		}
		db(a[Elem.s]);
		// turn = !turn;
	}

	// pc(A);
	sum = 0;
	for (auto &x : a)
	{
		sum += x;
		cout << x << '\n';
	}
	db(sum);
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
#endif
	return 0;
}