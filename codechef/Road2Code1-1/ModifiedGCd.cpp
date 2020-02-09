#include<bits/stdc++.h>
using namespace std;

typedef long long   ll;
const ll mod = 1e9 + 7;

#define speedup_IO      ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define forn(i,a,n)     for(ll i = a; i < n; i++)
#define ford(i,n,a)     for(ll i = n-1; i >= a; i--)
#define pb              push_back
#define lb              lower_bound
#define ub              upper_bound
#define pll             pair<ll,ll>
#define all(a)          (a).begin(),(a).end()
#define reset(a,x)      memset(a,x,sizeof(a))

ll mypow(ll base, ll exp) {ll res = 1; while (exp) {if (exp & 1) res = (res * base) % mod; exp >>= 1, base = (base * base) % mod;} return res;}
ll gcd(ll a, ll b)  { return b ? gcd(b, a % b) : a;            }
ll mult(ll a, ll b) { if (a < 0) {a += mod;} if (b < 0) {b += mod;} return ((a % mod) * (b % mod)) % mod; }
ll add(ll a, ll b)  { if (a < 0) {a += mod;} if (b < 0) {b += mod;} return (a % mod + b % mod) % mod;        }
ll sub(ll a, ll b)  { if (a < 0) {a += mod;} if (b < 0) {b += mod;} return (a % mod + mod - b % mod) % mod;  }

const ll inf = 1e18;
const int nax = 1e5 + 5;

int main()
{
	speedup_IO;
	ll a,b;
	cin>>a>>b;

	ll g = gcd(a,b);

	set<ll>factors;
	for(ll i=1;i*i<=g;i++)
	{
		if(g%i == 0)
		{
			factors.insert(i);
			factors.insert(g/i);
		}
	}

	ll n;
	cin>>n;

	ll low,high;
	forn(i,0,n)
	{
		cin>>low>>high;
		auto itr1 = factors.lb(low);
		auto itr2 = factors.lb(high);

		if(itr1 == factors.end())
		{
			cout<<-1<<endl;
		}
		else
		{
			if(itr2 == factors.end())
			{
				itr2--;
				if(*itr2<=high && *itr2>=low)
				{
					cout<<*itr2<<endl;
				}
				else
				{
					cout<<-1<<endl;
				}
			}
			else
			{
				if(itr2 == factors.begin())
				{
					if(*itr2<=high && *itr2>=low)
					{
						cout<<*itr2<<endl;
					}
					else
					{
						cout<<-1<<endl;
					}
				}
				else
				{
					if(*itr2>high)
					{
						itr2--;
						if(*itr2<=high && *itr2>=low)
						{
							cout<<*itr2<<endl;
						}
						else
						{
							cout<<-1<<endl;
						}
					}
					else
					{
						if(*itr2<=high && *itr2>=low)
						{
							cout<<*itr2<<endl;
						}
						else
						{
							cout<<-1<<endl;
						}
					}
				}
			}
		}
	}

	return 0;
}