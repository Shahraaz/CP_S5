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
vector<string> Grid(501);
bool vis[501][501];
int n, sx, sy, ex, ey, m;
int a[4] = {0, 0, 1, -1};
int b[4] = {1, -1, 0, 0};

bool valid(int x, int y)
{
	return x >= 0 && x < n && y >= 0 && y < m;
}

int checkSurr(int x, int y)
{
	int cnt = 0;
	for (int i = 0; i < 4; ++i)
	{
		int x1 = x + a[i];
		int y1 = y + b[i];
		if (valid(x1, y1) && Grid[x1][y1] == '.')
			cnt++;
	}
	return cnt;
}

bool dfs(int x, int y)
{
	if (Grid[x][y] == 'X' && !(sx == x && sy == y))
	{
		if (x == ex && y == ey)
			return true;
		return false;
	}
	vis[x][y] = true;
	if (x == ex && y == ey)
	{
		if (Grid[x][y] == 'X')
			return true;
		else
			return (checkSurr(x, y) >= 2);
	}
	for (int i = 0; i < 4; ++i)
	{
		int x1 = x + a[i];
		int y1 = y + b[i];
		if (valid(x1, y1) && !vis[x1][y1] && dfs(x1, y1))
			return true;
	}
	return false;
}

void solve()
{
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
		cin >> Grid[i];
	cin >> sx >> sy >> ex >> ey;
	--sx;
	--sy;
	--ex;
	--ey;
	if (sx == ex && sy == ey)
	{
		if (checkSurr(sx, sy))
			cout << "YES";
		else
			cout << "NO";
	}
	else
	{
		if (sx == ex)
		{
			if (sy == ey + 1)
			{
				if (checkSurr(ex, ey) || Grid[ex][ey]=='X')
					cout << "YES";
				else
					cout << "NO";
			}
			else if (sy == ey - 1)
			{
				if (checkSurr(ex, ey) || Grid[ex][ey] == 'X')
					cout << "YES";
				else
					cout << "NO";
			}
			else
				cout << (dfs(sx, sy) ? "YES" : "NO");
		}
		else if (sy == ey)
		{
			if (sx == ex + 1)
			{
				if (checkSurr(ex, ey) || Grid[ex][ey] == 'X')
					cout << "YES";
				else
					cout << "NO";
			}
			else if (sx == ex - 1)
			{
				if (checkSurr(ex, ey) || Grid[ex][ey] == 'X')
					cout << "YES";
				else
					cout << "NO";
			}
			else
				cout << (dfs(sx, sy) ? "YES" : "NO");
		}
		else
			cout << (dfs(sx, sy) ? "YES" : "NO");
	}
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