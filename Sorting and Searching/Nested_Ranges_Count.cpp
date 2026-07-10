#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define syncing           ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define ordered_set    tree<pair<ll, ll>, null_type,less<pair<ll, ll>>, rb_tree_tag,tree_order_statistics_node_update>
#define ll             long long
#define nn             cout<<"\n"
#define nl             "\n"
#define rr             return

#define i1(n)          ll n;cin>>n
#define i2(n, m)       ll n,m;cin>>n>>m
#define i3(n, m, k)    ll n,m,k;cin>>n>>m>>k
#define sot(v)         sort(v.begin(), v.end())
#define rsot(v)        sort(v.rbegin(), v.rend())
#define vll            vector<ll>
#define vin(n, v)      vector<ll>v(n);for(ll i=0;i<n;i++)cin>>v[i]
#define uniqs(v)        v.resize(unique(v.begin(),v.end())-v.begin());


ll gcd(ll a, ll b){while(a!=0 && b!=0){if(a>b) a = a%b;else b = b%a;}return a==0?b:a;}
ll lcm(ll a, ll b) {return (ll)a*b/gcd(a, b);}
void siev(ll n, vector<bool> &v){for(ll i=2;i*i<=n;i++){if(v[i]){for(ll j=i*i;j<=n;j+=i) v[j] = false;}}}
bool isps(ll x){ll sr=sqrtl(x);return x>=0&&(sr*sr==x);}
bool ckprime(ll a){ if (a != 2 && a % 2 == 0 || a < 2) return 0;  for(ll i = 3; i * i <= a; i += 2) if(a % i == 0) return 0; return 1;}
ll power(ll n,ll a){ ll res=1; while(a){ if(a%2) res*=n,a--; else   n*=n,a/=2;} return res;}
ll powerm(ll n, ll a, ll mod) { ll res = 1; for(n %= mod; a; n = n * n % mod, a /= 2) if(a & 1) res = res * n % mod; return res; }
const ll MODE = 1e9+7;
const ll LIM = 2*1e5+1;


vll f(LIM);
vll fi(LIM);

void calf(){
    f[0] = 1, f[1] = 1;
    fi[0] = 1, fi[1] = 1;
    for(ll i=2;i<LIM;i++){
        f[i] = (f[i-1]*i)%MODE;
        fi[i] = powerm(f[i], MODE-2, MODE);
    }
}

ll nCr(ll n, ll r){
    return (((f[n]*fi[r])%MODE)*(fi[n-r]%MODE))%MODE;
}

    
void solve() {
    i1(n);
    vector<vll> v(n, vll(3));
    for(ll i=0;i<n;i++){
        cin >> v[i][0] >> v[i][1];
        v[i][2] = i;
    }
    sort(v.begin(), v.end(), [&](vll &a, vll &b){
        if(a[0]!=b[0]) return a[0]<b[0];
        return a[1]>b[1];
    });
 
    ordered_set st;
    st.insert({v[0][1], 1});
    ll curr = 2;
    vll ans1(n);
    vll ans2(n);
    for(ll i=1;i<n;i++){
        st.insert({v[i][1], curr++});
        ll ind = st.order_of_key({v[i][1], INT_MIN});
        ll si = st.size();
        ans2[v[i][2]] = si-ind-1;
    }
    
    ordered_set st2;
    st2.insert({v[n-1][1], 1});
    curr = 2;
    for(ll i=n-2;i>=0;i--){
        st2.insert({v[i][1], curr++});
        ll ind = st2.order_of_key({v[i][1], curr-1});
        ans1[v[i][2]] = ind;
    }
    for(auto &it: ans1) cout << it << " ";
    nn;
    for(auto &it: ans2) cout << it << " ";
 
}


int main() {
    syncing;
    ll t=1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
