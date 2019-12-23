// https://github.com/kth-competitive-programming/kactl/commit/165807e28402c9be906f6e6a09452431787bb70d

#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define pb push_back
#define mk make_pair
#define ve vector
#define pi pair<ll,ll>
#define fi first
#define se second

struct Line {
    ll k, m;
    mutable ll p;
    bool operator<(const Line& o) const {
        return k < o.k;
    }
    bool operator<(const ll &x) const{
        return p < x;
    }
};
struct LineContainer : multiset<Line, less<>> {
    const ll inf = LLONG_MAX;
    ll div(ll a, ll b){
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(iterator x, iterator y) {
        if (y == end()) { x->p = inf; return false; }
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};


ll a[100001];
ll b[100001];
ve<ve<ll>>ar(100001);
ll sub[100001];
ll ans[100001];

void dfs1(ll u,ll p){
    sub[u]=1;
    for(auto i:ar[u]){
        if(i!=p){
            dfs1(i,u);
            sub[u]+=sub[i];
        }
    }
}

void dfs2(ll u,ll p,auto &cur){
    ll mx=-1,chd=-1,leaf=1;
    for(auto i:ar[u]){
        if(i!=p && sub[i]>mx){
            mx=sub[i];
            chd=i;
            leaf=0;
        }
    }
    if(chd!=-1){
        dfs2(chd,u,cur);
    }
    for(auto i:ar[u]){
        if(i!=p && i!=chd){
            LineContainer temp;
            dfs2(i,u,temp);
            for(auto j:temp){
                cur.add(j.k,j.m);
            }
        }
    }
    if(!leaf){
        ans[u]=-cur.query(a[u]);
    }
    else{
        ans[u]=0;
    }
    cur.add(-b[u],-ans[u]);
}

    int main(){
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);
        ll n;
        cin>>n;
        for(ll i=1;i<=n;i++){
            cin>>a[i];
        }
        for(ll i=1;i<=n;i++){
            cin>>b[i];
        }
        for(ll i=1,u,v;i<n;i++){
            cin>>u>>v;
            ar[u].pb(v);
            ar[v].pb(u);
        }
        dfs1(1,0);
        LineContainer lc;
        dfs2(1,0,lc);
        for(ll i=1;i<=n;i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
        return 0;
    }