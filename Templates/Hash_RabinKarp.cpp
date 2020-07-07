#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
using ll = long long;

struct Hash_RabinKarp
{
    const int maxSize = 1e6 + 10;
    const long long p1 = 805306457, p2 = 29, p3 = 31;
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
    int valLen;
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
    void prepareString(string text)
    {
        int n = text.size();
        valLen = n;
        hashUptoIndex.resize(n);
        for (int i = 0; i < n; ++i)
        {
            hashUptoIndex[i].f = (((i > 0) ? (hashUptoIndex[i - 1].f) : (0)) + (text[i] - 'a' + 1) * hashTables.p_pow1[i]) % hashTables.mod1;
            hashUptoIndex[i].s.f = (((i > 0) ? (hashUptoIndex[i - 1].s.f) : (0)) + (text[i] - 'a' + 1) * hashTables.p_pow2[i]) % hashTables.mod2;
            hashUptoIndex[i].s.s = (((i > 0) ? (hashUptoIndex[i - 1].s.s) : (0)) + (text[i] - 'a' + 1) * hashTables.p_pow3[i]) % hashTables.mod3;
        }
    }
};

Rabin_Karp R;

int main()
{
    return 0;
}


// 

// #define hash pair<int, pair<int, int>>
#define hash int
// struct Rabin_Karp
// {
//     int valLen;
//     Rabin_Karp()
//     {
//         valLen = 0;
//     }
//     Rabin_Karp(string str)
//     {
//         prepareString(str);
//     }
//     vector<hash> hashUptoIndex;
//     hash getHash(int startIndex, int endIndex)
//     {
//         if (startIndex > endIndex || startIndex < 0 || startIndex >= valLen || endIndex < 0 || endIndex >= valLen)
//             return {0, {0, 0}};
//         int a = (1LL * hashUptoIndex[endIndex].f - (startIndex ? hashUptoIndex[startIndex - 1].f * 1LL : 0LL) + hashTables.mod1) % hashTables.mod1;
//         int b = (1LL * hashUptoIndex[endIndex].s.f - (startIndex ? hashUptoIndex[startIndex - 1].s.f * 1LL : 0LL) + hashTables.mod2) % hashTables.mod2;
//         int c = 0;
//         // int c = (1LL * hashUptoIndex[endIndex].s.s - (startIndex ? hashUptoIndex[startIndex - 1].s.s * 1LL : 0LL) + hashTables.mod3) % hashTables.mod3;
//         a = (a * 1LL * hashTables.inv_pow1[startIndex]) % hashTables.mod1;
//         b = (b * 1LL * hashTables.inv_pow2[startIndex]) % hashTables.mod2;
//         // c = (c * 1LL * hashTables.inv_pow3[startIndex]) % hashTables.mod3;
//         auto ret = make_pair(a, make_pair(b, c));
//         return ret;
//     }
//     void prepareString(string text)
//     {
//         int n = text.size();
//         valLen = n;
//         hashUptoIndex.resize(n);
//         for (int i = 0; i < n; ++i)
//         {
//             hashUptoIndex[i].f = (((i > 0) ? (hashUptoIndex[i - 1].f * 1LL) : (0LL)) + (text[i] - 'a' + 1LL) * hashTables.p_pow1[i]) % hashTables.mod1;
//             hashUptoIndex[i].s.f = (((i > 0) ? (hashUptoIndex[i - 1].s.f * 1LL) : (0LL)) + (text[i] - 'a' + 1LL) * hashTables.p_pow2[i]) % hashTables.mod2;
//             // hashUptoIndex[i].s.s = (((i > 0) ? (hashUptoIndex[i - 1].s.s * 1LL) : (0LL)) + (text[i] - 'a' + 1LL) * hashTables.p_pow3[i]) % hashTables.mod3;
//             hashUptoIndex[i].s.s = 0;
//         }
//     }
// };

const int p = 331;
int hashs[NAX];
int pows[NAX];
struct Rabin_Karp
{
    int valLen;
    Rabin_Karp()
    {
        pows[0] = 1;
        for (int i = 1; i < NAX; i++)
            pows[i] = (pows[i - 1] * 1LL * p) % MOD;
    }
    Rabin_Karp(string str)
    {
        prepareString(str);
    }
    // vector<hash> hashUptoIndex;
    int getHash(int l, int r)
    {
        return ((hashs[r + 1] - (hashs[l] * 1LL * pows[r - l + 1]) % MOD) + MOD) % MOD;
    }
    void prepareString(string s)
    {
        for (int i = 0; i < s.length(); i++)
            hashs[i + 1] = (hashs[i] * 1LL * p + s[i]) % MOD;
        // int n = text.size();
        // valLen = n;
        // hashUptoIndex.resize(n);
        // for (int i = 0; i < n; ++i)
        // {
        //     hashUptoIndex[i].f = (((i > 0) ? (hashUptoIndex[i - 1].f * 1LL) : (0LL)) + (text[i] - 'a' + 1LL) * hashTables.p_pow1[i]) % hashTables.mod1;
        //     hashUptoIndex[i].s.f = (((i > 0) ? (hashUptoIndex[i - 1].s.f * 1LL) : (0LL)) + (text[i] - 'a' + 1LL) * hashTables.p_pow2[i]) % hashTables.mod2;
        //     // hashUptoIndex[i].s.s = (((i > 0) ? (hashUptoIndex[i - 1].s.s * 1LL) : (0LL)) + (text[i] - 'a' + 1LL) * hashTables.p_pow3[i]) % hashTables.mod3;
        //     hashUptoIndex[i].s.s = 0;
        // }
    }
};

Rabin_Karp R;
