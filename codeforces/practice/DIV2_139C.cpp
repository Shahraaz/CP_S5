//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
#ifdef Debug
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__);
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
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
const long long mod = 1000000007;
auto TimeStart = chrono::steady_clock::now();

const int nax = 1e3 + 10;

vector<string> Inp(nax);
vector<int> Blank(nax);
int n, m, x, y;
int dp[nax][nax][2];

int solve(int idx, int prevClr, bool anyPaint)
{
	if (idx == m)
	{
		if (prevClr == 0)
			if (anyPaint)
				return 0;
			else
				return mod;
		if (x <= prevClr && prevClr <= y)
			return 0;
		else
			return mod;
	}
	if (prevClr > y)
	{
		db("prev Clr greater than Y");
		return mod;
	}
	int &ret = dp[idx][prevClr][anyPaint];
	if (ret >= 0)
		return ret;
	ret = mod;
	if (prevClr > 0)
	{
		if (prevClr < x)
		{
			ret = min(ret, Blank[idx] + solve(idx + 1, prevClr + 1, true));
		}
		else
		{
			if (prevClr < y)
				ret = min(ret, Blank[idx] + solve(idx + 1, prevClr + 1, true));
			ret = min(ret, n - Blank[idx] + solve(idx + 1, 0, true));
		}
	}
	else
	{
		ret = min(ret, Blank[idx] + solve(idx + 1, 1, true));
		ret = min(ret, n - Blank[idx] + solve(idx + 1, 0, anyPaint));
	}
	return ret;
}

void solve()
{
	cin >> n >> m >> x >> y;
	for (int i = 0; i < n; ++i)
		cin >> Inp[i];
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			Blank[i] += Inp[j][i] == '.';
	cout << solve(0, 0, 0);
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