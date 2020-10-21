// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    string randomzd, substr;
    cin >> randomzd >> substr;
    int sz = randomzd.size();
    string res;
    vector<int> hash(10);
    for (auto &x : randomzd)
        hash[x - '0']++;
    for (auto &x : substr)
        hash[x - '0']--;
    auto gen = [&](int len) -> string {
        auto LEN = to_string(len);
        db(len, LEN);
        auto hash1 = hash;
        for (auto &x : LEN)
        {
            hash1[x - '0']--;
            if (hash1[x - '0'] < 0)
                return "";
        }
        if (substr.front() == '0')
            return "";
        string ret;
        ret = substr;
        for (size_t i = 0; i < 10; i++)
            while (hash1[i]--)
                ret += to_string(i);
        return ret;
    };
    auto gen1 = [&](int len) -> string {
        auto LEN = to_string(len);
        db(len, LEN);
        auto hash1 = hash;
        for (auto &x : LEN)
        {
            hash1[x - '0']--;
            if (hash1[x - '0'] < 0)
                return "";
        }
        string ret;
        for (size_t i = 1; i < 10; i++)
            if (hash1[i])
            {
                ret += to_string(i);
                hash1[i]--;
                break;
            }
        if (ret.empty())
            return "";
        for (size_t i = 0; i < (substr.front() - '0'); i++)
            while (hash1[i])
            {
                ret += to_string(i);
                hash1[i]--;
            }
        ret += substr;
        for (size_t i = 0; i < 10; i++)
            while (hash1[i])
            {
                ret += to_string(i);
                hash1[i]--;
            }
        return ret;
    };
    auto gen2 = [&](int len) -> string {
        auto LEN = to_string(len);
        db(len, LEN);
        auto hash1 = hash;
        for (auto &x : LEN)
        {
            hash1[x - '0']--;
            if (hash1[x - '0'] < 0)
                return "";
        }
        string ret;
        for (size_t i = 1; i < 10; i++)
            if (hash1[i])
            {
                ret += to_string(i);
                hash1[i]--;
                break;
            }
        if (ret.empty())
            return "";
        for (size_t i = 0; i <= (substr.front() - '0'); i++)
            while (hash1[i])
            {
                ret += to_string(i);
                hash1[i]--;
            }
        ret += substr;
        for (size_t i = 0; i < 10; i++)
            while (hash1[i])
            {
                ret += to_string(i);
                hash1[i]--;
            }
        return ret;
    };
    for (int i = 1; i < 7; i++)
    {
        int len = sz - i;
        if (len > 0 && to_string(len).size() == i)
        {
            auto temp = gen(len);
            if (temp.size())
                if (res.empty() || res.size() > temp.size() || (res.size() == temp.size() && res > temp))
                    res = temp;
            temp = gen1(len);
            if (temp.size())
                if (res.empty() || res.size() > temp.size() || (res.size() == temp.size() && res > temp))
                    res = temp;
            temp = gen2(len);
            if (temp.size())
                if (res.empty() || res.size() > temp.size() || (res.size() == temp.size() && res > temp))
                    res = temp;
        }
    }
    if (res.empty())
        res = "0";
    cout << res << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}