//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
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

vector<ll> Sum;
int _n;
void Sum_Pre(vector<int> &v)
{
	_n = v.size();
	Sum.resize(_n);
	Sum[0] = v[0];
	for (int i = 1; i < _n; ++i)
		Sum[i] = Sum[i - 1] + v[i];
}

ll rangesum(int start, int end)
{
	db(start, end);
	if (start == 0)
		return Sum[end];
	return Sum[end] - Sum[start - 1];
}

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	map<int, int> Indices;
	int ind = 0;
	for (auto &x : a)
	{
		cin >> x;
		Indices[x]++;
	}
	Sum_Pre(a);
	// ll res = 0, start = 0, startVal;
	// vector<ll> Res;
	// while (start < n)
	// {
	// 	int elem = start, i = start, end;
	// lab:
	// 	end = Indices[a[i]].back();
	// 	for (; i <= end; ++i)
	// 	{
	// 		int end2 = Indices[a[i]].back();
	// 		end = max(end, end2);
	// 	}
	// 	int cnt = end - start + 1;
	// 	// db(end, start, cnt);
	// 	if (cnt & 1)
	// 	{
	// 		i = end + 1;
	// 		goto lab;
	// 	}
	// 	else
	// 	{
	// 		Res.pb(elem);
	// 		start = end + 1;
	// 	}
	// }
	// pc(Res);
	// Res.pb(n);
	vector<ll> dp(n + 1);
	dp[n] = 0;
	for (int i = n - 1; i >= 0; i -= 1)
	{
		ll &ret = dp[i];
		ret = -1e18;
		// map<int, int> Temp;
		for (int j = i + 1; j <= n; ++j)
		{
			int cnt = j - i;
			// Temp[a[j - 1]]++;
			if (cnt % 2 == 0)
			{
				// ll temp = rangesum(Res[i], Res[i] + (Res[j] - Res[i]) / 2 - 1);
				// db(Res[i], Res[j], dp[j], temp);
				// ret = max(ret, dp[j] + temp);
				ll sum = rangesum(i, i + cnt / 2 - 1);
				// for (int k = 0; k < cnt / 2; ++k)
				// sum += a[i + k];
				bool b = true;
				// for (int k = i; k < j; ++k)
				// if (Temp[a[k]] != Indices[a[k]])
				// {
				// b = false;
				// break;
				// }
				// if (b)
				ret = max(ret, dp[j] + sum);
			}
		}
		db(i, ret);
	}
	cout << dp[0] << '\n';
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
	flush(cout);
#endif
	return 0;
}