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
auto TimeStart = chrono::steady_clock::now();

const int NAX = 2e5 + 10, MOD = 1000000007;

struct Rabin_Karp
{
    const int maxSize = 5e3 + 10;
    const long long p1 = 805306457, p2 = 53, p3 = 31;
    const int mod1 = 1610612741, mod2 = 1e9 + 7, mod3 = 1e9 + 9, m = 1e9 + 9;
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
    Rabin_Karp()
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
    string s, prefix, suffix;
    vector<pair<long long, pair<long long, long long>>> hashUptoIndex;
    pair<long long, pair<long long, long long>> getHash(int startIndex, int endIndex)
    {
        long long a = (hashUptoIndex[endIndex].f - (startIndex ? hashUptoIndex[startIndex - 1].f : 0) + mod1) % mod1;
        long long b = (hashUptoIndex[endIndex].s.f - (startIndex ? hashUptoIndex[startIndex - 1].s.f : 0) + mod2) % mod2;
        long long c = (hashUptoIndex[endIndex].s.s - (startIndex ? hashUptoIndex[startIndex - 1].s.s : 0) + mod3) % mod3;
        db(inv_pow1[startIndex], startIndex);
        a = (a * inv_pow1[startIndex]) % mod1;
        b = (b * inv_pow2[startIndex]) % mod2;
        c = (c * inv_pow3[startIndex]) % mod3;
        auto ret = make_pair(a, make_pair(b, c));
        auto temp = s.substr(startIndex, endIndex - startIndex + 1);
        db(startIndex, endIndex, ret, temp);
        return ret;
    }
    void solve()
    {
        pair<long long, pair<long long, long long>> hashSuffix;
        pair<long long, pair<long long, long long>> hashPrefix;
        cin >> s >> prefix >> suffix;
        hashPrefix.f = prefix[0] - 'a' + 1;
        hashPrefix.s.f = prefix[0] - 'a' + 1;
        hashPrefix.s.s = prefix[0] - 'a' + 1;
        for (int i = 1; i < prefix.size(); ++i)
        {
            auto c = prefix[i];
            hashPrefix.f = (hashPrefix.f + (c - 'a' + 1) * p1 % mod1) % mod1;
            hashPrefix.s.f = (hashPrefix.s.f + (c - 'a' + 1) * p2 % mod2) % mod2;
            hashPrefix.s.s = (hashPrefix.s.s + (c - 'a' + 1) * p3 % mod3) % mod3;
        }
        hashSuffix.f = suffix[0] - 'a' + 1;
        hashSuffix.s.f = suffix[0] - 'a' + 1;
        hashSuffix.s.s = suffix[0] - 'a' + 1;
        for (int i = 1; i < suffix.size(); ++i)
        {
            auto c = suffix[i];
            hashSuffix.f = (hashSuffix.f + (c - 'a' + 1) * p1 % mod1) % mod1;
            hashSuffix.s.f = (hashSuffix.s.f + (c - 'a' + 1) * p2 % mod2) % mod2;
            hashSuffix.s.s = (hashSuffix.s.s + (c - 'a' + 1) * p3 % mod3) % mod3;
        }
        int n = s.size();
        vector<int> startIndexes;
        set<pair<long long, pair<long long, long long>>> S;
        hashUptoIndex.resize(n + 1);
        db(hashPrefix, hashSuffix);
        hashUptoIndex[0].f = s[0] - 'a' + 1;
        hashUptoIndex[0].s.f = s[0] - 'a' + 1;
        hashUptoIndex[0].s.s = s[0] - 'a' + 1;
        for (int i = 1; i < n; ++i)
        {
            hashUptoIndex[i].f = (hashUptoIndex[i - 1].f + (s[i] - 'a' + 1) * p1 % mod1) % mod1;
            hashUptoIndex[i].s.f = (hashUptoIndex[i - 1].s.f + (s[i] - 'a' + 1) * p2 % mod2) % mod2;
            hashUptoIndex[i].s.s = (hashUptoIndex[i - 1].s.s + (s[i] - 'a' + 1) * p3 % mod3) % mod3;
        }
        for (int i = 0; i < n; ++i)
        {
            if (i + suffix.size() - 1 >= n)
                break;
            if (i + prefix.size() - 1 >= n)
                break;
            if (getHash(i, i + prefix.size() - 1) == hashPrefix)
                startIndexes.pb(i);
            db(i);
            pc(startIndexes);
            if (getHash(i, i + suffix.size() - 1) == hashSuffix)
                for (auto index : startIndexes)
                    if ((i - index + 1) >= suffix.size())
                        S.insert(getHash(index, i));
        }
        cout << S.size() << '\n';
    }
};

Rabin_Karp R;

void solveCase(int caseNo)
{
    R.solve();
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