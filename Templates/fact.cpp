int _n = 1e5 + 10;
vector<ll> Fact(_n), Inv(_n);
int kmod = 1000000007;

ll mul(ll a, ll b)
{
	return a * b % kmod;
}

ll power(int base, int index)
{
	if (index == 0)
		return 1;
	ll temp = power(base, index / 2);
	temp = mul(temp, temp);
	if (index & 1)
		temp = mul(temp, base);
	return temp;
}

void pre()
{
	Fact[0] = 1;
	for (int i = 1; i < _n; ++i)
		Fact[i] = mul(Fact[i - 1], i);
	Inv[_n - 1] = power(Fact[_n - 1], kmod - 2);
	for (int i = _n - 2; i >= 0; --i)
		Inv[i] = mul(Inv[i + 1], (1 + i));
}

ll ncr(int n, int r)
{
	if (n < 0 || r < 0 || n - r < 0)
		return 0;
	return mul(Fact[n], mul(Inv[r], Inv[n - r]));
}