//Optimise
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

const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase(int caseNo)
{
    int t;
    cin >> t;
    vector<pair<int, bool>> intervals;
    int last_minute = 24 * 60 * 7;
    for (int i = 0; i < 7; ++i)
    {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j)
        {
            string time;
            cin >> time;
            int hr = time[0] - '0';
            hr = hr * 10 + time[1] - '0';
            int mn = time[3] - '0';
            mn = mn * 10 + time[4] - '0';
            // db("start", hr, mn);
            intervals.pb({(i * 24 * 60 + hr * 60 + mn - t * 60 + last_minute) % last_minute, 0});
            cin >> time;
            hr = time[0] - '0';
            hr = hr * 10 + time[1] - '0';
            mn = time[3] - '0';
            mn = mn * 10 + time[4] - '0';
            // db("end", hr, mn);
            if (hr == 0 && mn == 0)
                hr = 24;
            intervals.pb({(i * 24 * 60 + hr * 60 + mn - t * 60 + last_minute) % last_minute, 1});
        }
    }
    sort(all(intervals));
    pc(intervals);
    vector<pair<pair<int, int>, bool>> Day[7];
    vector<pair<pair<int, int>, pair<int, int>>> res[7];
    bool b = false;
    for (int i = 0; i < intervals.size(); ++i)
    {
        if (b)
        {
            b = false;
            continue;
        }
        auto elem = intervals[i];
        if (i != intervals.size() - 1)
        {
            if (elem.f == intervals[i + 1].f)
            {
                b = true;
                continue;
            }
        }
        int tt = elem.f;
        tt %= (24 * 60);
        Day[elem.f / (24 * 60)].pb({{tt / 60, tt % 60}, elem.s});
    }
    for (int i = 0; i < 7; ++i)
    {
        // db(i);
        // pc(Day[i]);
        int n = Day[i].size();
        int prevMin, prevHr;
        bool exist = false;
        for (int j = 0; j < n; ++j)
        {
            if (j == 0)
            {
                if (Day[i][j].s == 0)
                {
                    exist = true;
                    prevHr = Day[i][j].f.f == 24 ? 0 : Day[i][j].f.f;
                    prevMin = Day[i][j].f.s;
                    continue;
                }
                else
                {
                    res[i].pb({{0, 0}, {Day[i][j].f.f == 24 ? 0 : Day[i][j].f.f, Day[i][j].f.s}});
                    continue;
                }
            }
            if (j == n - 1)
            {
                if (Day[i][j].s == 1)
                {
                    if (exist)
                    {
                        exist = false;
                        res[i].pb({{prevHr, prevMin}, {Day[i][j].f.f == 24 ? 0 : Day[i][j].f.f, Day[i][j].f.s}});
                        continue;
                    }
                    else
                    {
                        res[i].pb({{0, 0}, {Day[i][j].f.f == 24 ? 0 : Day[i][j].f.f, Day[i][j].f.s}});
                        continue;
                    }
                }
                else
                {
                    exist = false;
                    res[i].pb({{Day[i][j].f.f == 24 ? 0 : Day[i][j].f.f, Day[i][j].f.s}, {0, 0}});
                    continue;
                }
            }
            if (Day[i][j].s)
            {
                res[i].pb({{prevHr, prevMin}, {Day[i][j].f.f == 24 ? 0 : Day[i][j].f.f, Day[i][j].f.s}});
                exist = false;
            }
            else
            {
                exist = true;
                prevHr = Day[i][j].f.f == 24 ? 0 : Day[i][j].f.f;
                prevMin = Day[i][j].f.s;
            }
        }
        if (exist)
        {
            res[i].pb({{prevHr, prevMin}, {0, 0}});
            db("a");
        }
    }
    for (int i = 0; i < 7; ++i)
    {
        sort(all(res[i]));
        res[i].erase(unique(all(res[i])), res[i].end());
        vector<pair<pair<int, int>, pair<int, int>>> temp;
        for (auto elem : res[i])
        {
            if (elem.f == elem.s)
                continue;
            temp.pb(elem);
        }
        res[i] = temp;
    }
    for (int i = 0; i < 7; ++i)
    {
        printf("%d\n", res[i].size());
        for (auto elem : res[i])
        {
            printf("%02d:%02d %02d:%02d\n", elem.f.f, elem.f.s, elem.s.f, elem.s.s);
        }
    }
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
    for (int i = 1; i <= t; ++i)
    {
        solveCase(i);
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}