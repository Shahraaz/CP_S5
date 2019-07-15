vector<ll> Sum;
int _n;
void Sum_Pre(vector<int> &v)
{
	_n = v.size();
	Sum.resize(_n);
	Sum[0] = v[0];
	for (int i = 1; i < n; ++i)
		Sum[i] = Sum[i - 1] + v[i];
}

ll rangesum(int start, int end)
{
	if (start == 0)
		return Sum[end];
	return Sum[end] - Sum[start - 1];
}