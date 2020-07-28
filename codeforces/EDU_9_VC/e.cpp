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

const int NAX = 1e6 + 5, MOD = 1000000007;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C> &a)
{
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<C> rt(2, 1); // (^ 10% faster i f double )
    for (static int k = 2; k < n; k *= 2)
    {
        R.resize(n);
        rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        rep(i, k, 2 * k) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
    }
    vi rev(n);
    rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k)
            rep(j, 0, k)
            {
                C z = rt[j + k] * a[i + j + k]; // (25% faster i f hand−r o l l e d )
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
}

const double ERR = 1e-6;

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
    for (C &x : in)
        x *= x;
    rep(i, 0, n) out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out);
    rep(i, 0, sz(res))
    {
        res[i] = imag(out[i]) / (4 * n);
        if (res[i] > (1 - ERR))
            res[i] = 1;
        else
            res[i] = 0;
    }
    return res;
}

struct Solution
{
    Solution() {}
    void solveCase()
    {
        int n, k;
        cin >> n >> k;
        vector<double> a(1001);
        for (size_t i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            if (a[x] < ERR)
                a[x] = 1;
        }
        function<vd(int)> expo = [&](int idx) -> vd {
            if (idx == 0)
                return {};
            if (idx == 1)
                return a;
            auto temp = expo(idx / 2);
            temp = conv(temp, temp);
            if (idx & 1)
                temp = conv(temp, a);
            return temp;
        };
        auto ret = expo(k);
        int res = 0;
        for (size_t i = 0; i < ret.size(); i++)
            if (ret[i] > (1 - ERR))
                cout << i << ' ';
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
