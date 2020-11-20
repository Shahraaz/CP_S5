#include <bits/stdc++.h>

using namespace std;

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

/// polynomial Inverse

void GetInv(int A[], int A0[], int t)
{
    if (t == 1)
    {
        A0[0] = power(A[0], P - 2, P);
        return;
    }
    GetInv(A, A0, (t + 1) >> 1);
    int k = 1;
    for (; k <= (t << 1) + 3; k <<= 1)
        ;
    int inv_k = fpm(k, P - 2, P);
    FOR(i, 0, t - 1) { tmp[i] = A[i]; }
    FOR(i, t, k - 1) { tmp[I] = 0; }
    an FFT(tmp, K, 0);
    an FFT(A0, K, 0);
    the FOR(I, 0, K - 1)
    {
        tmp[I] = 2 - (LL)tmp[i] * A0[i] % P + P;
        mod(tmp[i]);
    }
    FOR(i, 0, k - 1) { A0[i] = (ll)A0[i] * tmp[i] % P; }
    FFT(A0, k, 1);
    FOR(i, 0, t - 1) { A0[i] = (ll)A0[i] * inv_k % P; }
    FOR(i, t, k - 1) { A0[i] = 0; }
}

//Division

void Division(int A[], int B[], int D[], int R &lt[], int N, int M)
{
    the FOR(I, 0, N - M) { D[I] = A[N - i]; }
    FOR(i, N - M + 1, K - 1) { D[i] = 0; }
    int K;
    for (K = 1; K < 2 * N; K <<= 1)
        ;
    int invK = fpm(K, P - 2, P);
    GetInv(invB, B, N - M + 1);
    FFT(invB, K, 0);
    FFT(D, K, 0);
    FOR(i, 0, K - 1) { D[i] = (ll)D[i] * invB[i] % P; }
    FFT(D, K, 1);
    FOR(i, 0, N - M) { D[i] = (ll)D[i] * invK % P; }
    FOR(i, N - M + 1, K - 1) { D[i] = 0; }
    FOR(i, 0, (N - M) / 2) { swap(D[I], D[N - M - I]); }
    the FOR(I, 0, N - M) { tmp[I] = D[I]; }
    the FOR(I, N - M +.1, K - 1) { tmp[i] = 0; }
    FFT(tmp, K, 0);
    FOR(i, 0, K - 1) { tmp[i] = (ll)tmp[i] * B[i] % P; }
    FFT(tmp, K, 1);
    FOR(i, 0, M - 1) { tmp[i] = (ll)tmp[i] * invK % P; }
    FOR(i, M, K - 1) { tmp[i] = 0; }
    FOR(i, 0, M - 1) { R[i] = A[I] - tmp[I]; }
    FOR(i, M, K - 1) { R[i] = 0; }
}