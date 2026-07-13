#include<bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
//using namespace __gnu_pbds;

#define syncing           ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define ordered_set    tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>
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

void update(ll ind, ll l, ll r, vll &seg, ll index, ll val) {
    if(l == r) {
        seg[ind] = val;
        return;
    }
    ll mid = (l+r)/2;
    if(index<=mid) update(2*ind+1, l, mid, seg, index, val);
    else update(2*ind+2, mid+1, r, seg, index, val);
    seg[ind] = max(seg[2*ind+1], seg[2*ind+2]);
}

ll query(ll ind, ll l, ll r, ll ql, ll qr, vll &seg) {
    if(ql<=l && r<=qr) return seg[ind];
    if(ql>r || qr<l) return 0LL;
    ll mid = (l+r)/2;
    ll left = query(2*ind+1, l, mid, ql, qr, seg);
    ll right = query(2*ind+2, mid+1, r, ql, qr, seg);
    return max(left, right);
}

    
void solve() {
    i1(n);
    vector<pair<ll, ll>> v(n);
    for(ll i=0;i<n;i++){
        cin >> v[i].first;
        v[i].second = i;
    }
    stack<ll> st;
    vll left(n, -1);
    vll right(n, n);
    for(ll i=0;i<n;i++){
        while(st.size() && v[st.top()].first < v[i].first) st.pop();
        if(st.size()) left[i] = st.top();
        st.push(i);
    }
    while(st.size()) st.pop();
    for(ll i=n-1;i>=0;i--){
        while(st.size() && v[st.top()].first < v[i].first) st.pop();
        if(st.size()) right[i] = st.top();
        st.push(i);
    }
    vll seg(4*n);
    ll ans = 0;
    sort(v.begin(), v.end());
    for(ll i=0;i<n;i++){
        ll l = 0, r = 0;
        ll ind = v[i].second;
        if(left[ind]+1 <= ind-1) l = query(0, 0, n-1, left[ind]+1, ind-1, seg);
        if(ind+1 <= right[ind]-1) r = query(0, 0, n-1, ind+1, right[ind]-1, seg);
        ll val = max(l, r)+1;
        ans = max(ans, val);
        update(0, 0, n-1, seg, ind, val);
    }
    cout << ans;
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
