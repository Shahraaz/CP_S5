typedef vector<ll> row;

struct matrix
{
	vector<row> MAT; 
	matrix(){}
	matrix(ll n,ll m)
	{
		MAT.resize(n,row(m));
	}
	
};

matrix mul(matrix &A,matrix &B)
{
	int n = A.MAT.size(),m = B.MAT.size(),k = B.MAT[0].size();
	matrix X(n,k) ;
	for(int i=0;i<n;++i)
		for(int j=0;j<k;++j)
		{
			X.MAT[i][j] = 0;
			for(int k=0;k<m;++k)
				X.MAT[i][j] = (X.MAT[i][j] + A.MAT[i][k]*B.MAT[k][j])%mod;
		}
	return X;
}

matrix unit(int n)
{
	matrix X(n,n);
	for(int i=0;i<n;++i)
		X.MAT[i][i] = 1;
	return X;
}

matrix POWER(matrix &A,ll index)
{
	db("POWER",index);
	matrix temp;
	if(index == 0)
		return unit(A.MAT.size());
	temp = POWER(A,index/2);
	temp = mul(temp,temp);
	if(index&1) 
		return mul(temp,A);
	return temp;
}


