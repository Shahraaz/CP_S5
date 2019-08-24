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

const int nax = 2e5 + 10, phi = 3;
int n, m;

struct node
{
	node *next[phi];
	bool end;
	node()
	{
		memset(next, NULL, sizeof(next));
		end = false;
	}
};

struct Trie
{
	node *root;
	Trie()
	{
		root = new node;
	}
	void insert(const string &s)
	{
		node *curr = root;
		for (auto ch : s)
		{
			// db(ch);
			if (curr->next[ch - 'a'] == NULL)
				curr->next[ch - 'a'] = new node;
			curr = curr->next[ch - 'a'];
		}
		curr->end = true;
	}
	bool find(const string &s, node *curr, int mismatch = 0, int i = 0)
	{
		if (curr == NULL)
			return false;
		if (i == s.length())
			return mismatch == 0 && curr->end;
		bool ans = false;
		for (int j = 0; j < phi; ++j)
			if (j == (s[i] - 'a'))
				ans |= find(s, curr->next[j], mismatch, i + 1);
			else if (mismatch > 0)
				ans |= find(s, curr->next[j], mismatch - 1, i + 1);
		return ans;
	}
	bool solve(const string &s)
	{
		return find(s, root, 1, 0);
	}
};

Trie trie;

void solve()
{
	cin >> n >> m;
	string s;
	while (n--)
	{
		cin >> s;
		trie.insert(s);
	}
	while (m--)
	{
		cin >> s;
		if (trie.solve(s))
			cout << "YES\n";
		else
			cout << "NO\n";
	}
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