#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
using ll = long long;
const int NAX = 2e5 + 5, MOD = 1000000007;

#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
using ll = long long;

struct Hash_RabinKarp
{
    const int maxSize = 1e6 + 10;
    const long long p1 = 805306457, p2 = 101, p3 = 31;
    const int mod1 = 1610612741, mod2 = 2100003221, mod3 = 1e9 + 9;
    vector<long long> p_pow1, p_pow2, p_pow3;
    vector<long long> inv_pow1, inv_pow2, inv_pow3;
    ll expo(ll base, int index, int mod)
    {
        if (index == 0)
            return 1;
        ll temp = expo(base, index / 2, mod);
        temp = (temp * temp) % mod;
        if (index & 1)
            temp = (temp * base) % mod;
        return temp;
    }
    Hash_RabinKarp()
    {
        p_pow1.resize(maxSize);
        p_pow2.resize(maxSize);
        p_pow3.resize(maxSize);
        inv_pow1.resize(maxSize);
        inv_pow2.resize(maxSize);
        inv_pow3.resize(maxSize);
        p_pow1[0] = p_pow2[0] = p_pow3[0] = 1;
        for (int i = 1; i < (int)p_pow1.size(); i++)
        {
            p_pow1[i] = (p_pow1[i - 1] * p1) % mod1;
            p_pow2[i] = (p_pow2[i - 1] * p2) % mod2;
            p_pow3[i] = (p_pow3[i - 1] * p3) % mod3;
        }
        inv_pow1[maxSize - 1] = expo(p_pow1[maxSize - 1], mod1 - 2, mod1);
        inv_pow2[maxSize - 1] = expo(p_pow2[maxSize - 1], mod2 - 2, mod2);
        inv_pow3[maxSize - 1] = expo(p_pow3[maxSize - 1], mod3 - 2, mod3);
        for (int i = maxSize - 2; i >= 0; --i)
        {
            inv_pow1[i] = (inv_pow1[i + 1] * p1) % mod1;
            inv_pow2[i] = (inv_pow2[i + 1] * p2) % mod2;
            inv_pow3[i] = (inv_pow3[i + 1] * p3) % mod3;
        }
    }
} hashTables;

struct Rabin_Karp
{
    int valLen, n;
    Rabin_Karp()
    {
        valLen = 0;
    }
    Rabin_Karp(string str)
    {
        prepareString(str);
    }
    vector<pair<long long, pair<long long, long long>>> hashUptoIndex;
    pair<long long, pair<long long, long long>> getHash(int startIndex, int endIndex)
    {
        if (startIndex > endIndex || startIndex < 0 || startIndex >= valLen || endIndex < 0 || endIndex >= valLen)
            return {0, {0, 0}};
        long long a = (hashUptoIndex[endIndex].f - (startIndex ? hashUptoIndex[startIndex - 1].f : 0) + hashTables.mod1) % hashTables.mod1;
        long long b = (hashUptoIndex[endIndex].s.f - (startIndex ? hashUptoIndex[startIndex - 1].s.f : 0) + hashTables.mod2) % hashTables.mod2;
        long long c = (hashUptoIndex[endIndex].s.s - (startIndex ? hashUptoIndex[startIndex - 1].s.s : 0) + hashTables.mod3) % hashTables.mod3;
        a = (a * hashTables.inv_pow1[startIndex]) % hashTables.mod1;
        b = (b * hashTables.inv_pow2[startIndex]) % hashTables.mod2;
        c = (c * hashTables.inv_pow3[startIndex]) % hashTables.mod3;
        auto ret = make_pair(a, make_pair(b, c));
        return ret;
    }
    int c2i(char c)
    {
        if ('0' <= c <= '9')
            return c - '0';
        if ('a' <= c <= 'z')
            return c - 'a' + 10;
        return c - 'A' + 36;
    }
    void prepareString(string text)
    {
        n = text.size();
        valLen = n;
        hashUptoIndex.resize(n);
        for (int i = 0; i < n; ++i)
        {
            hashUptoIndex[i].f = (((i > 0) ? (hashUptoIndex[i - 1].f) : (0)) + c2i(text[i]) * hashTables.p_pow1[i]) % hashTables.mod1;
            hashUptoIndex[i].s.f = (((i > 0) ? (hashUptoIndex[i - 1].s.f) : (0)) + c2i(text[i]) * hashTables.p_pow2[i]) % hashTables.mod2;
            hashUptoIndex[i].s.s = (((i > 0) ? (hashUptoIndex[i - 1].s.s) : (0)) + c2i(text[i]) * hashTables.p_pow3[i]) % hashTables.mod3;
        }
    }
    void add(char c)
    {
        int i = n;
        ++valLen;
        hashUptoIndex.pb({0, {0, 0}});
        db(i, c);
        ++n;
        {
            hashUptoIndex[i].f = (((i > 0) ? (hashUptoIndex[i - 1].f) : (0)) + c2i(c) * hashTables.p_pow1[i]) % hashTables.mod1;
            hashUptoIndex[i].s.f = (((i > 0) ? (hashUptoIndex[i - 1].s.f) : (0)) + c2i(c) * hashTables.p_pow2[i]) % hashTables.mod2;
            hashUptoIndex[i].s.s = (((i > 0) ? (hashUptoIndex[i - 1].s.s) : (0)) + c2i(c) * hashTables.p_pow3[i]) % hashTables.mod3;
        }
    }
};

Rabin_Karp R;
string str;

void addString(string &rhs)
{
    int curr_end_ptr = str.size() - 1;
    int rhs_sz = rhs.size();
    Rabin_Karp R2;
    R2.prepareString(rhs);
    int longestMatch = 0;
    for (int i = 1; i <= rhs_sz; i++)
    {
        int start_ptr = curr_end_ptr - i + 1;
        db(start_ptr, curr_end_ptr, i);
        if (start_ptr >= 0)
        {
            db(R.getHash(start_ptr, curr_end_ptr));
            db(R2.getHash(0, i - 1));
            if (R.getHash(start_ptr, curr_end_ptr) == R2.getHash(0, i - 1))
                longestMatch = i;
        }
    }
    db(str, rhs, longestMatch);
    for (size_t i = longestMatch; i < rhs_sz; i++)
    {
        str += rhs[i];
        R.add(rhs[i]);
    }
}

void solveCase()
{
    int n;
    cin >> n;
    cin >> str;
    R.prepareString(str);
    for (size_t i = 1; i < n; i++)
    {
        string str2;
        cin >> str2;
        addString(str2);
    }
    cout << str << '\n';
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
        solveCase();
    return 0;
}