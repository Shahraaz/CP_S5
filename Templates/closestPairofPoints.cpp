typedef complex<ll> point;
bool cmp(point a, point b)
{
	if (real(a) == real(b))
		return imag(a) < imag(b);
	return real(a) < real(b);
}

bool cmpy(point a, point b)
{
	if (imag(a) == imag(b))
		return real(a) < real(b);
	return imag(a) < imag(b);
}

ll DandC(vector<point> &Points, int begin, int end)
{
	if (begin == end)
		return 1e18;
	int m = (begin + end) / 2;
	ll d = min(DandC(Points, begin, m), DandC(Points, m + 1, end));
	vector<point> V;
	point mid = Points[m];
	for (int i = begin; i <= end; ++i)
	{
		auto x = Points[i];
		if (norm(point(real(x - mid), 0)) < d)
			V.pb(x);
	}
	sort(V.begin(),V.end(),cmpy);
	int s = V.size();
	for (int i = 0; i < s; ++i)
		for (int j = i + 1; j < s; ++j)
		{
			db(i, j, V[i], V[j], V[i] - V[j], norm(V[i] - V[j]), d);
			if (norm(V[i] - V[j]) < d)
				d = norm(V[i] - V[j]);
			else break;
		}
	return d;
}
