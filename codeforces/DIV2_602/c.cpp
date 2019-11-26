//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
#ifdef LOCAL
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
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    string t;
    --k;
    while (t.length() < n)
    {
        if (k > 0)
        {
            t += "()";
            --k;
        }
        else
        {
            int rem = (n - t.length()) / 2;
            for (int i = 0; i < rem; ++i)
                t += "(";
            for (int i = 0; i < rem; ++i)
                t += ")";
        }
    }
    db(s, t);
    vector<pair<int, int>> res;
    for (int i = 0; i < n; ++i)
    {
        if (s[i] == t[i])
            continue;
        for (int j = i + 1; j < n; ++j)
        {
            if (s[j] == t[i])
            {
                res.pb({i, j});
                reverse(s.begin() + i, s.begin() + j + 1);
                break;
            }
        }
    }
    db(s, t);
    cout << res.size() << '\n';
    for (auto elem : res)
        cout << elem.f + 1 << ' ' << elem.s + 1 << '\n';
}

int main()
{
#ifndef LOCAL
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