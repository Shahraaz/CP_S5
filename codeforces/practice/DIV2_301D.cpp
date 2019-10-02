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

using ld = long double;
ld prob[101][101][101];
bool vis[101][101][101];

// ld solve(int r, int s, int p, ld prob)
// {
// 	if (r == 0 && s == 0)
// 	{
// 	}
// }

typedef pair<int, pair<int, int>> pii;

void solve()
{
	int R, S, P;
	cin >> R >> S >> P;
	// solve(R, S, P, 1);
	queue<pii> Q;
	Q.push({R, {S, P}});
	prob[R][S][P] = 1;
	while (!Q.empty())
	{
		auto top = Q.front();
		Q.pop();
		int r = top.f, s = top.s.f, p = top.s.s;
		db(r, s, p, prob[r][s][p]);
		// prob[]
		// vis[r][s][p] = true;
		if (r >= 1 && s >= 1) // rock meet scissor
		{
			ld P = (ld)r * s / (r * s + s * p + r * p);
			prob[r][s - 1][p] += P * prob[r][s][p];
			// db(P);
			if (!vis[r][s - 1][p])
			{
				vis[r][s - 1][p] = true;
				Q.push({r, {s - 1, p}});
			}
		}
		if (r >= 1 && p >= 1) // rock meet paper
		{
			ld P = (ld)r * p / (r * s + s * p + r * p);
			// db(P);
			prob[r - 1][s][p] += P * prob[r][s][p];
			if (!vis[r - 1][s][p])
			{
				vis[r - 1][s][p] = true;
				Q.push({r - 1, {s, p}});
			}
		}
		if (p >= 1 && s >= 1) // scissor meet paper
		{
			ld P = (ld)p * s / (r * s + s * p + r * p);
			// db(P);
			prob[r][s][p - 1] += P * prob[r][s][p];
			if (!vis[r][s][p - 1])
			{
				vis[r][s][p - 1] = true;
				Q.push({r, {s, p - 1}});
			}
		}
	}
	ld a = 0, b = 0, c = 0;
	for (int i = 0; i <= R; ++i)
		a += prob[i][0][0];
	// cout << a << ' ';
	// a = 0;
	for (int i = 0; i <= S; ++i)
		b += prob[0][i][0];
	// cout << a << ' ';
	// a = 0;
	for (int i = 0; i <= P; ++i)
		c += prob[0][0][i];
	// cout << a << ' ';
	db(a + b + c);
	cout << fixed << setprecision(12);
	cout << a / (a + b + c) << ' ' << b / (a + b + c) << ' ' << c / (a + b + c) << '\n';
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