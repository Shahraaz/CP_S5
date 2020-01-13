//https://www.swtestacademy.com/intersection-convex-polygons-algorithm/
//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
#define Debug 1
#ifdef Debug
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__);
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
#endif
typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
const long long mod = 1000000007;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

///////////////////////////////////////////////////////////////////////

typedef complex<ld> point;

const ld EPS = 1e-8;
bool equal(ld a, ld b)
{
	return abs(a - b) <= EPS;
}

typedef vector<point> Polygon;

double area(Polygon &a)
{
	double answer = 0;
	int n = a.size();
	for (int i = 0; i < n; ++i)
		answer += imag(a[i] + a[(i + 1) % n]) * real(a[(i + 1) % n] - a[i]);
	answer /= 2;
	return fabs(answer);
}

void printPolygon(Polygon &a)
{
	cout << "Polygon's area is " << area(a) << " ans points are ";
	for (auto x : a)
		cout << x << ' ';
	cout << '\n';
}

int sign(ld a)
{
	if (equal(a, 0))
		return 0;
	if (a < 0)
		return -1;
	return 1;
}

int ccw(point o, point a, point b)
{
	a = a - o;
	b = b - o;
	return sign(real(a) * imag(b) - imag(a) * real(b));
}

bool pointOnLine(point p1, point e1, point &p)
{
	ld x = real(p);
	if (ccw(p1, e1, p) != 0)
		return false;
	if (real(p1) <= x && x <= real(e1))
		return true;
	if (real(e1) <= x && x <= real(p1))
		return true;
	return false;
}

point *getIntersectionPoint(point p1, point e1, point p2, point e2)
{
	ld a1 = imag(e1 - p1);
	ld b1 = real(p1 - e1);
	ld c1 = a1 * real(p1) + b1 * imag(p1);

	ld a2 = imag(e2 - p2);
	ld b2 = real(p2 - e2);
	ld c2 = a2 * real(p2) + b2 * imag(p2);

	ld det = a1 * b2 - a2 * b1;
	if (equal(det, 0))
		return NULL;
	else
	{
		ld x = (b2 * c1 - b1 * c2) / det;
		ld y = (c2 * a1 - c1 * a2) / det;
		if (real(p1) <= x && x <= real(e1))
		{
			if (real(p2) <= x && x <= real(e2))
			{
				if (imag(p1) <= y && y <= imag(e1))
				{
					if (imag(p2) <= y && y <= imag(e2))
						return new point(x, y);
					if (imag(e2) <= y && y <= imag(p2))
						return new point(x, y);
				}
				if (imag(e1) <= y && y <= imag(p1))
				{
					if (imag(p2) <= y && y <= imag(e2))
						return new point(x, y);
					if (imag(e2) <= y && y <= imag(p2))
						return new point(x, y);
				}
			}
			if (real(e2) <= x && x <= real(p2))
			{
				if (imag(p1) <= y && y <= imag(e1))
				{
					if (imag(p2) <= y && y <= imag(e2))
						return new point(x, y);
					if (imag(e2) <= y && y <= imag(p2))
						return new point(x, y);
				}
				if (imag(e1) <= y && y <= imag(p1))
				{
					if (imag(p2) <= y && y <= imag(e2))
						return new point(x, y);
					if (imag(e2) <= y && y <= imag(p2))
						return new point(x, y);
				}
			}
		}
		if (real(e1) <= x && x <= real(p1))
		{
			if (real(p2) <= x && x <= real(e2))
			{
				if (imag(p1) <= y && y <= imag(e1))
				{
					if (imag(p2) <= y && y <= imag(e2))
						return new point(x, y);
					if (imag(e2) <= y && y <= imag(p2))
						return new point(x, y);
				}
				if (imag(e1) <= y && y <= imag(p1))
				{
					if (imag(p2) <= y && y <= imag(e2))
						return new point(x, y);
					if (imag(e2) <= y && y <= imag(p2))
						return new point(x, y);
				}
			}
			if (real(e2) <= x && x <= real(p2))
			{
				if (imag(p1) <= y && y <= imag(e1))
				{
					if (imag(p2) <= y && y <= imag(e2))
						return new point(x, y);
					if (imag(e2) <= y && y <= imag(p2))
						return new point(x, y);
				}
				if (imag(e1) <= y && y <= imag(p1))
				{
					if (imag(p2) <= y && y <= imag(e2))
						return new point(x, y);
					if (imag(e2) <= y && y <= imag(p2))
						return new point(x, y);
				}
			}
		}
	}
	return NULL;
}

bool compare(point a, point b)
{
	if (real(a) == real(b))
		return imag(a) < imag(b);
	return real(a) < real(b);
}

bool isPointInsidePolygon(point p, Polygon Poly)
{
	int n = Poly.size();
	if (n < 3)
		return false;
	point extreme(1e9, imag(p));
	int i, count, next;
	i = count = 0;
	ld maxi = -mod, mini = mod;
	for (auto x : Poly)
	{
		maxi = max(maxi, imag(x));
		mini = min(mini, imag(x));
	}
	vector<point> S;
	do
	{
		next = (i + 1) % n;
		auto it = getIntersectionPoint(Poly[i], Poly[next], p, extreme);
		if (it != NULL)
		{
			auto v = *it;
			if (equal(imag(v), maxi) || equal(imag(v), mini))
			{
				// cout << p << ' ' << "outside\n";
				// printPolygon(Poly);
				return false;
			}
			else
				S.pb(v);
			// cout << Poly[i] << ' ' << Poly[next] << ' ' << p << ' ' << extreme << " intersect at " << (*it) << '\n';
			if (ccw(Poly[i], Poly[next], p) == 0)
			{
				// cout << Poly[i] << ' ' << Poly[next] << ' ' << p << ' ' << "are collinear" << '\n';
				auto it = pointOnLine(Poly[i], Poly[next], p);
				// if (it)
				// 	cout << Poly[i] << ' ' << Poly[next] << ' ' << p << ' ' << "p is on line " << '\n';
				// else
				// 	cout << Poly[i] << ' ' << Poly[next] << ' ' << p << ' ' << "p is not on line " << '\n';
				return it;
			}
			// else
			// 	cout << Poly[i] << ' ' << Poly[next] << ' ' << p << ' ' << "are not collinear" << '\n';
		}
		// else
		// 	cout << Poly[i] << ' ' << Poly[next] << ' ' << p << ' ' << extreme << " dont't intersect " << '\n';
		i = next;
	} while (i != 0);
	sort(S.begin(),S.end(),compare);
	S.erase(unique(S.begin(),S.end()),S.end());
	count = S.size();
	// if ((count & 1))
	// 	cout << p << ' ' << "inside\n";
	// else
	// 	cout << p << ' ' << "outside\n";
	// printPolygon(Poly);
	return (count & 1);
}

Polygon getIntersectionPoints(point p1, point e1, Polygon Poly)
{
	Polygon I;
	int n = Poly.size();
	int i, next;
	i = 0;
	do
	{
		next = (i + 1) % n;
		auto it = getIntersectionPoint(p1, e1, Poly[i], Poly[next]);
		if (it != NULL)
		{
			I.push_back(*it);
		}
		i = next;
		delete it;
	} while (i != 0);
	return I;
}

void Addpoints(Polygon &pool, Polygon newpoints)
{
	for (auto x : newpoints)
	{
		bool found = false;
		for (auto y : pool)
		{
			if (equal(real(y), real(x)) && equal(imag(y), imag(x)))
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			// cout << x << " added to pool\n";
			pool.push_back(x);
		}
	}
}

point mid;
bool cmp(point a, point b)
{
	return arg(a - mid) < arg(b - mid);
}
void OrderClockwise(vector<point> &points)
{
	mid = point(0, 0);
	for (auto x : points)
		mid += x;
	mid /= points.size();
	// cout << "mid " << mid << '\n';
	sort(points.begin(), points.end(), cmp);
}

Polygon GetIntersectionOfPolygons(Polygon &a, Polygon &b)
{
	Polygon pool;
	for (auto x : a)
		if (isPointInsidePolygon(x, b))
			Addpoints(pool, Polygon(1, x));
	for (auto x : b)
		if (isPointInsidePolygon(x, a))
			Addpoints(pool, Polygon(1, x));
	int i = 0, n = a.size();
	int next = (i + 1) % n;
	do
	{
		next = (i + 1) % n;
		Addpoints(pool, getIntersectionPoints(a[i], a[next], b));
		i = next;
	} while (i != 0);
	// printPolygon(pool);
	OrderClockwise(pool);
	// cout << "After Ordering\n";
	// printPolygon(pool);
	return pool;
}
