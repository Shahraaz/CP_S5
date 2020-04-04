#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        ll m,d;
        cin>>d>>m;
        ll r=0LL;
        //ll sum=0;
        while((1LL<<r)<=d)
        {
            r++;
        }
        r--;
       // cout<<"r  "<<r<<"\n";
        ll ans=1LL;
        for(ll i=0;i<r;i++)
        {
            ll y;
            y = 1LL<<i;
            y = y+1LL;
            ans = (ans*y)%m;
        }
        //cout<<"ans "<<ans<<endl;
        ll y;
        y = d - (1LL<<r);
        //cout<<y<<endl;
        y = y+2LL;
        ans = (ans*y)%m;
        //cout<<"ans "<<ans<<endl;
        ans = (ans -1LL + m)%m;
      //  cout<<"ans "<<ans<<endl;
        cout<<ans<<"\n";
    }
    return 0;
}