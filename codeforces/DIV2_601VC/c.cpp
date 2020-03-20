// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define MULTI_TEST
#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#define pc(...)
#endif

#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()
auto TimeStart = chrono::steady_clock::now();
auto seed = TimeStart.time_since_epoch().count();
std::mt19937 rng(seed);
using ll = long long;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using Random = std::uniform_int_distribution<T>;

const int NAX = 2e5 + 5, MOD = 1000000007;

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        map<int, map<int, int>> mp;
        vector<int> cnt(n + 1);
        for (size_t i = 0; i < n - 2; i++)
        {
            int x, y, z;
            cin >> x >> y >> z;
            cnt[x]++;
            cnt[y]++;
            cnt[z]++;

            mp[x][y]++;
            mp[y][x]++;

            mp[x][z]++;
            mp[z][x]++;

            mp[y][z]++;
            mp[z][y]++;
        }
        int first = min_element(cnt.begin() + 1, cnt.end()) - cnt.begin();
        // db(first);
        // pc(cnt);
        while (n--)
        {
            db(first);
            if ((n + 1) == 2)
            {
                // db("a");
                cout << first << ' ';
                cout << ((++mp[first].begin())->f) << ' ';
                break;
            }
            else
            {
                // db("b");
                cout << first << ' ';
                vector<int> temp;
                for (auto &elem : mp[first])
                {
                    temp.pb(elem.f);
                    mp[elem.f][first]--;
                    if (mp[elem.f][first] == 0)
                        mp[elem.f].erase(first);
                }
                mp.erase(first);
                pc(temp);
                if (mp[temp[0]].size() > mp[temp[1]].size())
                    first = temp[1];
                else
                    first = temp[0];
            }
#ifdef LOCAL
            for (auto &elem : mp)
            {
                db(elem.f);
                pc(elem.s);
            }
#else

#endif
            db("----------------");
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