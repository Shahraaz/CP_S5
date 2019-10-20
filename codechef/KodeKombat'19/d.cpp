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

vector<int> a;
vector<bool> sign;

bool vis[1001][1001][2];
ll dp[1001][1001][2];
ll solve(int start, int end, bool ch)
{
	if (vis[start][end][ch])
		return dp[start][end][ch];
	vis[start][end][ch] = true;
	if (start == end)
		return dp[start][end][ch] = a[start];
	ll &eval = dp[start][end][ch];
	if (ch)
	{
		eval = LLONG_MIN;
	}
	else
	{
		eval = LLONG_MAX;
	}
	for (int i = start + 1; i <= end; ++i)
	{
		bool Sign = sign[i - 1];
		if (Sign)
		{
			if (ch)
			{
				eval = max(eval, solve(start, i - 1, 1) + solve(i, end, 1));
				// eval = max(eval, solve(start, i - 1, 1) + solve(i, end, 0));
				// eval = max(eval, solve(start, i - 1, 0) + solve(i, end, 1));
				// eval = max(eval, solve(start, i - 1, 0) + solve(i, end, 0));
			}
			else
			{
				// eval = min(eval, solve(start, i - 1, 1) + solve(i, end, 1));
				// eval = min(eval, solve(start, i - 1, 1) + solve(i, end, 0));
				// eval = min(eval, solve(start, i - 1, 0) + solve(i, end, 1));
				eval = min(eval, solve(start, i - 1, 0) + solve(i, end, 0));
			}
		}
		else
		{
			if (ch)
			{
				// eval = max(eval, solve(start, i - 1, 1) - solve(i, end, 1));
				eval = max(eval, solve(start, i - 1, 1) - solve(i, end, 0));
				// eval = max(eval, solve(start, i - 1, 0) - solve(i, end, 1));
				// eval = max(eval, solve(start, i - 1, 0) - solve(i, end, 0));
			}
			else
			{
				// eval = min(eval, solve(start, i - 1, 1) - solve(i, end, 1));
				// eval = min(eval, solve(start, i - 1, 1) - solve(i, end, 0));
				eval = min(eval, solve(start, i - 1, 0) - solve(i, end, 1));
				// eval = min(eval, solve(start, i - 1, 0) - solve(i, end, 0));
			}
		}
	}
	db(eval, start, end, ch);
	return eval;
}

void solve()
{
	int n;
	cin >> n;
	string s;
	cin >> s;
	int prev = 0;
	for (auto c : s)
	{
		if (c == ' ')
			continue;
		if (c == '+')
		{
			a.pb(prev);
			sign.pb(true);
			prev = 0;
		}
		else if (c == '-')
		{
			a.pb(prev);
			sign.pb(false);
			prev = 0;
		}
		else
		{
			prev = prev * 10 + c - '0';
		}
	}
	a.pb(prev);
	pc(a, sign);
	cout << solve(0, a.size() - 1, 1) - solve(0, a.size() - 1, 0) << '\n';
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