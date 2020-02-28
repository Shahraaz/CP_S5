// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define MULTI_TEST
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
#define all(v) v.begin(), v.end()
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 5e3 + 5, MOD = 1000000007;

int answer[NAX][NAX];
class Solution
{
private:
    // int n;
    int que(int x, int y)
    {
        if (answer[x][y] >= 0)
            return answer[x][y];
        cout << "? " << x << ' ' << y << endl;
        int res;
        cin >> res;
        return answer[x][y] = res;
    }
    bool smart_test(vector<int> p)
    {
        int n = p.size();
        vector<int> b(n);
        for (size_t i = 0; i < n; i++)
            b[p[i]] = i;
        for (int i = 0; i < n; i++)
            if (que(0, i) != (p[0] ^ b[i]))
                return false;
        for (int i = 0; i < n; i++)
            if (que(i, 0) != (p[i] ^ b[0]))
                return false;
        return true;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        int answer_cnt = 0;
        memset(answer, -1, sizeof answer);
        vector<int> ans;
        vector<int> p(n), t(n);
        for (int b0 = 0; b0 < n; b0++)
        {
            int flag = 1;
            fill(all(t), 0);
            for (int i = 0; i < n; i++)
            {
                p[i] = que(i, 0) ^ b0;
                if (p[i] > n || t[p[i]])
                {
                    flag = 0;
                    break;
                }
                t[p[i]] = 1;
            }
            if (flag && smart_test(p))
            {
                ++answer_cnt;
                if (ans.size() == 0)
                    ans = p;
            }
        }

        cout << "!" << '\n';
        cout << answer_cnt << '\n';
        for (auto &x : ans)
            cout << x << ' ';
        cout << endl;
    }
};

int32_t main()
{
#ifndef LOCAL
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
#endif
    int t = 1;
#ifdef MULTI_TEST
    cin >> t;
#endif
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
