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

vector<ll> ans;
string s;
ll n;

bool solve(ll pos, ll prv=-1){
    ll i=pos;
    while(i<n && s[i]=='_') i++;
    ll dash=i-pos;
    if(i==n){
        ll len=i-pos-prv;
        if(len>prv) return false;
        if(len>0) ans.pb(len);
        return true;
    }
    ll j=i;
    while(j<n && s[j]=='#') j++;
    ll hash=j-i;
    for(ll k=j; k<j+dash; k++){
        if(k>=n || s[k]=='#') return false;
    }
    if(j+dash<n && (s[j+dash]=='#' || j+dash==n-1))
        return false;
    ans.pb(j-pos);
    return solve(j+1,dash);
}

int main(){
 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll T=clock();
 
    cin>>s;
    n=s.size();
    bool ok=true;
    for(char c: s){
        if(c=='#')
            ok=false;
    }
    if(ok){
        cout<<0<<"\n";
        return 0;
    }
    if(!solve(0))
        cout<<-1;
    else{
        cout<<ans.size()<<"\n";
        for(ll u: ans)
            cout<<u<<" ";
    }





 
 
    cerr<<"\n\nTIME: "<<(double)(clock()-T)/CLOCKS_PER_SEC<<" sec\n";
    T = clock();
    return 0;
}