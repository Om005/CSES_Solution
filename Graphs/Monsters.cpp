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

    
void solve() {
    i2(n, m);
    vector<string> v(n);
    for(ll i=0;i<n;i++) cin >> v[i];
    vector<vector<ll>> dis(n, vll(m, LLONG_MAX));
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    queue<vll> q;
    pair<ll, ll> st;
    for(ll i=0;i<n;i++){
        for(ll j=0;j<m;j++){
            if(v[i][j]=='M') {
                q.push({i, j, 0});
                vis[i][j] = true;
            }
            else if(v[i][j]=='A') st = {i, j};
        }
    }
    vll dir = {1, 0, -1, 0, 1};
    vll move = {'D', 'L', 'U', 'R'};
    auto check = [&](ll l, ll r) -> bool {
        return (l<n && r<m && l>=0 && r>=0 && v[l][r]!='#' && !vis[l][r]);
    };
    while(q.size()){
        ll si = q.size();
        for(ll i=0;i<si;i++){
            vll monster = q.front();
            q.pop();
            ll x = monster[0], y = monster[1], curr = monster[2];
            dis[x][y] = min(dis[x][y], curr);
            for(ll k=0;k<4;k++){
                ll newx = x+dir[k], newy = y+dir[k+1];
                if(check(newx, newy)){
                    q.push({newx, newy, curr+1});
                    vis[newx][newy] = true;
                }
            }
        }
    }
    fill(vis.begin(), vis.end(), vector<bool>(m, false));
    vector<vector<pair<ll, ll>>> parent(n, vector<pair<ll, ll>>(m, {-1, -1}));
    q.push({st.first, st.second, 0});
    vis[st.first][st.second] = true;
    pair<ll, ll> en = {-1, -1};
    while(q.size()) {
        ll si = q.size();
        for(ll i=0;i<si;i++){
            vll tm = q.front();
            q.pop();
            ll x = tm[0], y = tm[1], curr = tm[2];
            if(x==0 || y==0 || x==n-1 || y==m-1) {
                en = {x, y};
                break;
            }
            for(ll k=0;k<4;k++){
                ll newx = x+dir[k], newy = y+dir[k+1];
                if(check(newx, newy) && curr+1<dis[newx][newy]){
                    q.push({newx, newy, curr+1});
                    parent[newx][newy] = {x, y};
                    vis[newx][newy] = true;
                }
            }
        }
        if(en.first != -1) break;
    }
    map<pair<ll, ll>, char> mv;
    mv[{1, 0}] = 'D';
    mv[{0, -1}] = 'L';
    mv[{-1, 0}] = 'U';
    mv[{0, 1}] = 'R';
 
    if(en.first==-1) cout << "NO";
    else{
        cout << "YES\n";
        string ans = "";
        while(en.first!=-1){
            auto pt = parent[en.first][en.second];
            if(pt.first==-1) break;
            ans.push_back(mv[{en.first-pt.first, en.second-pt.second}]);
            en = pt;
        }
        cout << ans.size() << nl;
        reverse(ans.begin(), ans.end());
        cout << ans;
    }
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
