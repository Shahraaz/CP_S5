//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
// #define Debug 1
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

typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
const long long mod = 1000000007;

void solve()
{
	string s1, s2;
	cin >> s1 >> s2;
	if (s1.size() < s2.size())
		swap(s1, s2);
	if (s1.substr(0, s2.size()) != s2)
		cout << 0 << '\n';
	else
	{
		int ans = 0;
		int g = __gcd(s1.size(), s2.size());
		for (int i = 1; i <= g; ++i)
		{
			if (g % i == 0)
			{
				bool b = true;
				for (int j = 0; j < s1.size(); j += i)
					if(s1.substr(j,i) != s1.substr(0,i))
					{
						b = false;
						break;
					}
				if(b) ans++;
			}
		}
		cout << ans << '\n';
	}
}

int main()
{
#ifndef Debug
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#endif
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (t--)
		solve();
	return 0;
}