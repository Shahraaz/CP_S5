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

void solve()
{
	int n;
	std::cin >> n;
	vector<ll> C(n);
	ll sum = 0;
	for (auto &x : C)
		std::cin >> x;
	if (n == 1)
	{
		cout << C[0] << ' ' << 0 << '\n';
		return;
	}
	int x;
	std::cin >> x;
	ll left = 0, right = n - 1;
	ll lEat, rEat;
	lEat = rEat = 0;
	pc(C);
	while (left <= right)
	{
		db(left, right, lEat, rEat);
		if (left == right)
		{
			int cnt = n - 1 - right;
			if (lEat < x * (rEat))
			{
				lEat += C[left];
				left++;
			}
			else if (lEat > x * (rEat))
			{
				rEat += C[right];
				right--;
			}
			else
			{
				if (left > cnt)
				{
					lEat += C[left];
					left++;
				}
				else if (left < cnt)
				{
					rEat += C[right];
					right--;
				}
				else
				{
					lEat += C[left];
					left++;
				}
			}
		}
		else if (lEat + C[left] < x * (rEat + C[right]))
		{
			lEat += C[left];
			left++;
		}
		else if (lEat + C[left] > x * (rEat + C[right]))
		{
			rEat += C[right];
			right--;
		}
		else
		{
			lEat += C[left];
			left++;
			rEat += C[right];
			right--;
		}
		db(left, right, lEat, rEat);
	}
	cout << left << ' ' << n - left << '\n';
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
	flush(cout);
#endif
	return 0;
}