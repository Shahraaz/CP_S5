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
const long long mod = 1000000007;
auto TimeStart = chrono::steady_clock::now();

const int nax = 1e3 + 10;

using ld = long double;
ld prob[2], dp[nax][nax][2], stateProb[nax][nax][2];
bool vis[nax][nax][2];
#define princess 0
#define dragon 1

struct turn
{
	bool who;
	int w, b;
	turn(int w, int b, bool who) : w(w), b(b), who(who) {}
};
ostream &operator<<(ostream &out, const turn &p)
{
	out << "w " << p.w << " b " << p.b << ' ';
	switch (p.who)
	{
	case princess:
		out << "Princess ";
		break;

	default:
		out << "Dragon ";
		break;
	}
	out << stateProb[p.w][p.b][p.who];
	return out;
}

ld getProb(int a, int b)
{
	if ((a + b) == 0)
		return 0;
	return (ld)a / (a + b);
}

void solve()
{
	int w, b;
	cin >> w >> b;
	queue<turn> Q;
	Q.push(turn(w, b, princess));
	vis[w][b][princess] = true;
	stateProb[w][b][princess] = (ld)1;
	while (!Q.empty())
	{
		auto top = Q.front();
		Q.pop();
		// db(top.w, top.b, top.who, stateProb[top.w][top.b][top.who]);
		db(top);
		switch (top.who)
		{
		case princess:
			prob[princess] += stateProb[top.w][top.b][top.who] * getProb(top.w, top.b);
			if (top.b > 0)
			{
				stateProb[top.w][top.b - 1][1 - top.who] += stateProb[top.w][top.b][top.who] * getProb(top.b, top.w);
				if (!vis[top.w][top.b - 1][1 - top.who])
				{
					vis[top.w][top.b - 1][1 - top.who] = true;
					Q.push(turn(top.w, top.b - 1, 1 - top.who));
				}
			}
			break;
		case dragon:
			prob[dragon] += stateProb[top.w][top.b][top.who] * getProb(top.w, top.b);
			if (top.b > 0)
			{
				ld temp = getProb(top.b, top.w);
				db(temp, top.b, top.w);
				top.b--;
				if (top.b > 0)
				{
					stateProb[top.w][top.b - 1][1 - top.who] += stateProb[top.w][top.b + 1][top.who] * getProb(top.b, top.w) * temp;
					if (!vis[top.w][top.b - 1][1 - top.who])
					{
						vis[top.w][top.b - 1][1 - top.who] = true;
						Q.push(turn(top.w, top.b - 1, 1 - top.who));
					}
				}
				if (top.w > 0)
				{
					stateProb[top.w - 1][top.b][1 - top.who] += stateProb[top.w][top.b + 1][top.who] * getProb(top.w, top.b) * temp;
					if (!vis[top.w - 1][top.b][1 - top.who])
					{
						vis[top.w - 1][top.b][1 - top.who] = true;
						Q.push(turn(top.w - 1, top.b, 1 - top.who));
					}
				}
			}
			break;

		default:
			break;
		}
	}
	cout << fixed << setprecision(10);
	cout << prob[princess] << '\n';
}

int main()
{
#ifndef WIN32
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout << fixed << setprecision(10);
	cerr << fixed << setprecision(10);
#endif
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