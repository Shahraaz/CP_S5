template <typename Arg>
class modint
{
	public:
	Arg num;
	int Mmod = 1000000007;
	modint ()
	{ 
		this->num = 0;
	}
	modint (Arg a)
	{
		a %= Mmod;
		if(a<0)
			a+=Mmod;
		this->num = a;
	}
	modint operator+(modint a)
	{
		modint temp;
		temp = *this;
		temp.num += a.num;
		if(temp.num > Mmod)
			temp.num -= Mmod;
		return temp;
	}
	modint operator-(modint a)
	{
		modint temp;
		temp = *this;
		temp.num -= a.num;
		if(temp.num < 0)
			temp.num += Mmod;
		return temp;
	}
	modint operator*(modint a)
	{
		modint temp;
		temp = *this;
		temp.num *= a.num;
		temp.num %= Mmod;
		return temp;
	}
	bool operator<(modint a)
	{
		return this->num < a.num; 
	}
	bool operator>(modint a)
	{
		return this->num > a.num; 
	}
	modint Power(modint a,int index)
	{
		if(index==0)
			return modint<Arg>(1);
		modint temp = Power(a,index/2);
		temp = temp*temp;
		if(index&1)
			temp = temp*a;
		return temp;
	}
};

typedef modint<ll> modll;

