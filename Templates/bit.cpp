
struct BIT
{
	int N;
	vector<long long> bit;
 
	void init(int n)
	{
		N = n;
		bit.assign(n + 1, 0);
	}
 
	void update(int idx, long long val)
	{
		while(idx <= N)
		{
			bit[idx] += val;
			idx += idx & -idx;
		}
	}
 
	void updateMax(int idx, long long val)
	{
		while(idx <= N)
		{
			bit[idx] = max(bit[idx], val);
			idx += idx & -idx;
		}
	}
 
	long long pref(int idx)
	{
		long long ans = 0;
		while(idx > 0)
		{
			ans += bit[idx];
			idx -= idx & -idx;
		}
		return ans;
	}
 
	long long rsum(int l, int r)
	{
		return pref(r) - pref(l - 1);
	}
 
	long long prefMax(int idx)
	{
		long long ans = -2e9;
		while(idx > 0)
		{
			ans = max(ans, bit[idx]);
			idx -= idx & -idx;
		}
		return ans;
	}
};