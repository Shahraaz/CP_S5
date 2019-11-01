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

ll dp[20][10][2];
int a[30], len;

ll Solve(int i, int firstDig, int checkSmall)
{
	if (i == len + 1)
		return checkSmall;
	if (i == len)
		return checkSmall || (firstDig < a[i]);
	ll &ret = dp[i][firstDig][checkSmall];
	if (ret >= 0)
		return ret;
	ret = 0;
	if (checkSmall)
		for (int j = 0; j <= 9; ++j)
			ret += Solve(i + 1, firstDig, 1);
	else
		for (int j = 0; j <= a[i]; ++j)
			ret += Solve(i + 1, firstDig, j < a[i]);
	return ret;
}

ll Solve(ll k)
{
	int storelen = 0;
	int idx = 1;
	while (k > 0)
	{
		a[idx++] = k % 10;
		k /= 10;
		storelen++;
	}
	reverse(a + 1, a + 1 + storelen);
	ll ans = 0;
	for (int l = 1; l <= storelen; ++l)
	{
		len = l;
		memset(dp, -1, sizeof dp);
		for (int firstdig = 1; firstdig <= 9; ++firstdig)
			if (l < storelen || firstdig <= a[1])
				ans += Solve(2, firstdig, firstdig < a[1] || l < storelen);
	}
	return ans;
}

void solve(int caseNo)
{
	ll l, r;
	cin >> l >> r;
	cout << Solve(r + 1) - Solve(l) << '\n';
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