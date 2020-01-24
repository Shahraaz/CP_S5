/*reference https://github.com/Ashishgup1/Competitive-Coding/blob/master/Convex%20Hull%20(Graham's%20Scan).cpp
COmputational Geometry and Computational Graphics in C++ by Michael J.Laszlo*/

/////////////////////////////////

typedef int typeone;
typedef long double typetwo;
enum
{
    LEFT,
    RIGHT,
    BEYOND,
    BEHIND,
    BETWEEN,
    ORIGIN,
    DESTINATION
};

const long double EPS = 1e-9;
class point
{
public:
    typeone x, y;
    point(typeone _x = 0, typeone _y = 0) : x(_x), y(_y) {}
    bool operator<(const point &p) const
    {
        return (x < p.x) || (x == p.x && y < p.y);
    }
    bool operator>(point &p)
    {
        return (x > p.x) || (x == p.x && y > p.y);
    }
    bool operator==(point &p)
    {
        return x == p.x && y == p.y;
    }
    bool operator!=(point &p)
    {
        return !(*this == p);
    }
    point operator=(const point &p)
    {
        x = p.x;
        y = p.y;
        return *this;
    }
    point operator*(typetwo s)
    {
        return point(s * x, s * y);
    }
    point operator+(point &p)
    {
        return point(x + p.x, y + p.y);
    }
    point operator-(point &p)
    {
        return point(x - p.x, y - p.y);
    }
    typeone operator[](const int i)
    {
        return i == 0 ? x : y;
    }
    typeone orientation(point p0, point p1, point p2)
    {
        p1 = p1 - p0;
        p2 = p2 - p0;
        typeone sa = p1.x * p2.y - p2.x * p1.y;
        if (sa > 0)
            return 1;
        if (sa < 0)
            return -1;
        return 0;
    }
    typeone len2()
    {
        return x * x + y * y;
    }
    typetwo len()
    {
        return sqrtl((long double)len2());
    }

    typetwo PolarAngle()
    {
        if (x == 0 && y == 0)
            return 0;
        if (x == 0)
            return (y > 0) ? 90 : 270;
        typetwo theta = atanf((long double)y / x);
        theta *= 180 / (long double)3.141592653;
        if (x > 0)
            return y >= 0 ? theta : 360 + theta;
        else
            return 180 + theta;
    }
    int classify(point &p0, point &p1)
    {
        point p2 = *this;
        point a = p1 - p0;
        point b = p2 - p0;
        typeone sa = a.x * b.y - b.x * a.y;
        if (sa > 0)
            return LEFT;
        if (sa < 0)
            return RIGHT;
        if ((a.x * b.x < 0) || (a.y * b.y < 0))
            return BEHIND;
        if (a.len2() < b.len2())
            return BEYOND;
        if (p0 == p2)
            return ORIGIN;
        if (p0 == p1)
            return DESTINATION;
        return BETWEEN;
    }
};

typeone dotproduct(point a, point b)
{
    return a.x * b.x + a.y * b.y;
}

typeone Area2(point a, point b, point c)
{
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

bool left(point a, point b, point c)
{
    return Area2(a, b, c) > 0;
}

bool left2(point a, point b, point c)
{
    return Area2(a, b, c) >= 0;
}

bool collinear(point a, point b, point c)
{
    return Area2(a, b, c) == 0;
}

bool Xor(bool x, bool y)
{
    return (!x) ^ (!y);
}

bool IntersectProp(point a, point b, point c, point d)
{
    if (collinear(a, b, c) || collinear(a, b, d) || collinear(c, d, a) || collinear(c, d, b))
        return true;
    return (Xor(left(a, b, c), left(a, b, d)) && Xor(left(c, d, a), left(c, d, b)));
}

bool between(point a, point b, point c)
{
    if (!collinear(a, b, c))
        return false;
    if (a.x != b.x)
        return ((a.x <= c.x) && (c.x <= b.x)) || ((a.x >= c.x) && (c.x >= b.x));
    return ((a.y <= c.y) && (c.y <= b.y)) || ((a.y >= c.y) && (c.y >= b.y));
}

bool Intersect(point a, point b, point c, point d)
{
    return IntersectProp(a, b, c, d) || between(a, b, c) || between(a, b, d) || between(c, d, a) || between(c, d, b);
}


///////////////////////////////////

typedef int typeone;
typedef long double typetwo;
enum
{
    LEFT,
    RIGHT,
    BEYOND,
    BEHIND,
    BETWEEN,
    ORIGIN,
    DESTINATION
};

const long double EPS = 1e-9;
class point
{
public:
    typeone x, y;
    point(typeone _x = 0, typeone _y = 0) : x(_x), y(_y) {}
    bool operator<(const point &p) const
    {
        return (x < p.x) || (x == p.x && y < p.y);
    }
    bool operator>(point &p)
    {
        return (x > p.x) || (x == p.x && y > p.y);
    }
    bool operator==(point &p)
    {
        return x == p.x && y == p.y;
    }
    bool operator!=(point &p)
    {
        return !(*this == p);
    }
    point operator=(const point &p)
    {
        x = p.x;
        y = p.y;
        return *this;
    }
    point operator*(typetwo s)
    {
        return point(s * x, s * y);
    }
    point operator+(point &p)
    {
        return point(x + p.x, y + p.y);
    }
    point operator-(point &p)
    {
        return point(x - p.x, y - p.y);
    }
    typeone operator[](const int i)
    {
        return i == 0 ? x : y;
    }
    typeone orientation(point p0, point p1, point p2)
    {
        p1 = p1 - p0;
        p2 = p2 - p0;
        typeone sa = p1.x * p2.y - p2.x * p1.y;
        if (sa > 0)
            return 1;
        if (sa < 0)
            return -1;
        return 0;
    }
    typeone len2()
    {
        return x * x + y * y;
    }
    typetwo len()
    {
        return sqrtl((long double)len2());
    }

    typetwo PolarAngle()
    {
        if (x == 0 && y == 0)
            return 0;
        if (x == 0)
            return (y > 0) ? 90 : 270;
        typetwo theta = atanf((long double)y / x);
        theta *= 180 / (long double)3.141592653;
        if (x > 0)
            return y >= 0 ? theta : 360 + theta;
        else
            return 180 + theta;
    }
    int classify(point &p0, point &p1)
    {
        point p2 = *this;
        point a = p1 - p0;
        point b = p2 - p0;
        typeone sa = a.x * b.y - b.x * a.y;
        if (sa > 0)
            return LEFT;
        if (sa < 0)
            return RIGHT;
        if ((a.x * b.x < 0) || (a.y * b.y < 0))
            return BEHIND;
        if (a.len2() < b.len2())
            return BEYOND;
        if (p0 == p2)
            return ORIGIN;
        if (p0 == p1)
            return DESTINATION;
        return BETWEEN;
    }
    int classify(Edge &e)
    {
        return classify(e.org, e.dest);
    }
    typetwo distance(Edge &e)
    {
        Edge ab = e;
        ab.flip().rot();
        point n(ab.dest - ab.org);
        n = n * (1 / n.len());
        Edge f(*this, *this + n);
        double t;
        f.intersect(e, t);
        return t;
    }
};

typeone dotproduct(point a, point b)
{
    return a.x * b.x + a.y * b.y;
}

typeone Area2(point a, point b, point c)
{
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

bool left(point a, point b, point c)
{
    return Area2(a, b, c) > 0;
}

bool left2(point a, point b, point c)
{
    return Area2(a, b, c) >= 0;
}

bool collinear(point a, point b, point c)
{
    return Area2(a, b, c) == 0;
}

bool Xor(bool x, bool y)
{
    return (!x) ^ (!y);
}

bool IntersectProp(point a, point b, point c, point d)
{
    if (collinear(a, b, c) || collinear(a, b, d) || collinear(c, d, a) || collinear(c, d, b))
        return true;
    return (Xor(left(a, b, c), left(a, b, d)) && Xor(left(c, d, a), left(c, d, b)));
}

bool between(point a, point b, point c)
{
    if (!collinear(a, b, c))
        return false;
    if (a.x != b.x)
        return ((a.x <= c.x) && (c.x <= b.x)) || ((a.x >= c.x) && (c.x >= b.x));
    return ((a.y <= c.y) && (c.y <= b.y)) || ((a.y >= c.y) && (c.y >= b.y));
}

bool Intersect(point a, point b, point c, point d)
{
    return IntersectProp(a, b, c, d) || between(a, b, c) || between(a, b, d) || between(c, d, a) || between(c, d, b);
}

//given line ax + by + c = 0 and circle eith center origin and radius r number of intersection points and their co ordinates

typedef long double ld;
void Circle_Intersect(ld a, ld b, ld c, ld r)
{
    ld x0 = -a * c / (a * a + b + b), yo = -b * c / (a * a + b * b);
    if (c * c > r * r * (a * a + b * b) + EPS)
        cout << 0 << '\n';
    else if (abs(c * c - r * r * (a * a + b * b)) < EPS)
    {
        cout << 1 << '\n';
        cout << x0 << ' ' << y0 << '\n';
    }
    else
    {
        ld d = r * r - c * c / (a * a + b * b);
        ld mult = sqrtl(d / (a * a + b * b));
        ld ax, ay, bx, by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;
        cout << 2 << '\n';
        cout << ax << ' ' << ay << '\n';
        cout << bx << ' ' << by << '\n';
    }
}

enum
{
    COLLINEAR,
    PARALLEL,
    SKEW,
    SKEW_CROSS,
    SKEW_NO_CROSS
};
class Edge
{
public:
    point org, dest;
    Edge(point _org = *new point(0, 0), point _dest = *new point(1, 0)) : org(_org), dest(_dest) {}
    Edge rot()
    {
        point m = (org + dest) * 0.5;
        point v = dest - org;
        point n(v.y, -v.x);
        org = m - (n * 0.5);
        dest = m + (n * 0.5);
        return *this;
    }
    Edge flip()
    {
        return rot().rot();
    }
    point Point(long double t)
    {
        return point(org + (dest - org) * t);
    }
    int intersect(Edge &e, long double &t)
    {
        point a = org;
        point b = dest;
        point c = e.org;
        point d = e.dest;
        point n((d - c).y, (c - d).x);
        long double denom = dotproduct(n, b - a);
        if (denom == 0.0)
        {
            int aclass = org.classify(e);
            if ((aclass == LEFT) || (aclass == RIGHT))
                return PARALLEL;
            return COLLINEAR;
        }
        long double num = dotproduct(n, a - c);
        t = -num / denom;
        return SKEW;
    }
    int cross(Edge &e, long double &t)
    {
        double s;
        int crosstype = e.intersect(*this, s);
        if ((crosstype == COLLINEAR) || (crosstype == PARALLEL))
            return crosstype;
        if ((s < 0.0) || (s > 1.0))
            return SKEW_NO_CROSS;
        intersect(e, t);
        if ((0.0 <= t) && (t <= 1.0))
            return SKEW_CROSS;
        return SKEW_NO_CROSS;
    }
    bool isVertical()
    {
        return org.x == dest.x;
    }
    long double slope()
    {
        if (!isVertical())
            return (dest.y - org.y) / (dest.x - org.x);
        return LDBL_MAX;
    }
};
typedef long long tslope;
typedef long double tconstant;
typedef long double D2;
class Line
{
public:
	// y - m*x - c = 0;
	tslope m;
	tconstant c;
	bool isverticle;
	tconstant xincident;
	Line(tslope _m = 0, tconstant _c = 0, bool b = false, tconstant _xincident = 0) : m(_m), c(_c), isverticle(b), xincident(_xincident) {}
	D2 Distance2(point p)
	{
		if (isverticle)
			return abs(xincident - p.x);
		return abs(p.y - m * (p.x) - c) / sqrtl(1 + m * m);
	}
	bool isDLessThanx(point p, long long D)
	{
		return Distance2(p) <= D;
	}
};
