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
	int n;
	cin >> n;
	vector<int> a(n);
	multiset<int> S;
	set<int> s;
	for (auto &x : a)
	{
		cin >> x;
		S.insert(x);
		s.insert(x);
	}
	if (s.size() == n)
	{
		cout << 0;
		return;
	}
	int Len = INT_MAX;
	for (int i = 0; i < n; ++i)
	{
		auto temp = S;
		auto Temp = s;
		for (int j = i; j < n; ++j)
		{
			temp.erase(temp.find(a[j]));
			if (temp.find(a[j]) == temp.end())
				Temp.erase(a[j]);
			int len = j - i + 1;
			int rem = n - len;
			if (len > Len)
				break;
			if (Temp.size() == rem)
			{
				Len = min(Len, len);
				break;
			}
		}
		db(i, Len);
	}
	db("ow");
	cout << Len;
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