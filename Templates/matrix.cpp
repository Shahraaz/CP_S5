struct matrix
{
	vector<vector<long long>> MAT;
	matrix() {}
	matrix(long long n, long long m)
	{
		MAT.resize(n, vector<long long>(m));
	}
};

matrix mul(cosnt matrix &A, const matrix &B)
{
	int n = A.MAT.size(), m = B.MAT.size(), k = B.MAT[0].size();
	matrix X(n, k);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < k; ++j)
		{
			X.MAT[i][j] = 0;
			for (int k = 0; k < m; ++k)
				X.MAT[i][j] = (X.MAT[i][j] + A.MAT[i][k] * B.MAT[k][j]);
		}
	return X;
}

matrix unit(int n)
{
	matrix X(n, n);
	for (int i = 0; i < n; ++i)
		X.MAT[i][i] = 1;
	return X;
}

matrix power(const matrix &A, long long index)
{
	matrix temp;
	if (index == 0)
		return unit(A.MAT.size());
	temp = power(A, index / 2);
	temp = mul(temp, temp);
	if (index & 1)
		return mul(temp, A);
	return temp;
}
