//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
#ifdef WIN32
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
	std::cerr << name << " { ";
	for (const auto &v : arg)
		cerr << v << ' ';
	cerr << " }\n";
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
#define f first
#define s second
#define pb push_back
const long long mod = 1000000007;
auto TimeStart = chrono::steady_clock::now();

const int nax = 2e5 + 10;
using ld = double;
using cd = complex<ld>;
const ld PI = acosl(-1);

void fft(vector<cd> &a, bool invert)
{
	int n = a.size();
	if (n == 1)
		return;
	vector<cd> a0(n / 2), a1(n / 2);
	for (int i = 0; 2 * i < n; ++i)
	{
		a0[i] = a[2 * i];
		a1[i] = a[2 * i + 1];
	}
	fft(a0, invert);
	fft(a1, invert);
	ld ang = 2 * PI / n * (invert ? -1 : 1);
	cd w(1), wn(cosl(ang), sinl(ang));
	for (int i = 0; 2 * i < n; ++i)
	{
		a[i] = a0[i] + w * a1[i];
		a[i + n / 2] = a0[i] - w * a1[i];
		if (invert)
		{
			a[i] /= 2;
			a[i + n / 2] /= 2;
		}
		w *= wn;
	}
}

vector<ll> mult(vector<ll> a, vector<ll> b)
{
	vector<cd> fa(a.begin(), a.end());
	vector<cd> fb(b.begin(), b.end());
	int n = 1;
	while (n < a.size() + b.size())
		n <<= 1;
	fa.resize(n);
	fb.resize(n);
	fft(fa, false);
	fft(fb, false);
	for (int i = 0; i < n; ++i)
		fa[i] *= fb[i];
	fft(fa, true);
	vector<ll> res(n);
	for (int i = 0; i < n; ++i)
		res[i] = round(fa[i].real());
	// reverse(res.begin(), res.end());
	return res;
}

void solve()
{
	ll n;
	cin >> n;
	++n;
	vector<ll> a(n), b(n);
	for (auto &x : a)
		cin >> x;
	for (auto &x : b)
		cin >> x;
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	vector<ll> res = mult(a, b);
	// pc(res);
	// reverse(res.begin(), res.end());
	// pc(res);
	// for (int i = 0; i < (2 * n + 1); ++i)
	// 	cout << res[2 * res.size() - i - 1] << ' ';
	vector<ll> res2;
	for (int i = 0; i < 2 * n - 1; ++i)
		res2.pb(res[i]);
	reverse(res2.begin(), res2.end());
	for (int i = 0; i < 2 * n - 1; ++i)
		cout << res2[i] << ' ';
	cout << '\n';
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (t--)
		solve();
#ifdef WIN32
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}