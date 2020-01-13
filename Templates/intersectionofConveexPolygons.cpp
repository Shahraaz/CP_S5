#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <map>
#include <set>
#include <cstdlib>
#include <queue>
using namespace std;

#include <math.h>
#include <complex>
#include <cstdio>
#include <algorithm>
using namespace std;

#define oo 1000000000
#define eps 1.0e-9
#define SGN(x) ((x) < -eps ? -1 : (x) > eps ? 1 : 0)
#define DET(a, b, c, d) ((a) * (d) - (b) * (c))
#define CRAMER1(a, b, x, c, d, y) (DET(x, b, y, d) / DET(a, b, c, d))

typedef complex<double> tComp;

int ccw(tComp a, tComp b, tComp c)
{
	double d = DET(real(b - a), real(c - a), imag(b - a), imag(c - a));
	return SGN(d);
}

int ccw5(tComp a, tComp b, tComp c)
{
	tComp e = b - a;
	tComp f = c - a;
	double d = DET(real(e), real(f), imag(e), imag(f));
	if (d > eps) // counterclockwise
		return 1;
	if (d < -eps ||										// clockwise
		real(e) * real(f) < 0 || imag(e) * imag(f) < 0) // b a c
		return -1;
	if (abs(e) < abs(f)) // a b c
		return 1;
	return 0; // b c a
}

int intersect(tComp a, tComp b, tComp c, tComp d)
{
	return ccw5(a, b, c) * ccw5(a, b, d) <= 0 && ccw5(c, d, a) * ccw5(c, d, b) <= 0;
}

tComp intersection(tComp a, tComp b, tComp c, tComp d)
{
	return a + CRAMER1(real(b - a), real(c - d), real(c - a),
					   imag(b - a), imag(c - d), imag(c - a)) *
				   (b - a);
}

int inside_cpoly(tComp p, int n, tComp a[])
{
	int left = 0;
	int right = 0;
	for (int i = 0; i < n; i++)
		switch (ccw(p, a[i], a[(i + 1) % n]))
		{
		case 1:
			left = 1;
			break;
		case -1:
			right = 1;
			break;
		}
	return !(left & right);
}

int startpos(int n, tComp p[])
{
	int j = 0;
	for (int k = 1; k < n; k++)
		if (imag(p[k]) < imag(p[j]) ||
			(imag(p[k]) == imag(p[j]) && real(p[k]) < real(p[j])))
			j = k;
	return j;
}

int nextpos(int n, tComp p[], int i)
{
	int j = 0;
	for (int k = 1; k < n; k++)
	{
		int c = ccw(p[i], p[j], p[k]);
		if (c == -1 || (c == 0 && abs(p[i] - p[k]) > abs(p[i] - p[j])))
			j = k;
	}
	return j;
}

// convex hull of (n, p[])
// yielding the m indices of the hull points saved in index
void convex_idx(int n, tComp p[], int &m, int index[])
{
	index[0] = startpos(n, p);
	for (m = 0; index[m] != index[0] || m == 0; m++)
		index[m + 1] = nextpos(n, p, index[m]);
}

typedef struct
{
	int n;
	tComp p[100];
} cpolygon;

// convex hull of (n, p[])
// returning a polygon
// Polygon should be non-empty !
// n <= 100
cpolygon convex(int n, tComp p[])
{
	int i, index[100];
	cpolygon ch;

	convex_idx(n, p, ch.n, index);
	for (i = 0; i < ch.n; i++)
		ch.p[i] = p[index[i]];
	return ch;
}

// area of an arbitrary polygon, n >= 0
double polyarea(int n, tComp p[])
{
	double area = 0;
	for (int i = 0; i < n; i++)
		area += 0.5 * imag(p[i] + p[(i + 1) % n]) * real(p[(i + 1) % n] - p[i]);
	return fabs(area);
}

double doit(int n, tComp *p, int m, tComp *q)
{
	tComp r[100];
	cpolygon cx;
	int i, j, k;
	for (i = k = 0; i < n; i++)
	{
		if (inside_cpoly(p[i], m, q))
		{
			r[k++] = p[i];
		}
		for (j = 0; j < m; j++)
		{
			if (i == 0 && inside_cpoly(q[j], n, p))
			{
				r[k++] = q[j];
			}
			if (intersect(p[i], p[(i + 1) % n], q[j], q[(j + 1) % m]))
			{
				r[k++] = intersection(p[i], p[(i + 1) % n], q[j], q[(j + 1) % m]);
			}
		}
	}
	cx = convex(k, r);
	return polyarea(cx.n, cx.p);
}

class ConvexPolygons
{
public:
	double overlap(vector<string> polygon1, vector<string> polygon2)
	{
		tComp p[100], q[100];
		int n = polygon1.size();
		int m = polygon2.size();
		for (int i = 0; i < n; i++)
		{
			double x, y;
			sscanf(polygon1[i].c_str(), "%lf %lf", &x, &y);
			p[i] = tComp(x, y);
		}
		for (int i = 0; i < m; i++)
		{
			double x, y;
			sscanf(polygon2[i].c_str(), "%lf %lf", &x, &y);
			q[i] = tComp(x, y);
		}
		return doit(n, p, m, q);
	}
};
