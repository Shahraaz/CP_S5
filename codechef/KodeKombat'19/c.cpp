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
vector<string> May;

struct Node
{
	vector<Node *> Child;
	Node()
	{
		Child.resize(26, NULL);
	}
};

int m;
int n;
string s;
bool vis[20][20][20];
void makeTrie(int x, int y, int i)
{
	if (i == m)
	{
		cout << "Yes\n";
		exit(0);
	}
	if (x == n || y == n)
		return;
	if (vis[x][y][i])
		return;
	vis[x][y][i] = true;
	makeTrie(x + 1, y + 1, 0);
	makeTrie(x + 1, y, 0);
	makeTrie(x, y + 1, 0);
	if (s[0] == May[x][y])
	{
		makeTrie(x + 1, y + 1, 1);
		makeTrie(x + 1, y, 1);
		makeTrie(x, y + 1, 1);
	}
	if (s[i] == May[x][y])
	{
		makeTrie(x + 1, y + 1, i + 1);
		makeTrie(x + 1, y, i + 1);
		makeTrie(x, y + 1, i + 1);
	}
}

void solve()
{
	cin >> n;
	May.resize(n);
	for (auto &x : May)
		cin >> x;
	cin >> m >> s;
	makeTrie(0, 0, 0);
	cout << "No";
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
#endif
	return 0;
}