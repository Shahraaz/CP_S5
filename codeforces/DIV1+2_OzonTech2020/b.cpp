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

const int NAX = 2e5 + 5, MOD = 1000000007;

class Solution
{
    vector<int> temp;

private:
    // int len(vector<pair<char, int>> inp)
    // {
    //     temp.clear();
    //     int sum = 0;
    //     int maxi = 0;

    //     // Traversing the string.
    //     for (int i = 0; i < n; i++)
    //     {

    //         // If open bracket add 1 to sum.
    //         if (inp[i].f == '(')
    //             sum += 1;

    //         // If closed bracket subtract 1
    //         // from sum
    //         else if (inp[i].f == ')')
    //             sum -= 1;

    //         // If sum is 0, store the index
    //         // value.
    //         if (sum == 0)
    //             maxi = i;
    //     }

    //     return maxi + 1;
    // }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        string str;
        cin >> str;
        auto str2 = str;
        if (count(all(str2), '(') == str.size() || count(all(str2), ')') == str.size())
        {
            cout << 0;
            return;
        }
        vector<vector<int>> res;
        vector<pair<char, int>> inp;
        for (int i = 0; i < str.size(); i++)
            inp.pb({str[i], i});
        while (true)
        {
            vector<int> posOpen;
            vector<int> closeOpen;
            vector<int> match;
            for (int i = 0; i < str.size(); i++)
            {
                if (str[i] == '(')
                {
                    posOpen.pb(i);
                }
                if (str[i] == ')')
                {
                    closeOpen.pb(i);
                    // if (posOpen.size())
                    // {
                    //     match.pb(posOpen.back());
                    //     str[posOpen.back()] = '$';
                    //     posOpen.pop_back();
                    //     match.pb(closeOpen.back());
                    //     str[closeOpen.back()] = '$';
                    //     closeOpen.pop_back();
                    // }
                }
            }
            int idx = -1, len = 0;
            for (size_t i = 0; i < posOpen.size(); i++)
            {
                if ((closeOpen.size() - (lower_bound(all(closeOpen), posOpen[i]) - closeOpen.begin())) >= (i + 1))
                {
                    idx = i;
                    len = i + 1;
                }
            }
            if (len == 0)
                break;
            for (int i = 0; i < len; i++)
            {
                match.pb(posOpen[i]);
                str[posOpen[i]] = '$';
            }
            reverse(all(closeOpen));
            for (int i = 0; i < len; i++)
            {
                match.pb(closeOpen[i]);
                str[closeOpen[i]] = '$';
            }
            if (match.size() == 0)
                break;
            res.pb(match);
        }
        cout << res.size() << '\n';
        for (auto &elem : res)
        {
            cout << elem.size() << '\n';
            sort(all(elem));
            for (auto &e : elem)
            {
                cout << e + 1 << ' ';
            }
            cout << '\n';
        }
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
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
