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

const int nax = 1e5 + 10;
vector<int> V[nax], in(nax), dp(nax);
vector<bool> Pchk(nax);
vector<int> Plist;

void solve()
{
	for (int i = 2; i * i <= nax; ++i)
	{
		if (Pchk[i])
			continue;
		Plist.pb(i);
		for (int j = i * i; j <= nax; j += i)
			Pchk[j] = false;
	}
	int n, num;
	cin >> n;
	int ans = 0;
	map<int, int> Mx;
	for (int i = 0; i < n; ++i)
	{
		cin >> num;
		for (auto it : Plist)
		{
			if (it * it > num)
				break;
			if (num % it)
				continue;
			if (Mx.count(it))
				V[i].pb(Mx[it]);
			Mx[it] = i;
			while (num % it == 0)
				num /= it;
		}
		if (num != 1)
		{
			if (Mx.count(num))
				V[i].pb(Mx[num]);
			Mx[num] = i;
		}
		dp[i] = 1;
		for (auto it : V[i])
			dp[i] = max(dp[i], dp[it] + 1);
		ans = max(ans, dp[i]);
	}
	cout << ans;
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