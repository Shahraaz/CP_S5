//Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define MULTI_TEST
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
    const int maxSize = 1e6;
    const int p1 = 805306457, p2 = 53, p3 = 31;
    const int mod1 = 1610612741, mod2 = 1e9 + 7, mod3 = 1e9 + 9;
    vector<long long> p_pow1, p_pow2, p_pow3;
    Rabin_Karp()
    {
        p_pow1.resize(maxSize);
        p_pow2.resize(maxSize);
        p_pow3.resize(maxSize);
        p_pow1[0] = p_pow2[0] = p_pow3[0] = 1;
        for (int i = 1; i < maxSize; ++i)
        {
            p_pow1[i] = (p_pow1[i - 1] * p1) % mod1;
            p_pow2[i] = (p_pow2[i - 1] * p2) % mod2;
            p_pow3[i] = (p_pow3[i - 1] * p3) % mod3;
        }
    }
    vector<int> match(string pattern, string text)
    {
        int S = pattern.size(), T = text.size();
        vector<int> h1(T + 1), h2(T + 1), h3(T + 1);
        for (int i = 0; i < T; ++i)
        {
            h1[i + 1] = ((h1[i] + text[i] - 'a' + 1) * p_pow1[i]) % mod1;
            h2[i + 1] = ((h2[i] + text[i] - 'a' + 1) * p_pow2[i]) % mod2;
            h3[i + 1] = ((h3[i] + text[i] - 'a' + 1) * p_pow3[i]) % mod3;
        }
        long h_s1 = 0, h_s2 = 0, h_s3 = 0;
        for (int i = 0; i < S; ++i)
        {
            h_s1 = ((h_s1 + pattern[i] - 'a' + 1) * p_pow1[i]) % mod1;
            h_s2 = ((h_s2 + pattern[i] - 'a' + 1) * p_pow2[i]) % mod2;
            h_s3 = ((h_s3 + pattern[i] - 'a' + 1) * p_pow3[i]) % mod3;
        }
        vector<int> occurances;
        for (int i = 0; i + S - 1 < T; ++i)
        {
            ll cur_h1 = (h1[i + S] + mod1 - h1[i]) % mod1;
            ll cur_h2 = (h1[i + S] + mod2 - h1[i]) % mod2;
            ll cur_h3 = (h1[i + S] + mod3 - h1[i]) % mod3;
            db(i,cur_h1,cur_h2,cur_h3);
            db(((h_s1 * p_pow1[i]) % mod1));
            db(((h_s2 * p_pow2[i]) % mod2));
            db(((h_s3 * p_pow3[i]) % mod3));
            if (cur_h1 == ((h_s1 * p_pow1[i]) % mod1))
                if (cur_h2 == ((h_s2 * p_pow2[i]) % mod2))
                    if (cur_h3 == ((h_s3 * p_pow3[i]) % mod3))
                        occurances.pb(i);
        }
        return occurances;
    }
};

Rabin_Karp R;

void solveCase(int caseNo)
{
    string a, b;
    cin >> a >> b;
    auto ret = R.match(a, b);
    if (ret.size())
    {
        cout << ret.size() << '\n';
        for (auto elem : ret)
            cout << elem << ' ';
    }
    else
        cout << "NotFound";
    cout << "\n\n";
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