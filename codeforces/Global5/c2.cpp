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

using ld = long double;

struct point
{
	ll x, y, z;
	ld DistSQ;
	ld a, b, c;
	point(int x1 = 0, int y1 = 0, int z1 = 0)
	{
		x = x1;
		y = y1;
		z = z1;
		// DistSQ = sqrtl(x * x + y * y + z * z);
		// a = x / DistSQ;
		// b = y / DistSQ;
		// c = z / DistSQ;
	}
	bool operator<(const point &rhs) const
	{
		// if (DistSQ == rhs.DistSQ)
		{
			if (x == rhs.x)
			{
				if (y == rhs.y)
				{
					return z < rhs.z;
				}
				return y < rhs.y;
			}
			return x < rhs.x;
		}
		// return DistSQ < rhs.DistSQ;
	}
	ll dist(const point &rhs)
	{
		return (x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y) + (z - rhs.z) * (z - rhs.z);
	}
};

ostream &operator<<(ostream &out, const point &p)
{
	out << p.x << " " << p.y << " " << p.z;
	return out;
}

bool del[nax];

pair<bool, int> Solve(set<pair<point, int>> &A)
{
	pc(A);
	map<int, set<pair<point, int>>> B;
	for (auto item : A)
	{
		auto y = item.f.y;
		B[y].insert(item);
	}
	bool hasPrev;
	int idx;
	hasPrev = false;
	// pair<point, int> ret;
	for (auto List : B)
	{
		auto C = List.s;
		while (C.size() >= 2)
		{
			auto one = C.begin();
			// B.s.pop();
			auto two = ++C.begin();
			db("ONE");
			// one->second
			std::cout << (one->s) + 1 << ' ' << two->s + 1 << '\n';
			C.erase(one);
			C.erase(two);
		}
		if (C.size())
		{
			auto indx2 = C.begin()->s + 1;
			if (hasPrev)
			{
				db("THREE");
				cout << idx << ' ' << indx2 << '\n';
				hasPrev = false;
			}
			else
			{
				hasPrev = true;
				// ret = C.begin->f;
				idx = indx2;
			}
		}
	}
	auto rett = make_pair(hasPrev, idx);
	db(rett);
	return rett;
}

void solve()
{
	int n, x, y, z;
	cin >> n;
	vector<pair<point, int>> A;
	map<int, set<pair<point, int>>> MM;
	for (int i = 0; i < n; ++i)
	{
		cin >> x >> y >> z;
		A.pb({point(x, y, z), i});
		MM[x].insert({point(x, y, z), i});
	}
	bool prevExist = false;
	int idx = 0;
	point prevPoint(0, 0, 0);
	for (auto List : MM)
	{
		auto Elem = List.s;
		// db(List.f);
		// pc(Elem);
		auto ret = Solve(Elem);
		// while (Elem.size() >= 2)
		// {
		// 	auto one = Elem.begin();
		// 	auto two = ++Elem.begin();
		// 	db("ONE");
		// 	cout << one->s + 1 << ' ' << two->s + 1 << '\n';
		// 	Elem.erase(one);
		// 	Elem.erase(two);
		// }
		if (ret.f)
		{
			auto indx2 = ret.s;
			if (prevExist)
			{
				db("TWO");
				cout << idx << ' ' << indx2 << '\n';
				prevExist = false;
			}
			else
			{
				prevExist = true;
				idx = indx2;
			}
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
#endif
	return 0;
}