// E. Xenia and Tree, Codeforces
#define ln 20
#define N 100001
#define INF 1e9
ll n; vector<vector<ll>>ar(N);
ll lev[N]; ll pa[N][ln];
ll centroidMarked[N]={0};
ll sub[N]; ll par[N]; ll ans[N];
// dist(u,v)
void dfs(ll u,ll p,ll l){
    pa[u][0]=p;
    lev[u]=l;
    for(auto i:ar[u]){
        if(i!=p)
            dfs(i,u,l+1);
    }
}
ll lca(ll u,ll v){
    if(lev[u]<lev[v]) swap(u,v); 
    ll log;
    for(log=1;(1<<log)<=lev[u];log++);
    log--;
    for(ll i=log;i>=0;i--){
        if(lev[u]-(1<<i)>=lev[v])
            u=pa[u][i];
    }
    if(u==v) return u;
    for(ll i=log;i>=0;i--){
        if(pa[u][i]!=-1 && pa[u][i]!=pa[v][i])
            u=pa[u][i],v=pa[v][i];
    }
    return pa[u][0];
}
ll dist(ll u,ll v){
    return lev[u]+lev[v]-2*lev[lca(u,v)];
}
// decompose
ll nn;
void dfs1(ll u,ll p){
    nn++;
    sub[u]=1;
    for(auto i:ar[u]){
        if(i!=p && !centroidMarked[i]){
            dfs1(i,u);
            sub[u]+=sub[i];
        }
    }
}
ll dfs2(ll u,ll p){
    for(auto i:ar[u]){
        if(i!=p && !centroidMarked[i] && sub[i]>nn/2)
            return dfs2(i,u);
    }
    return u;
}
void decompose(ll u,ll p){
    nn=0;
    dfs1(u,p);
    ll centroid=dfs2(u,p);
    centroidMarked[centroid]=1;
    par[centroid]=p;
    for(auto i:ar[centroid]){
        if(!centroidMarked[i]){
            decompose(i,centroid);
        }
    }
}
// query
void update(ll u){
    ll x=u;
    while(x!=-1){
        ans[x]=min(ans[x],dist(u,x));
        x=par[x];
    }
}
ll query(ll u){
    ll x=u;
    ll an=INF;
    while(x!=-1){
        an=min(an,ans[x]+dist(u,x));
        x=par[x];
    }
    return an;
}
int main(){
    ll m;
    cin>>n>>m;
    for(ll i=1,u,v;i<n;i++){
        cin>>u>>v;
        ar[u].pb(v);
        ar[v].pb(u);
    }
    for(ll i=0;i<=n;i++){
        for(ll j=0;j<ln;j++)
            pa[i][j]=-1;
    }
    dfs(1,-1,0);
    for(ll i=1;i<ln;i++){
        for(ll j=1;j<=n;j++)
            if(pa[j][i-1]!=-1)
                pa[j][i]=pa[pa[j][i-1]][i-1];
    }
    decompose(1,-1);
    for(ll i=0;i<=n;i++){
        ans[i]=INF;
    }
    update(1);
    while(m--){
        ll t,v;
        cin>>t;
        if(t==2){
            cin>>v;
            cout << query(v) << "\n";
        }
        else{
            cin>>v;
            update(v);
        }
    }
}