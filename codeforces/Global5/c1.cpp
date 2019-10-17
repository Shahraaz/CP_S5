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

struct point
{
	ll x, y, z;
	ll DistSQ;
	point(int x1, int y1, int z1)
	{
		x = x1;
		y = y1;
		z = z1;
		DistSQ = x * x + y * y + z * z;
	}
	bool operator<(const point &rhs) const
	{
		if (DistSQ == rhs.DistSQ)
		{
		}
		return DistSQ < rhs.DistSQ;
	}
	ll dist(const point &rhs)
	{
		return (x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y) + (z - rhs.z) * (z - rhs.z);
	}
};

bool del[nax];
void solve()
{
	int n, x, y, z;
	cin >> n;
	vector<pair<point, int>> A;
	for (int i = 0; i < n; ++i)
	{
		cin >> x >> y >> z;
		A.pb({point(x, y, z), i});
	}

	for (int i = 0; i < n; ++i)
	{
		if (del[i])
			continue;
		int idx = -1;
		for (int j = i + 1; j < n; ++j)
		{
			if (del[j])
				continue;
			if (idx == -1)
				idx = j;
			else
			{
				if (A[i].f.dist(A[j].f) < A[i].f.dist(A[idx].f))
				{
					idx = j;
				}
				db(i,j,idx,A[i].f.dist(A[j].f), A[i].f.dist(A[idx].f));
			}
		}
		del[idx] = true;
		cout << i + 1 << ' ' << idx + 1 << '\n';
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