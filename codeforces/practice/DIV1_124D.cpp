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

const int NAX = 4e5 + 5, MOD = 1000000007;
int d, n;
string s, t;
const int maxSize = NAX;
ll hsh1[NAX], hsh2[NAX], hsh3[NAX];
ll Revhsh1[NAX], Revhsh2[NAX], Revhsh3[NAX];
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
void Rabin_Karp()
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

bool check1(int pos, int d)
{
    return ((hsh1[pos] - hsh1[pos - d] * p_pow1[d] % mod1 + mod1) % mod1 * p_pow1[pos - d]) % mod1 == (Revhsh1[pos] - Revhsh1[pos - d] + mod1) % mod1;
}

bool check2(int pos, int d)
{
    return ((hsh2[pos] - hsh2[pos - d] * p_pow2[d] % mod2 + mod2) % mod2 * p_pow2[pos - d]) % mod2 == (Revhsh2[pos] - Revhsh2[pos - d] + mod2) % mod2;
}

bool check3(int pos, int d)
{
    return ((hsh3[pos] - hsh3[pos - d] * p_pow3[d] % mod3 + mod3) % mod3 * p_pow3[pos - d]) % mod3 == (Revhsh3[pos] - Revhsh3[pos - d] + mod3) % mod3;
}

bool ok(int pos, int d)
{
    return !(pos >= d && check1(pos, d) && check2(pos, d) && check3(pos, d));
}

void go(int pos, bool b)
{
    db(pos, d, s, t);
    if (!ok(pos, d) || !ok(pos, d + 1))
        return;
    if (pos == n)
    {
        if (b)
        {
            cout << t << '\n';
            exit(0);
        }
        return;
    }
    for (t[pos] = (b ? 'a' : s[pos]); t[pos] <= 'z'; t[pos]++)
    {
        hsh1[pos + 1] = (hsh1[pos] * p1 + t[pos]) % mod1;
        hsh2[pos + 1] = (hsh2[pos] * p2 + t[pos]) % mod2;
        hsh3[pos + 1] = (hsh3[pos] * p3 + t[pos]) % mod3;

        Revhsh1[pos + 1] = (Revhsh1[pos] + p_pow1[pos] * t[pos]) % mod1;
        Revhsh2[pos + 1] = (Revhsh2[pos] + p_pow2[pos] * t[pos]) % mod2;
        Revhsh3[pos + 1] = (Revhsh3[pos] + p_pow3[pos] * t[pos]) % mod3;

        go(pos + 1, b || (t[pos] > s[pos]));
    }
}

void solveCase(int caseNo)
{
    Rabin_Karp();
    cin >> d >> s;
    n = s.size();
    t = string(n, '.');
    go(0, false);
    cout << "Impossible\n";
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
