#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back
#define mp make_pair
#define deb(x) cout<< #x << " " << x << "\n";
#define MAX 9223372036854775807
#define MIN -9223372036854775807
#define PI 3.141592653589
#define setbits(n) __builtin_popcountll(n)
#define mkunique(a) a.resize(unique(a.begin(),a.end())-a.begin());
const ll mod=1e9+7;
 

 
int main() {
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll T=clock();
 
    ll t;
    cin>>t;
    while(t--){
        ll n,m;
        cin>>n>>m;
        vector<string> a(n), b;
        vector<vector<pair<ll,ll>>> p(26);
        for(ll i=0;i<n;i++){
            cin>>a[i];
            string s;
            for(ll j=0;j<m;j++){
                p[a[i][j]-'a'].pb({i,j});
                s+='.';
            }
            b.pb(s);
            
        }
        vector<vector<ll>> ans(26);
        bool ok=true;
        ll len=-1;
        for(ll i=0;i<26;i++){
            ans[i].clear();
            if(p[i].size()==0) continue;
            len=i;
            sort(p[i].begin(),p[i].end());
            pair<ll,ll> x=p[i][0], y=p[i][p[i].size()-1];
            if(x.first==y.first){
                for(int j=x.second;j<=y.second;j++)
                    b[x.first][j]='a'+i;
            }
            else if(x.second==y.second){
                for(int j=x.first;j<=y.first;j++)
                    b[j][x.second]='a'+i;
            }
            else ok=false;
            ans[i]={x.first,x.second,y.first,y.second};
        }
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(a[i][j]!=b[i][j])
                    ok=false;
        if(!ok){
            cout<<"NO\n";
            continue;
        }
        cout<<"YES\n";
        cout<<len+1<<"\n";
        if(len==-1) continue;
        vector<ll> c=ans[len];
        for(ll i=0;i<=len;i++){
            if(ans[i].size()==0)
                for(ll j=0;j<4;j++)
                    cout<<c[j]+1<<" ";
            else
                for(ll j=0;j<4;j++)
                    cout<<ans[i][j]+1<<" ";
            cout<<"\n";
        }
    }
    
 
    cerr<<"\n\nTIME: "<<(double)(clock()-T)/CLOCKS_PER_SEC<<" sec\n";
    T = clock();
    return 0;
}