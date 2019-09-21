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

struct Rect
{
	pair<int, int> Bottom, Top;
};

vector<int> area(int x1, int y1, int x2, int y2,
				 int x3, int y3, int x4, int y4)
{
	// gives bottom-left point
	// of intersection rectangle
	int x5 = max(x1, x3);
	int y5 = max(y1, y3);

	// gives top-right point
	// of intersection rectangle
	int x6 = min(x2, x4);
	int y6 = min(y2, y4);

	// no intersection
	if (x5 > x6 || y5 > y6)
	{
		// cout << "No intersection";
		return vector<int>(4);
	}

	vector<int> ret;
	ret.pb(x5);
	ret.pb(y5);
	ret.pb(x6);
	ret.pb(y6);
	return ret;
	// cout << "(" << x5 << ", " << y5 << ") ";

	// cout << "(" << x6 << ", " << y6 << ") ";
	// gives top-left point
	// of intersection rectangle
	// int x7 = x5;

	// int y7 = y6;
	// cout << "(" << x7 << ", " << y7 << ") ";

	// gives bottom-right point
	// of intersection rectangle
	// int x8 = x6;
	// int y8 = y5;

	// cout << "(" << x8 << ", " << y8 << ") ";
	// return y8 -
}

long long Area(int x1, int y1, int x2, int y2)
{
	return (ll)abs(y1 - y2) * abs(x1 - x2);
}

void solve()
{
	Rect white, Black1, Black2;
	cin >> white.Bottom.f >> white.Bottom.s;
	cin >> white.Top.f >> white.Top.s;
	Black1 = white;
	cin >> white.Bottom.f >> white.Bottom.s;
	cin >> white.Top.f >> white.Top.s;
	swap(white, Black1);
	swap(white, Black2);
	cin >> white.Bottom.f >> white.Bottom.s;
	cin >> white.Top.f >> white.Top.s;
	swap(white, Black2);
	ll res = Area(white.Bottom.f, white.Bottom.s, white.Top.f, white.Top.s);
	ll top, bottom;
	if (Black1.Bottom.s > Black2.Bottom.s)
		swap(Black1, Black2);
	auto ret = area(white.Bottom.f, white.Bottom.s, white.Top.f, white.Top.s, Black1.Bottom.f, Black1.Bottom.s, Black1.Top.f, Black1.Top.s);
	res -= Area(ret[0], ret[1], ret[2], ret[3]);
	swap(Black1, Black2);
	auto rett = area(white.Bottom.f, white.Bottom.s, white.Top.f, white.Top.s, Black1.Bottom.f, Black1.Bottom.s, Black1.Top.f, Black1.Top.s);
	swap(Black1, Black2);
	res -= Area(rett[0], rett[1], rett[2], rett[3]);
	auto rettt = area(white.Bottom.f, white.Bottom.s, white.Top.f, white.Top.s, Black1.Bottom.f, Black1.Bottom.s, Black1.Top.f, Black1.Top.s);
	swap(white, Black2);
	rettt = area(white.Bottom.f, white.Bottom.s, white.Top.f, white.Top.s, rettt[0], rettt[1], rettt[2], rettt[3]);
	res += Area(rettt[0], rettt[1], rettt[2], rettt[3]);
	cout << (res == 0 ? "NO" : "YES") << '\n';
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
	flush(cout);
#endif
	return 0;
}