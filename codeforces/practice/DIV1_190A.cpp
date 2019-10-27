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

void solve(int caseNo)
{
	vector<pair<int, int>> pos;
	int a, b;
	string s;
	cin >> a >> b >> s;
	pos.pb({0, 0});
	for (auto c : s)
	{
		auto b = pos.back();
		switch (c)
		{
		case 'U':
			b.s++;
			pos.pb(b);
			break;
		case 'D':
			b.s--;
			pos.pb(b);
			break;
		case 'L':
			b.f--;
			pos.pb(b);
			break;
		case 'R':
			b.f++;
			pos.pb(b);
			break;
		default:
			break;
		}
	}
	auto back = pos.back();
	int x = back.f, y = back.s;
	db(x, y);
	pos.pop_back();
	for (auto elem : pos)
	{
		int a1 = a - elem.f;
		int b1 = b - elem.s;
		db(a1, b1);
		if (x == 0)
		{
			if (y == 0)
			{
				if (a1 == 0 && b1 == 0)
				{
					cout << "Yes\n";
					return;
				}
			}
			else
			{
				if (a1 == 0 && b1 % y == 0)
				{
					if (b1 / y >= 0)
					{
						cout << "Yes\n";
						return;
					}
				}
			}
		}
		else if (y == 0)
		{
			if (a1 % x == 0 && b1 == 0)
			{
				if (a1 / x >= 0)
				{
					cout << "Yes\n";
					return;
				}
			}
		}
		else
		{
			if (a1 % x == 0 && b1 % y == 0 && ((a1 / x) == (b1 / y)))
			{
				if (a1 / x >= 0)
				{
					cout << "Yes\n";
					return;
				}
			}
		}
	}
	cout << "No\n";
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
	for (int i = 0; i < t; ++i)
		solve(i);
#ifdef TIME
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}