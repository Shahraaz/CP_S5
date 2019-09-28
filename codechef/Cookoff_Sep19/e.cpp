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
vector<int> Adj[nax];
bool wt[nax];
int n;
int zcnt[nax], ocnt[nax];
// ll dp[nax];
// vector<pair<int, pair<int, int>>> Cnt[nax];
// map<pair<int, int>, pair<int, int>> SS;

bool cmp(pair<int, int> a, pair<int, int> b)
{
	return (ll)a.f * b.s > (ll)a.s * b.f;
}

ll dfsa(int node, int par = -1)
{
	zcnt[node] = !wt[node];
	ocnt[node] = wt[node];
	// swap(zcnt)
	vector<pair<int, int>> C;
	ll ret = 0;
	for (auto c : Adj[node])
		if (c != par)
		{
			ret += dfsa(c, node);
			C.pb({zcnt[c], ocnt[c]});
			zcnt[node] += zcnt[c];
			ocnt[node] += ocnt[c];
		}
	pc(C);
	sort(C.begin(), C.end(),cmp);
	pc(C);
	ll z = 0;
	for (int i = 0; i < C.size(); ++i)
		z += C[i].f;
	// int one = 0;
	for (int i = 0; i < C.size(); ++i)
	{
		z -= C[i].f;
		ret += (ll)C[i].s * z;
		// SS[{node, i}] = {one, z};
		// one += C[i].s;
	}
	if (wt[node])
		ret += zcnt[node];
	// Cnt[node] = C;
	return ret;
}

void solve()
{
	// SS.clear();
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		Adj[i].clear();
		cin >> wt[i];
		// wt[i] = !wt[i];
	}
	int a, b;
	for (int i = 1; i < n; ++i)
	{
		cin >> a >> b;
		--a, --b;
		Adj[a].pb(b);
		Adj[b].pb(a);
	}
	cout << dfsa(0) << '\n';
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