const int kmod = 1000000007;

int mul(int a, int b, int mod = kmod)
{
	return (long long)a * b % mod;
}

int power(int base, int index, int mod = kmod)
{
	if (index == 0)
		return 1;
	int temp = power(base, index / 2, mod);
	temp = mul(temp, temp, mod);
	if (index & 1)
		temp = mul(temp, base, mod);
	return temp;
}
