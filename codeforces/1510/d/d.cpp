#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back
#define mp make_pair
#define deb(x) cout<< #x << " " << x << "\n";
#define MAX 9223372036854775807
#define MIN -9223372036854775807
#define setbits(n) __builtin_popcountll(n)
#define mkunique(a) a.resize(unique(a.begin(),a.end())-a.begin());
const ll mod=1e9+7;

const int N=1e5+10;
double dp[N][10];
bool vis[N][10];
vector<ll> a(N);
ll n,d;

double go(ll pos, ll ld){
    if(pos==n){
        if(ld==d) return dp[pos][ld] = 0;
        else return dp[pos][ld] = -mod;
    }
    if(vis[pos][ld])
        return dp[pos][ld];
    vis[pos][ld]=true;
    double ans=-mod*mod;
    ans = go(pos+1,ld);
    ll dd=a[pos]%10;
    ans = max(ans, log2(a[pos])+go(pos+1,ld*dd%10));
    return dp[pos][ld]=ans;
}   

int main(){
 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll T=clock();

    cin>>n>>d;
    for(ll i=0;i<n;i++)
        cin>>a[i];
    memset(vis,false,sizeof(vis));
    ll val=go(0,1);
    if(val<=0){
        cout<<-1;
        return 0;
    }
    vector<ll> ans;
    ll i=0, d=1;
    while(i<n){
        double c=log2(a[i]);
        ll dd=(a[i]%10)*d%10;
        if(dp[i][d]==dp[i+1][d]){
            i++;
        }
        else if(dp[i][d]==c+dp[i+1][dd]){
            ans.pb(a[i]);
            i++; d=dd;
        }
        else assert(false);
    }
    cout<<ans.size()<<"\n";
    for(ll i=0;i<ans.size();i++)
        cout<<ans[i]<<" ";




 
 
    cerr<<"\n\nTIME: "<<(double)(clock()-T)/CLOCKS_PER_SEC<<" sec\n";
    T = clock();
    return 0;
}