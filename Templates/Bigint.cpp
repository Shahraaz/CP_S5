#include <bits/stdc++.h>
using namespace std;
const int base = 1000000000;
const int base_digit = 9;
struct Bigint
{
    vector<int> a;
    int sign;
    Bigint()
    {
    }
    void trim()
    {
        while (!a.empty() && !a.back())
            a.pop_back();
        if (a.empty())
            sign = 1;
    }
    Bigint(string s)
    {
        sign = 1;
        a.clear();
        int pos = 0;
        if (s[0] == '-')
        {
            sign = -sign;
            ++pos;
        }
        if (s[pos] == '+')
        {
            // sign = -sign;
            ++pos;
        }
        for (int i = s.size() - 1; i >= pos; i -= base_digit)
        {
            int x = 0;
            for (int j = max(pos, i - base_digit + 1); j <= i; ++j)
                x = x * 10 + s[j] - '0';
            a.push_back(x);
        }
        trim();
    }

    friend istream &operator>>(istream &stream, bigint &v)
    {
        string s;
        stream >> s;
        v.read(s);
        return stream;
    }

    friend ostream &operator<<(ostream &stream, const bigint &v)
    {
        if (v.sign == -1)
            stream << '-';
        stream << (v.a.empty() ? 0 : v.a.back());
        for (int i = (int)v.a.size() - 2; i >= 0; --i)
            stream << setw(base_digits) << setfill('0') << v.a[i];
        return stream;
    }

    bigint operator-() const
    {
        bigint res = *this;
        res.sign = -sign;
        return res;
    }

    bigint abs() const
    {
        bigint res = *this;
        res.sign *= res.sign;
        return res;
    }

    string to_string()
    {
        stringstream ss;
        ss << *this;
        string s;
        ss >> s;
        return s;
    }

    void operator=(const bigint &v)
    {
        sign = v.sign;
        a = v.a;
    }

    bigint operator+(const bigint &v) const
    {
        if (sign == v.sign)
        {
            bigint res = v;

            for (int i = 0, carry = 0; i < (int)max(a.size(), v.a.size()) || carry; ++i)
            {
                if (i == (int)res.a.size())
                    res.a.push_back(0);
                res.a[i] += carry + (i < (int)a.size() ? a[i] : 0);
                carry = res.a[i] >= base;
                if (carry)
                    res.a[i] -= base;
            }
            return res;
        }
        return *this - (-v);
    }

    bigint operator-(const bigint &v) const
    {
        if (sign == v.sign)
        {
            if (abs() >= v.abs())
            {
                bigint res = *this;
                for (int i = 0, carry = 0; i < (int)v.a.size() || carry; ++i)
                {
                    res.a[i] -= carry + (i < (int)v.a.size() ? v.a[i] : 0);
                    carry = res.a[i] < 0;
                    if (carry)
                        res.a[i] += base;
                }
                res.trim();
                return res;
            }
            return -(v - *this);
        }
        return *this + (-v);
    }
};