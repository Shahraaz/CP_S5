#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;
#define f(a , b) for(auto i = a;i < b;i++)

vector < ll > sieve;
ll prime[1000001]; 
void SieveOfEratosthenes(ll b) 
{  
  	for(ll i = 2;i <= b;i++)
  		prime[i] = 1;
    for (ll p=2; p*p <= b; p++) 
    { 
        if (prime[p] == 1) 
        { 
	        for (ll i = p*p; i <= b; i += p) 
	            prime[i] = 0; 
        } 
    } 

} 
int main()
{
	ll a, b, k, idx, l, x, maxi = 0;
	cin >> a >> b >> k;
	SieveOfEratosthenes(b);


	for(ll i = a + 1;i <= b; ++i) prime[i]+=prime[i-1];

	prime[a-1]=0;
	if(prime[b] < k) cout << "-1\n";

	else
	{
		ll res = 1,it;
		for(it = a - 1;it + res <= b;++it)
			while(it + res <= b && prime[it + res]-prime[it] < k)
				 res++;
 
		cout << res << "\n";
	}
	return 0;
}