// Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define MULTI_TEST
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

struct Rabin_Karp
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
        // db(startIndex, endIndex);
        if (startIndex > endIndex)
            return {0, {0, 0}};
        long long a = (hashUptoIndex[endIndex].f - (startIndex ? hashUptoIndex[startIndex - 1].f : 0) + mod1) % mod1;
        long long b = (hashUptoIndex[endIndex].s.f - (startIndex ? hashUptoIndex[startIndex - 1].s.f : 0) + mod2) % mod2;
        long long c = (hashUptoIndex[endIndex].s.s - (startIndex ? hashUptoIndex[startIndex - 1].s.s : 0) + mod3) % mod3;
        a = (a * inv_pow1[startIndex]) % mod1;
        b = (b * inv_pow2[startIndex]) % mod2;
        c = (c * inv_pow3[startIndex]) % mod3;
        auto ret = make_pair(a, make_pair(b, c));
        return ret;
    }
    int solve(string pattern, string text)
    {
        if (text.size() < pattern.size())
            return 0;
        int patternSize = pattern.size();
        int textSize = text.size();
        int cnt = 0;
        pair<ll, pair<ll, ll>> hashPattern;
        for (auto c : pattern)
        {
            hashPattern.f = (hashPattern.f * p1 + c - 'a' + 1) % mod1;
            hashPattern.s.f = (hashPattern.s.f * p2 + c - 'a' + 1) % mod2;
            hashPattern.s.s = (hashPattern.s.s * p3 + c - 'a' + 1) % mod3;
        }
        pair<ll, pair<ll, ll>> currentTextHash;
        for (int i = 0; i < patternSize; ++i)
        {
            currentTextHash.f = (currentTextHash.f * p1 + text[i] - 'a' + 1) % mod1;
            currentTextHash.s.f = (currentTextHash.s.f * p2 + text[i] - 'a' + 1) % mod2;
            currentTextHash.s.s = (currentTextHash.s.s * p3 + text[i] - 'a' + 1) % mod3;
        }
        cnt += currentTextHash == hashPattern;
        for (int i = patternSize; i < textSize; ++i)
        {
            currentTextHash.f = (currentTextHash.f - ((text[i - patternSize] - 'a' + 1) * p_pow1[patternSize - 1]) % mod1 + mod1) % mod1;
            currentTextHash.s.f = (currentTextHash.s.f - ((text[i - patternSize] - 'a' + 1) * p_pow2[patternSize - 1]) % mod2 + mod2) % mod2;
            currentTextHash.s.s = (currentTextHash.s.s - ((text[i - patternSize] - 'a' + 1) * p_pow3[patternSize - 1]) % mod3 + mod3) % mod3;

            currentTextHash.f = (currentTextHash.f * p_pow1[1]) % mod1;
            currentTextHash.s.f = (currentTextHash.s.f * p_pow2[1]) % mod2;
            currentTextHash.s.s = (currentTextHash.s.s * p_pow3[1]) % mod3;

            currentTextHash.f = (currentTextHash.f + (text[i] - 'a' + 1)) % mod1;
            currentTextHash.s.f = (currentTextHash.s.f + (text[i] - 'a' + 1)) % mod2;
            currentTextHash.s.s = (currentTextHash.s.s + (text[i] - 'a' + 1)) % mod3;

            cnt += currentTextHash == hashPattern;
            // db(i, currentTextHash, hashPattern);
        }
        return cnt;
    }
    void prepareString(string text)
    {
        int n = text.size();
        hashUptoIndex.resize(n);
        for (int i = 0; i < n; ++i)
        {
            hashUptoIndex[i].f = (((i > 0) ? (hashUptoIndex[i - 1].f) : (0)) + (text[i] - 'a' + 1) * p_pow1[i]) % mod1;
            hashUptoIndex[i].s.f = (((i > 0) ? (hashUptoIndex[i - 1].s.f) : (0)) + (text[i] - 'a' + 1) * p_pow2[i]) % mod2;
            hashUptoIndex[i].s.s = (((i > 0) ? (hashUptoIndex[i - 1].s.s) : (0)) + (text[i] - 'a' + 1) * p_pow3[i]) % mod3;
        }
    }
};

Rabin_Karp Forw, Back;
int n;

class Solution
{
private:
    bool check(int lptr, int llptr, int rptr, int rrptr)
    {
        auto getRIdx = [](int idx) {
            return n - 1 - idx;
        };
        pair<long long, pair<long long, long long>> al;
        pair<long long, pair<long long, long long>> ar;
        pair<long long, pair<long long, long long>> bl;
        pair<long long, pair<long long, long long>> br;
        if (lptr > llptr)
        {
            al = {0, {0, 0}};
            br = {0, {0, 0}};
        }
        else
        {
            al = Forw.getHash(lptr, llptr);
            br = Forw.getHash(getRIdx(llptr), getRIdx(lptr));
        }
        if (rptr > rrptr)
        {
            ar = {0, {0, 0}};
            bl = {0, {0, 0}};
        }
        else
        {
            ar = Back.getHash(rptr, rrptr);
            bl = Back.getHash(getRIdx(rrptr), getRIdx(rptr));
        }

        // db(al, ar, bl, br);

        int len1 = llptr - lptr + 1;
        al.f = (al.f + (ar.f) * Forw.p_pow1[len1]) % Forw.mod1;
        al.s.f = (al.s.f + (ar.s.f) * Forw.p_pow2[len1]) % Forw.mod2;
        al.s.s = (al.s.s + (ar.s.s) * Forw.p_pow3[len1]) % Forw.mod3;

        swap(al, bl);
        swap(ar, br);
        len1 = rrptr - rptr + 1;

        al.f = (al.f + (ar.f) * Forw.p_pow1[len1]) % Forw.mod1;
        al.s.f = (al.s.f + (ar.s.f) * Forw.p_pow2[len1]) % Forw.mod2;
        al.s.s = (al.s.s + (ar.s.s) * Forw.p_pow3[len1]) % Forw.mod3;

        // db(al, bl);
        return al == bl;
    }

public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        string str;
        cin >> str;
        auto srev = str;
        reverse(all(srev));
        Forw.prepareString(str);
        Back.prepareString(srev);
        n = str.length();
        if (Forw.getHash(0, n - 1) == Back.getHash(0, n - 1))
        {
            cout << str << '\n';
        }
        else
        {
            auto getRIdx = [](int idx) {
                return n - 1 - idx;
            };
            int preflen = 0;
            int startidx, bestLen;
            startidx = bestLen = -1;
            db(str);
            bool fromFront = true;
            int len1, len2;
            len1 = len2 = 0;
            while (2 * preflen <= n)
            {
                // db(preflen);
                int l = 0, lr = preflen;
                // db(l, lr, Forw.getHash(0, lr));
                // db(Back.getHash(0, lr));
                if (l == lr || Forw.getHash(0, lr - 1) == Back.getHash(0, lr - 1))
                {
                    // bestLen = max(2 * (lr - l), bestLen);
                    int currLen = 2 * (lr - l);
                    int remLen = n - currLen;
                    for (int i = 1; i <= remLen; i++)
                    {
                        // db(lr, lr + i - 1);
                        if (Forw.getHash(lr, lr + i - 1) == Back.getHash(getRIdx(lr + i - 1), getRIdx(lr)))
                        {
                            if (currLen + i > bestLen)
                            {
                                bestLen = currLen + i;
                                len1 = preflen;
                                len2 = i;
                                fromFront = true;
                            }
                        }
                        if (Back.getHash(lr, lr + i - 1) == Forw.getHash(getRIdx(lr + i - 1), getRIdx(lr)))
                        {
                            if (currLen + i > bestLen)
                            {
                                bestLen = currLen + i;
                                len1 = preflen;
                                len2 = i;
                                fromFront = false;
                            }
                        }
                    }
                }
                preflen++;
            }
            // db(str, srev);
            // db(bestLen, len1, len2, fromFront);
            // cout << 1 << '\n';
            if (fromFront)
                cout << str.substr(0, len1 + len2);
            else
                cout << srev.substr(0, len1 + len2);
            if (len1)
                cout << srev.substr(n - len1, len1) << '\n';
            else
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