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

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C> &a)
{
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<C> rt(2, 1); // (ˆ 10% f a s t e r i f double )
    for (static int k = 2; k < n; k *= 2)
    {
        R.resize(n);
        rt.resize(n);
        auto x = polar(1.0L, M_PIl / k); // M PI, lower−case L
        rep(i, k, 2 * k) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
    }
    vi rev(n);
    rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k)
            rep(j, 0, k)
            {
                C z = rt[j + k] * a[i + j + k]; // (25% f a s t e r i f hand−r o l l e d )
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
}
vd conv(const vd &a, const vd &b)
{
    if (a.empty() || b.empty())
        return {};
    vd res(sz(a) + sz(b) - 1);
    int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
    vector<C> in(n), out(n);
    copy(all(a), begin(in));
    rep(i, 0, sz(b)) in[i].imag(b[i]);
    fft(in);
    trav(x, in) x *= x;
    rep(i, 0, n) out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out);
    rep(i, 0, sz(res)) res[i] = imag(out[i]) / (4 * n);
    return res;
}

struct Solution
{
    vd conv_slow(vd a, vd b)
    {
        vd ret(a.size() + b.size());
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = 0; j < b.size(); j++)
                ret[i + j] += a[i] * b[j];
        return ret;
    }
    vector<int> conv(vector<int> a, vector<int> b)
    {
        vd a1(a.size()), b1(b.size());
        copy(all(a), a1.begin());
        copy(all(b), b1.begin());
        auto ret1 = ::conv(a1, b1);
        // auto ret2 = conv_slow(a1, b1);
        vector<int> ret(ret1.size());
        // db(ret1.size(), ret2.size());
        for (size_t i = 0; i < ret.size(); i++)
        {
            cout << fixed << setprecision(5);
            ret[i] = ret1[i] + 0.5;
            // cout << double(ret[i]) << ' ' << ret1[i] << ' ' << ret2[i] << '\n';
        }
        return ret;
    }
    Solution() {}
    vector<int> match(string s1, string s2)
    {
        swap(s1, s2);
        const int LIM = max(s1.size(), s2.size());
        vector<int> ret(LIM);
        for (auto x : {'a', 'b', 'c'})
        {
            vector<int> a(LIM);
            vector<int> b(LIM);
            for (int i = 0; i < s1.size(); i++)
                a[i] = (x == s1[i]);
            for (int i = 0; i < s2.size(); i++)
                b[s2.size() - i - 1] = (x == s2[i]);
            // db(x, a, b);
            auto c = conv(a, b);
            // db(c);
            for (int i = 0; i < LIM; i++)
                ret[i] += c[i + LIM - 1];
        }
        return ret;
    }
    void solveCase()
    {
        string s1, s2;
        cin >> s1;
        s2 = s1;
        // reverse(all(s2));
        auto ret = match(s1, s2);
        db(ret);
        auto it = *max_element(ret.begin() + 1, ret.end());
        cout << it << '\n';
        for (size_t i = 1; i < ret.size(); i++)
            if (ret[i] == it)
                cout << i << ' ';
        cout << '\n';
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
