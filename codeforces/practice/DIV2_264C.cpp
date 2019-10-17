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
const long long mod = 1000000007;
auto TimeStart = chrono::steady_clock::now();

const int nax = 2e3 + 10;

ll mat[nax][nax], topl[nax][nax], bottoml[nax][nax];
ll topr[nax][nax], bottomr[nax][nax];

int n;
ll cal(int i, int j)
{
	int i1 = i + 1, j1 = j + 1;
	ll ret = 0;
	while (i1 < n && j1 < n && i1 >= 0 && j1 >= 0)
	{
		ret += mat[i1][j1];
		++i1;
		++j1;
	}
	i1 = i + 1, j1 = j - 1;
	while (i1 < n && j1 < n && i1 >= 0 && j1 >= 0)
	{
		ret += mat[i1][j1];
		++i1;
		--j1;
	}
	i1 = i - 1, j1 = j + 1;
	while (i1 < n && j1 < n && i1 >= 0 && j1 >= 0)
	{
		ret += mat[i1][j1];
		--i1;
		++j1;
	}
	i1 = i - 1, j1 = j - 1;
	while (i1 < n && j1 < n && i1 >= 0 && j1 >= 0)
	{
		ret += mat[i1][j1];
		--i1;
		--j1;
	}
	return ret + mat[i][j];
}

void solve()
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> mat[i][j];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
		{
			topl[i][j] += topl[i - 1][j - 1];
			topr[i][j] += topr[i - 1][j + 1];
			topl[i][j] += mat[i][j];
			topr[i][j] += mat[i][j];
		}
	ll max1, max2;
	int x1, y1, x2, y2;
	max1 = -1;
	max2 = -1;
	for (int i = n; i >= 1; --i)
		for (int j = 1; j <= n; ++j)
		{
			bottomr[i][j] += bottomr[i + 1][j - 1];
			bottoml[i][j] += bottoml[i + 1][j + 1];
			ll temp = topl[i][j] + bottoml[i][j];
			temp += topr[i][j] + bottomr[i][j];
			temp -= mat[i][j];
			ll temp2 = cal(i, j);
			bottoml[i][j] += mat[i][j];
			bottomr[i][j] += mat[i][j];
			db(i, j, temp, temp2);
			if (i & 1)
			{
				if (j & 1)
				{
					if (temp > max1)
					{
						max1 = temp;
						x1 = i, y1 = j;
					}
				}
				else
				{
					if (temp > max2)
					{
						max2 = temp;
						x2 = i, y2 = j;
					}
				}
			}
			else
			{
				if (!(j & 1))
				{
					if (temp > max1)
					{
						max1 = temp;
						x1 = i, y1 = j;
					}
				}
				else
				{
					if (temp > max2)
					{
						max2 = temp;
						x2 = i, y2 = j;
					}
				}
			}
		}
	cout << max1 + max2 << '\n';
	cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
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