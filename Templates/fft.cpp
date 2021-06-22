// make it understandable one day...
namespace fft {
typedef double dbl;
struct num {
  dbl x, y;
  num() { x = y = 0; }
  num(dbl x_, dbl y_) : x(x_), y(y_) {}
};
inline num operator+(num a, num b) { return num(a.x + b.x, a.y + b.y); }
inline num operator-(num a, num b) { return num(a.x - b.x, a.y - b.y); }
inline num operator*(num a, num b) { return num(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
inline num conj(num a) { return num(a.x, -a.y); }
int base = 1;
vector<num> roots = {{0, 0}, {1, 0}};
vector<int> rev = {0, 1};
const dbl PI = static_cast<dbl>(acosl(-1.0));
void ensure_base(int nbase) {
  if (nbase <= base) {
    return;
  }
  rev.resize(1 << nbase);
  for (int i = 0; i < (1 << nbase); i++) {
    rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
  }
  roots.resize(1 << nbase);
  while (base < nbase) {
    dbl angle = 2 * PI / (1 << (base + 1));
//      num z(cos(angle), sin(angle));
    for (int i = 1 << (base - 1); i < (1 << base); i++) {
      roots[i << 1] = roots[i];
//        roots[(i << 1) + 1] = roots[i] * z;
      dbl angle_i = angle * (2 * i + 1 - (1 << base));
      roots[(i << 1) + 1] = num(cos(angle_i), sin(angle_i));
    }
    base++;
  }
}
void fft(vector<num>& a, int n = -1) {
  if (n == -1) {
    n = (int) a.size();
  }
  assert((n & (n - 1)) == 0);
  int zeros = __builtin_ctz(n);
  ensure_base(zeros);
  int shift = base - zeros;
  for (int i = 0; i < n; i++) {
    if (i < (rev[i] >> shift)) {
      swap(a[i], a[rev[i] >> shift]);
    }
  }
  for (int k = 1; k < n; k <<= 1) {
    for (int i = 0; i < n; i += 2 * k) {
      for (int j = 0; j < k; j++) {
        num z = a[i + j + k] * roots[j + k];
        a[i + j + k] = a[i + j] - z;
        a[i + j] = a[i + j] + z;
      }
    }
  }
}
vector<num> fa, fb;
vector<int64_t> square(const vector<int>& a) {
  if (a.empty()) {
    return {};
  }
  int need = (int) a.size() + (int) a.size() - 1;
  int nbase = 1;
  while ((1 << nbase) < need) nbase++;
  ensure_base(nbase);
  int sz = 1 << nbase;
  if ((sz >> 1) > (int) fa.size()) {
    fa.resize(sz >> 1);
  }
  for (int i = 0; i < (sz >> 1); i++) {
    int x = (2 * i < (int) a.size() ? a[2 * i] : 0);
    int y = (2 * i + 1 < (int) a.size() ? a[2 * i + 1] : 0);
    fa[i] = num(x, y);
  }
  fft(fa, sz >> 1);
  num r(1.0 / (sz >> 1), 0.0);
  for (int i = 0; i <= (sz >> 2); i++) {
    int j = ((sz >> 1) - i) & ((sz >> 1) - 1);
    num fe = (fa[i] + conj(fa[j])) * num(0.5, 0);
    num fo = (fa[i] - conj(fa[j])) * num(0, -0.5);
    num aux = fe * fe + fo * fo * roots[(sz >> 1) + i] * roots[(sz >> 1) + i];
    num tmp = fe * fo;
    fa[i] = r * (conj(aux) + num(0, 2) * conj(tmp));
    fa[j] = r * (aux + num(0, 2) * tmp);
  }
  fft(fa, sz >> 1);
  vector<int64_t> res(need);
  for (int i = 0; i < need; i++) {
    res[i] = llround(i % 2 == 0 ? fa[i >> 1].x : fa[i >> 1].y);
  }
  return res;
}
vector<int64_t> multiply(const vector<int>& a, const vector<int>& b) {
  if (a.empty() || b.empty()) {
    return {};
  }
  if (a == b) {
    return square(a);
  }
  int need = (int) a.size() + (int) b.size() - 1;
  int nbase = 1;
  while ((1 << nbase) < need) nbase++;
  ensure_base(nbase);
  int sz = 1 << nbase;
  if (sz > (int) fa.size()) {
    fa.resize(sz);
  }
  for (int i = 0; i < sz; i++) {
    int x = (i < (int) a.size() ? a[i] : 0);
    int y = (i < (int) b.size() ? b[i] : 0);
    fa[i] = num(x, y);
  }
  fft(fa, sz);
  num r(0, -0.25 / (sz >> 1));
  for (int i = 0; i <= (sz >> 1); i++) {
    int j = (sz - i) & (sz - 1);
    num z = (fa[j] * fa[j] - conj(fa[i] * fa[i])) * r;
    fa[j] = (fa[i] * fa[i] - conj(fa[j] * fa[j])) * r;
    fa[i] = z;
  }
  for (int i = 0; i < (sz >> 1); i++) {
    num A0 = (fa[i] + fa[i + (sz >> 1)]) * num(0.5, 0);
    num A1 = (fa[i] - fa[i + (sz >> 1)]) * num(0.5, 0) * roots[(sz >> 1) + i];
    fa[i] = A0 + A1 * num(0, 1);
  }
  fft(fa, sz >> 1);
  vector<int64_t> res(need);
  for (int i = 0; i < need; i++) {
    res[i] = llround(i % 2 == 0 ? fa[i >> 1].x : fa[i >> 1].y);
  }
  return res;
}
vector<int> multiply_mod(const vector<int>& a, const vector<int>& b, int m) {
  if (a.empty() || b.empty()) {
    return {};
  }
  int eq = (a.size() == b.size() && a == b);
  int need = (int) a.size() + (int) b.size() - 1;
  int nbase = 0;
  while ((1 << nbase) < need) nbase++;
  ensure_base(nbase);
  int sz = 1 << nbase;
  if (sz > (int) fa.size()) {
    fa.resize(sz);
  }
  for (int i = 0; i < (int) a.size(); i++) {
    int x = (a[i] % m + m) % m;
    fa[i] = num(x & ((1 << 15) - 1), x >> 15);
  }
  fill(fa.begin() + a.size(), fa.begin() + sz, num {0, 0});
  fft(fa, sz);
  if (sz > (int) fb.size()) {
    fb.resize(sz);
  }
  if (eq) {
    copy(fa.begin(), fa.begin() + sz, fb.begin());
  } else {
    for (int i = 0; i < (int) b.size(); i++) {
      int x = (b[i] % m + m) % m;
      fb[i] = num(x & ((1 << 15) - 1), x >> 15);
    }
    fill(fb.begin() + b.size(), fb.begin() + sz, num {0, 0});
    fft(fb, sz);
  }
  dbl ratio = 0.25 / sz;
  num r2(0, -1);
  num r3(ratio, 0);
  num r4(0, -ratio);
  num r5(0, 1);
  for (int i = 0; i <= (sz >> 1); i++) {
    int j = (sz - i) & (sz - 1);
    num a1 = (fa[i] + conj(fa[j]));
    num a2 = (fa[i] - conj(fa[j])) * r2;
    num b1 = (fb[i] + conj(fb[j])) * r3;
    num b2 = (fb[i] - conj(fb[j])) * r4;
    if (i != j) {
      num c1 = (fa[j] + conj(fa[i]));
      num c2 = (fa[j] - conj(fa[i])) * r2;
      num d1 = (fb[j] + conj(fb[i])) * r3;
      num d2 = (fb[j] - conj(fb[i])) * r4;
      fa[i] = c1 * d1 + c2 * d2 * r5;
      fb[i] = c1 * d2 + c2 * d1;
    }
    fa[j] = a1 * b1 + a2 * b2 * r5;
    fb[j] = a1 * b2 + a2 * b1;
  }
  fft(fa, sz);
  fft(fb, sz);
  vector<int> res(need);
  for (int i = 0; i < need; i++) {
    int64_t aa = llround(fa[i].x);
    int64_t bb = llround(fb[i].x);
    int64_t cc = llround(fa[i].y);
    res[i] = static_cast<int>((aa + ((bb % m) << 15) + ((cc % m) << 30)) % m);
  }
  return res;
}
}  // namespace fft
// template <typename T>
// typename enable_if<is_same<typename Modular<T>::Type, int>::value, vector<Modular<T>>>::type operator*(
//     const vector<Modular<T>>& a,
//     const vector<Modular<T>>& b) {
//   if (a.empty() || b.empty()) {
//     return {};
//   }
//   if (min(a.size(), b.size()) < 150) {
//     vector<Modular<T>> c(a.size() + b.size() - 1, 0);
//     for (int i = 0; i < (int) a.size(); i++) {
//       for (int j = 0; j < (int) b.size(); j++) {
//         c[i + j] += a[i] * b[j];
//       }
//     }
//     return c;
//   } 
//   vector<int> a_mul(a.size());
//   for (int i = 0; i < (int) a.size(); i++) {
//     a_mul[i] = static_cast<int>(a[i]);
//   }
//   vector<int> b_mul(b.size());
//   for (int i = 0; i < (int) b.size(); i++) {
//     b_mul[i] = static_cast<int>(b[i]);
//   }
//   vector<int> c_mul = fft::multiply_mod(a_mul, b_mul, T::value);
//   vector<Modular<T>> c(c_mul.size());
//   for (int i = 0; i < (int) c.size(); i++) {
//     c[i] = c_mul[i];
//   }
//   return c;
// }
// template <typename T>
// typename enable_if<is_same<typename Modular<T>::Type, int>::value, vector<Modular<T>>>::type& operator*=(
//     vector<Modular<T>>& a,
//     const vector<Modular<T>>& b) {
//   return a = a * b;
// }

using namespace fft;

// use multiply function directly
// if the number is big then change double to long double
//////////////

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