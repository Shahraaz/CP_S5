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
int Grid[10][10];
pair<int, int> Next[10][10];
using ld = long double;
ld Steps[10][10];

void solve(int caseNo)
{
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j)
			cin >> Grid[i][j];
	for (int i = 1; i <= 6; ++i)
	{
		Steps[0][i] = 6;
		// db(0, i, Steps[0][i]);
	}
	for (int i = 7; i < 10; ++i)
	{
		for (int j = 1; j <= 6; ++j)
			Steps[0][i] += (ld)1 / 6 * (1 + Steps[0][i - j]);
		// db(0, i, Steps[0][i]);
	}
	bool way = 1;
	for (int i = 9; i >= 0; --i)
	{
		for (int j = 0; j <= 9; ++j)
		{
			if (way)
				Next[i][j] = {i, j + 1};
			else
				Next[i][j] = {i, j - 1};
		}
		if (way)
			Next[i][9] = {i - 1, 9};
		else
			Next[i][0] = {i - 1, 0};
		way = !way;
	}
	way = 1;
	for (int i = 1; i < 10; ++i)
	{
		if (way)
		{
			for (int j = 9; j >= 0; --j)
			{
				int x = i;
				int y = j;
				db(i, j);
				for (int k = 0; k < 6; ++k)
				{
					int x1 = Next[x][y].f;
					int y1 = Next[x][y].s;
					// db(x, y, x1, y1, x1, y1 - Grid[x1][y1]);
					x = x1, y = y1;
					db(k, x1, y1);
					Steps[i][j] += ld(1) / 6 * (1 + min(Steps[x - Grid[x][y]][y], Steps[x][y]));
				}
				db(i, j, Steps[i][j]);
			}
		}
		else
		{
			for (int j = 0; j < 10; ++j)
			{
				int x = i;
				int y = j;
				db(i, j);
				for (int k = 0; k < 6; ++k)
				{
					int x1 = Next[x][y].f;
					int y1 = Next[x][y].s;
					x = x1, y = y1;
					db(k, x1, y1);
					Steps[i][j] += ld(1) / 6 * (1 + min(Steps[x - Grid[x][y]][y], Steps[x][y]));
				}
				db(i, j, Steps[i][j]);
			}
		}
		way = !way;
	}
	cout << fixed << setprecision(9);
	cout << Steps[9][0] << '\n';
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