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

bool isSq(ll num)
{
	return ((ll)sqrtl(num) * (ll)sqrtl(num)) == num;
}

ll red(ll num)
{
	ll ret = 1;
	for (ll i = 2; i * i <= num; ++i)
	{
		if (num % i == 0)
		{
			int cnt = 0;
			while (num % i == 0)
			{
				cnt++;
				num /= i;
			}
			if (cnt & 1)
				ret *= i;
		}
	}
	if (num > 1)
		ret *= num;
	return ret;
}

ll power(ll base, int index)
{
	if (index == 0)
		return 1;
	ll temp = power(base, index / 2);
	temp *= temp;
	if (index & 1)
		temp *= base;
	return temp;
}

void solve(int caseNo)
{
	int n, k;
	cin >> n >> k;
	vector<ll> a(n);
	for (auto &x : a)
		cin >> x;
	if (k == 2)
	{
		for (int i = 0; i < n; ++i)
			a[i] = red(a[i]);
		sort(a.begin(), a.end());
		ll res = 0, prev = -1, cnt = 0;
		for (int i = 0; i < n; ++i)
		{
			if (a[i] == prev)
			{
				cnt++;
			}
			else
			{
				res += cnt * (cnt - 1);
				cnt = 1;
				prev = a[i];
			}
		}
		res += cnt * (cnt - 1);
		cout << res / 2 << '\n';
	}
	else
	{
		vector<ll> LAL;
		sort(a.begin(), a.end());
		ll lim = a[n - 1] * a[n - 2], temp;
		for (ll i = 1; (pow(i, k)) <= lim; ++i)
			LAL.pb(power(i, k));
		vector<int> Cnt(1e6, 0);
		ll res = 0;
		pc(LAL);
		for (int i = 0; i < n; ++i)
		{
			for (auto elem : LAL)
				if (elem % a[i] == 0)
					if (elem <= a[n - 1] * a[i])
					{
						db(elem, res, Cnt[elem / a[i]], elem / a[i]);
						res += Cnt[elem / a[i]];
					}
			Cnt[a[i]]++;
			db(res, i);
		}
		cout << res << '\n';
	}
	// db(cnt);
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