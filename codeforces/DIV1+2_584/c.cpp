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
int n;
string str;
string res;

void solve()
{
	cin >> n;
	cin >> str;
	res.assign(n, '2');
	db(str);
	// str.assign(n,'1');
	vector<deque<int>> V(10);
	for (int i = 0; i < n; ++i)
		V[str[i] - '0'].pb(i);
	int prev;
	char c;
	int start = 0;
	// for (int k = 0; k < 10; ++k)
	// pc(V[k]);
	for (int k = 0; k < 10; ++k)
	{
		bool iWant = false;
		for (int i = 0; i < 10; ++i)
		{
			if (V[i].size())
			{
				c = i + '0';
				// db(i);
				// pc(V[i]);
				for (auto j : V[i])
				{
					res[j] = '1';
					prev = j;
				}
				V[i].clear();
				iWant = true;
				break;
			}
		}
		if (!iWant)
			break;
		string s;
		int maxT = -1, minT = 11;
		for (int i = start; i < prev; ++i)
		{
			if (res[i] == '2')
			{
				V[str[i] - '0'].pop_front();
				s.pb(str[i]);
				maxT = max(maxT, str[i] - '0');
				minT = min(minT, str[i] - '0');
			}
		}
		start = prev + 1;
		string N = s;
		s = c + s;
		db(k, s, prev, minT, maxT);
		if (is_sorted(s.begin(), s.end()))
		{
			if (maxT == -1)
			{
				start = prev + 1;
			}
			else
			{
				s = N;
				for (int i = prev + 1; i < n; ++i)
				{
					if (str[i] <= (minT + '0'))
					{
						res[i] = '1';
						// s += str[i];
					}
					else
					{
						res[i] = '2';
						// N.pb(str[i]);
					}
				}
				string A, B;
				for (int i = 0; i < n; ++i)
					if (res[i] == '1')
						A.pb(str[i]);
					else
						B.pb(str[i]);
				db(A, B);
				A += B;
				if (is_sorted(A.begin(), A.end()))
					cout << res << '\n';
				else
					cout << "-\n";
				return;
			}
		}
		else
		{
			cout << "-\n";
			return;
		}
	}
	string A, B;
	for (int i = 0; i < n; ++i)
		if (res[i] == '1')
			A.pb(str[i]);
		else
			B.pb(str[i]);
	A += B;
	if (is_sorted(A.begin(), A.end()))
		cout << res << '\n';
	else
		cout << "-\n";
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