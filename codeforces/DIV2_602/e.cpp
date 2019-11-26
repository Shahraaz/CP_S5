//Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define multitest 1
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
using T = pair<int, int>;
using pbds = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define f first
#define s second
#define pb push_back
auto TimeStart = chrono::steady_clock::now();

const int nax = 2e6 + 10, mod = 1000000007;

int n, m;
string a[nax];
vector<vector<int>> v, v2;
vector<vector<bool>> mark;

void precompute()
{
    v = v2 = vector<vector<int>>(n + 2, vector<int>(m + 2));
    mark = vector<vector<bool>>(n + 2, vector<bool>(m + 2));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            v[i][j] = v[i][j - 1] + (a[i][j] == 'X');
    for (int j = 1; j <= m; ++j)
        for (int i = 1; i <= n; ++i)
            v[i][j] += v[i - 1][j];
}

int get(int x1, int y1, int x2, int y2)
{
    return v[x2][y2] - v[x2][y1 - 1] - v[x1 - 1][y2] + v[x1 - 1][y1 - 1];
}

bool check(int t)
{
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            mark[i][j] = v2[i][j] = 0;
    for (int i = t + 1; i + t <= n; ++i)
        for (int j = t + 1; j + t <= m; ++j)
        {
            int cnt = get(i - t, j - t, i + t, j + t);
            if (cnt == (2 * t + 1) * (2 * t + 1))
            {
                mark[i][j] = 1;
                v2[i - t][j - t] += 1;
                v2[i + t + 1][j + t + 1] += 1;
                v2[i + t + 1][j - t] -= 1;
                v2[i - t][j + t + 1] -= 1;
            }
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            v2[i][j] += v2[i][j - 1];
    for (int j = 1; j <= m; ++j)
        for (int i = 1; i <= n; ++i)
            v2[i][j] += v2[i - 1][j];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            int isBurnt = (v2[i][j] > 0);
            int shouldBeBurnt = (a[i][j] == 'X');
            if (isBurnt != shouldBeBurnt)
                return false;
        }
    return true;
}

int binarySearch(int low, int high)
{
    int ans = low;
    while (low <= high)
    {
        db(low, high);
        int mid = (low + high) / 2;
        if (check(mid))
            ans = mid, low = mid + 1;
        else
            high = mid - 1;
        db(mid, ans);
    }
    check(ans);
    return ans;
}

void solve(int caseNo)
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        a[i] = '$' + a[i];
        db(a[i]);
    }
    precompute();
    int ans = binarySearch(0, min(n, m));
    cout << ans << '\n';
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
            cout << (mark[i][j] ? 'X' : '.');
        cout << '\n';
    }
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