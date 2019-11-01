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
	string s;
	cin >> s;
	s += "#";
	ll ways = 1;
	int cntu, cntn;
	cntu = cntn = 0;
	int n = s.length();
	ll fib[nax];
	fib[0] = fib[1] = 1;
	for (int i = 2; i < nax; ++i)
		fib[i] = (fib[i - 1] + fib[i - 2]) % mod;
	for (int i = 0; i < n; ++i)
	{
		if (s[i] == 'n')
		{
			if (cntu)
			{
				ways *= fib[cntu];
				ways %= mod;
				cntu = 0;
			}
			cntn++;
		}
		else if (s[i] == 'u')
		{
			if (cntn)
			{
				ways *= fib[cntn];
				ways %= mod;
				cntn = 0;
			}
			cntu++;
		}
		else
		{
			if (cntu)
			{
				ways *= fib[cntu];
				ways %= mod;
				cntu = 0;
			}
			if (cntn)
			{
				ways *= fib[cntn];
				ways %= mod;
				cntn = 0;
			}
		}
		if (s[i] == 'm')
		{
			cout << 0 << '\n';
			return;
		}
		if (s[i] == 'w')
		{
			cout << 0 << '\n';
			return;
		}
	}
	if (cntu)
	{
		ways *= fib[cntu];
		ways %= mod;
		cntu = 0;
	}
	if (cntn)
	{
		ways *= fib[cntn];
		ways %= mod;
		cntn = 0;
	}
	cout << ways << '\n';
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