//Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define MULTI_TEST
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
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define f first
#define s second
#define pb push_back
auto TimeStart = chrono::steady_clock::now();

const int NAX = 2e5 + 10, MOD = 1000000007;

void solveCase(int caseNo)
{
    int n;
    cin >> n;
    map<string, vector<int>> p;
    set<string> exist;
    for (int i = 0; i < n; ++i)
    {
        string str;
        exist.insert(str);
        cin >> str;
        p[str].pb(i);
    }
    vector<string> ret(n);
    int ans = 0;
    for (auto elem : p)
    {
        if (elem.s.size() == 1)
        {
            ret[elem.s[0]] = elem.f;
        }
        else
        {
            auto str = elem.f;
            int pos = 4, cnt = 0;

            for (int i = 0; i < elem.s.size(); ++i)
            {
                while (exist.count(str))
                {
                    if (cnt == 10)
                    {
                        pos--;
                        cnt = -1;
                    }
                    else if (str[pos] == '9')
                        str[pos] = '0';
                    else
                        str[pos] = str[pos] + 1;
                    cnt++;
                }
                db(str,elem.s[i]);
                ret[elem.s[i]] = str;
                exist.insert(str);
                ans++;
            }
            ans--;
        }
    }
    cout << ans << '\n';
    for (auto elem : ret)
        cout << elem << '\n';
}

int main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
#ifdef MULTI_TEST
    cin >> t;
#endif
    for (int i = 0; i < t; ++i)
        solveCase(i);
#ifdef TIME
    cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
    return 0;
}