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

void solve(int caseNo)
{
	int n, m, x, y;
	cin >> n >> m;
	map<int, vector<pair<int, int>>> Diag1, Diag2;
	vector<vector<pair<int, int>>> Row(n), Col(n);
	for (int i = 0; i < m; ++i)
	{
		cin >> x >> y;
		--x, --y;
		Row[x].pb({x, y});
		Col[y].pb({x, y});
		Diag1[x + y].pb(make_pair(x, y));
		Diag2[x - y].pb(make_pair(x, y));
	}
	vector<int> t(9);
	for (auto &elem : Row)
		sort(elem.begin(), elem.end());
	for (auto &elem : Col)
		sort(elem.begin(), elem.end());
	for (auto &elem : Diag1)
		sort(elem.s.begin(), elem.s.end());
	for (auto &elem : Diag2)
		sort(elem.s.begin(), elem.s.end());
	for (auto &elem : Row)
		for (auto elem2 : elem)
		{
			int cnt = 0;
			auto it = lower_bound(elem.begin(), elem.end(), elem2);
			cnt += it != elem.begin();
			++it;
			cnt += it != elem.end();
			db(cnt);
			/////////////////////////////////////////////////////////
			it = lower_bound(Col[elem2.s].begin(), Col[elem2.s].end(), elem2);
			cnt += it != Col[elem2.s].begin();
			++it;
			cnt += it != Col[elem2.s].end();
			db(cnt);
			//////////////////////////////////////////////////////////
			{
				int a = elem2.f + elem2.s;
				auto it = lower_bound(Diag1[a].begin(), Diag1[a].end(), elem2);
				cnt += it != Diag1[a].begin();
				++it;
				cnt += it != Diag1[a].end();
			}
			db(cnt);
			///////////////////////////////////////////////////////////
			{
				int a = elem2.f - elem2.s;
				auto it = lower_bound(Diag2[a].begin(), Diag2[a].end(), elem2);
				cnt += it != Diag2[a].begin();
				++it;
				cnt += it != Diag2[a].end();
			}
			db(cnt);
			db(elem2);
			t[cnt]++;
		}
	for (auto elem : t)
		cout << elem << ' ';
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
	for (int i = 0; i < t; ++i)
		solve(i);
#ifdef TIME
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}