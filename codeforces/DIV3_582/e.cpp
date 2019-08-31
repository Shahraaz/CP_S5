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

void solve()
{
	string fff, sss;
	int n;
	cin >> n >> fff >> sss;
	vector<string> SS;
	vector<char> Perm;
	Perm.pb('a');
	Perm.pb('b');
	Perm.pb('c');
	do
	{
		string ff = "" + Perm[0] + Perm[1];
		string ss = "" + Perm[1] + Perm[2];
		string sss = "" + Perm[2] + Perm[0];
		if (ff != fff && ss != sss && ff != sss && ss != fff && sss != fff && sss != sss)
		{
			cout << "YES\n";
			for (int i = 0; i < n; ++i)
				cout << Perm[0] << Perm[1] << Perm[2];
			return;
		}
		ff = "" + Perm[0];
		ff += Perm[0];
		ss = "" + Perm[1];
		ss += Perm[1];
		sss = "" + Perm[2];
		sss += Perm[2];
		string xx = "" + Perm[0];
		xx += Perm[1];
		string yy = "" + Perm[1];
		yy += Perm[2];

		if (xx != fff && yy != sss && xx != sss && yy != fff)
			if (ff != fff && ss != sss && ff != sss && ss != fff && sss != fff && sss != sss)
			{
				cout << "YES\n";
				for (int i = 0; i < n; ++i)
					cout << Perm[0];
				// cout << '\n';
				// cout << '\n';
				for (int i = 0; i < n; ++i)
					cout << Perm[1];
				// cout << '\n';
				for (int i = 0; i < n; ++i)
					cout << Perm[2];
				return;
			}
	} while (next_permutation(Perm.begin(), Perm.end()));
	cout << "NO";
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