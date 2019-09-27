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
	vector<ll> Cap(n), Fill(n), NextNonFull(n + 1);
	for (auto &x : Cap)
		cin >> x;
	int m, ch, p, k, x;
	cin >> m;
	for (int i = 0; i < n; ++i)
		NextNonFull[i] = i + 1;
	NextNonFull[n] = n;
	while (m--)
	{
		cin >> ch;
		if (ch == 1)
		{
			cin >> p >> x;
			--p;
			int rem = Cap[p] - Fill[p];
			queue<int> Q;
			while (x)
			{
				if (rem <= x)
				{
					Q.push(p);
					Fill[p] = Cap[p];
					x -= rem;
					p = NextNonFull[p];
					if (p == n)
						x = 0;
					else
						rem = Cap[p] - Fill[p];
				}
				else
				{
					Fill[p] += x;
					x = 0;
					// p = NextNonFull[p];
				}
			}
			while (!Q.empty())
			{
				auto front = Q.front();
				Q.pop();
				NextNonFull[front] = p;
			}
			pc(Cap);
			pc(Fill);
			pc(NextNonFull);
		}
		else
		{
			cin >> k;
			--k;
			cout << Fill[k] << '\n';
		}
	}
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