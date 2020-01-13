typedef int coord_t;		// coordinate type
typedef long long coord2_t; // must be big enough to hold 2*max(|coordinate|)^2

struct Point
{
	coord_t x, y;
	bool operator<(const Point &p) const
	{
		return x < p.x || (x == p.x && y < p.y);
	}
};

// 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
// Returns a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
coord2_t cross(const Point &O, const Point &A, const Point &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<Point> convex_hull(vector<Point> &P)
{
	size_t n = P.size(), k = 0;
	if (n <= 3)
		return P;
	vector<Point> H(2 * n);
	// Sort points lexicographically
	sort(P.begin(), P.end());
	// Build lower hull
	for (size_t i = 0; i < n; ++i)
	{
		while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0)
			k--;
		H[k++] = P[i];
	}
	// Build upper hull
	for (size_t i = n - 1, t = k + 1; i > 0; --i)
	{
		while (k >= t && cross(H[k - 2], H[k - 1], P[i - 1]) <= 0)
			k--;
		H[k++] = P[i - 1];
	}
	H.resize(k - 1);
	return H;
}

double polygonArea(vector<Point> Polygon)
{
	// Initialze area
	long long area = 0;
	int n = Polygon.size();
	// Calculate value of shoelace formula
	int j = n - 1;
	for (int i = 0; i < n; i++)
	{
		area += ((ll)Polygon[j].x + Polygon[i].x) * (Polygon[j].y - Polygon[i].y);
		// area += (X[j] + X[i]) * (Y[j] - Y[i]);
		j = i; // j is previous vertex to i
	}

	// Return absolute value
	return abs(area / 2.0);
}
