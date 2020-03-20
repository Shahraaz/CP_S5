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
        string str;
        cin >> str;
        db(str);
        if (str.length() == 2)
        {
            int cnt = count(all(str), '?');
            if (cnt == 0)
            {
                cout << str << '\n';
            }
            else
            {
                if (cnt == 1)
                {
                    for (size_t i = 0; i < 2; i++)
                    {
                        if (str[i] == '?')
                        {
                            str[i] = '0';
                            cout << str << '\n';
                            str[i] = '1';
                            cout << str << '\n';
                        }
                    }
                }
                else
                {
                    cout << "00\n01\n10\n11\n ";
                }
            }
            return;
        }
        else
        {
            int zeroCnt = count(all(str), '0');
            int oneCnt = count(all(str), '1');
            int quesCnt = count(all(str), '?');
            db(str, zeroCnt, oneCnt, quesCnt);
            if ((oneCnt) < (zeroCnt + quesCnt))
                cout << "00\n";
            if (quesCnt > 0)
            {
                if (str.back() == '1' || str.back() == '?')
                {
                    if (str.back() == '?')
                    {
                        oneCnt++;
                        quesCnt--;
                    }
                    int twoX = zeroCnt + quesCnt - oneCnt + (str.length() % 2);
                    db(twoX);
                    if (twoX % 2 == 0)
                    {
                        twoX /= 2;
                        if (0 <= twoX && twoX <= quesCnt)
                            cout << "01\n";
                    }
                    if (str.back() == '?')
                    {
                        oneCnt--;
                        quesCnt++;
                    }
                }

                if (str.back() == '0' || str.back() == '?')
                {
                    if (str.back() == '?')
                    {
                        zeroCnt++;
                        quesCnt--;
                    }
                    int twoX = zeroCnt + quesCnt - oneCnt + (str.length() % 2);
                    db(twoX);
                    if (twoX % 2 == 0)
                    {
                        twoX /= 2;
                        if (0 <= twoX && twoX <= quesCnt)
                            cout << "10\n";
                    }
                    if (str.back() == '?')
                    {
                        zeroCnt--;
                        quesCnt++;
                    }
                }
            }
            else
            {
                if (oneCnt == zeroCnt || oneCnt == (zeroCnt + 1))
                {
                    if (str.back() == '0')
                        cout << "10\n";
                    else
                        cout << "01\n";
                }
            }

            if ((oneCnt + quesCnt) > (1 + zeroCnt))
                cout << "11\n";
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