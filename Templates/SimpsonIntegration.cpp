
ld f(ld x)
{
	// return x;
	ld temp = x/ld(a);
	// return temp;
	return b * sqrtl(1 - temp * temp);
}
ld eps = 1e-25;

ld simpson(ld fl, ld fr, ld fmid, ld l, ld r)
{
	return (fl + fr + 4 * fmid) * (r - l) / 6;
}

ld rsimpson(ld slr, ld fl, ld fr, ld fmid, ld l, ld r)
{
	ld mid = (l + r) / 2;
	ld fml = f((l + mid) / 2);
	ld fmr = f((r + mid) / 2);
	ld slm = simpson(fl, fmid, fml, l, mid);
	ld smr = simpson(fmid, fr, fmr, mid, r);
	db(l, r, mid, slr, slm, smr);
	if (fabs(slr - slm - smr) < eps)
		return slm + smr;
	return rsimpson(slm, fl, fmid, fml, l, mid) + rsimpson(smr, fmid, fr, fmr, mid, r);
}

ld Integral(ld start, ld end)
{
	ld mid = (start + end) / 2;
	ld fl = f(start);
	ld fr = f(end);
	ld fmid = f(mid);
	return rsimpson(simpson(fl, fr, fmid, start, end), fl, fr, fmid, start, end);
}

ld Area(int x)
{
	return 2*Integral(-a, x);
}
