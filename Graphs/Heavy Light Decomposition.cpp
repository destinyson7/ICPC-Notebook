// QTREE SPOJ
struct node{
    ll depth,par,size,chain,posInBase;
};
#define ln 16
#define N 100001
ll n,chainNo,ptr;
vector<vector<pair<ll,pair<ll,ll>>>>ar(N);
node nd[N];
ll chainHead[N],otherEnd[N];
vector<ll> baseArray(N);
ll pa[N][ln];
struct segtree{
    struct node{
        ll sum;
    };
    vector<node> seg;
    segtree(){}
    segtree(ll n){
        seg.resize(4*n+4,{0});
    }
    segtree(ll n, vector<ll> &ar){
        seg.resize(4*n+4);
        build(ar, 1, 1, n);
    }
    node merge(node a, node b){
        node k;
        k.sum=max(a.sum,b.sum);
        return k;
    }
    // build segtree
    node get(ll pos,ll l,ll r,ll st,ll en){
        if(l>en || r<st || l>r){
            node k={-1};
            return k;
        }
        if(st<=l && en>=r){
            return seg[pos];
        }
        ll b=(l+r)/2;
        return merge(get(2*pos,l,b,st,en),get(2*pos+1,b+1,r,st,en));
    }
    // update segtree
};
ll query(segtree &obj,ll u,ll v){
    if(u==v) return 0;
    ll uchain,vchain=nd[v].chain,cost=0;
    while(1){
        uchain=nd[u].chain;
        if(uchain==vchain){
            if(u==v)return cost;
            return max(cost,obj.get(1,1,n-1,nd[v].posInBase+1,nd[u].posInBase).sum);
        }
        cost=max(cost,obj.get(1,1,n-1,nd[chainHead[uchain]].posInBase,nd[u].posInBase).sum); 
        u=nd[chainHead[uchain]].par;  
    }
}
ll lca(ll u,ll v){
    if(nd[u].depth < nd[v].depth) swap(u,v);
    ll log;
    for(log=1;(1<<log)<=nd[u].depth;log++);
    log--;
    for(ll i=log;i>=0;i--){
        if(nd[u].depth-(1<<i)>=nd[v].depth){
            u=pa[u][i];
        }
    }
    if(u==v) return v;
    for(ll i=log;i>=0;i--){
        if(pa[u][i]!=-1 && pa[u][i]!=pa[v][i])
            u=pa[u][i],v=pa[v][i];
    }
    return pa[u][0];
}
void hld(ll cur,ll cost,ll pre){
    if(chainHead[chainNo]==-1){
        chainHead[chainNo]=cur;
    }
    nd[cur].chain=chainNo;
    nd[cur].posInBase=ptr;
    baseArray[ptr++]=cost;

    ll sc=-1,ncost;
    for(auto i:ar[cur]){
        if(i.first==pre) continue;
        if(sc==-1 || nd[sc].size<nd[i.first].size){
            sc=i.first;
            ncost=i.second.first;
        }
    }
    if(sc!=-1){
        hld(sc,ncost,cur);
    }
    for(auto i:ar[cur]){
        if(i.first==pre) continue;
        if(sc!=i.first){
            chainNo++;
            hld(i.first,i.second.first,cur);
        }
    }
}
void dfs(ll x,ll p,ll d){
    nd[x].depth=d;
    nd[x].par=p;
    nd[x].size=1;
    for(auto i:ar[x]){
        if(i.first==p) continue;
        otherEnd[i.second.second]=i.first;
        dfs(i.first,x,d+1);
        nd[x].size+=nd[i.first].size;
    }
}
int main(){
    ll t; cin>>t;
    while(t--){
        cin>>n;
        chainNo=0,ptr=0;
        for(ll i=0;i<=n;i++){
            ar[i].clear();
            chainHead[i]=-1;
            for(ll j=0;j<ln;j++){
                pa[i][j]=-1;
            }
        }
        for(ll i=1,u,v,w;i<n;i++){
            cin>>u>>v>>w;
            ar[u].push_back(mk(v,mk(w,i)));
            ar[v].push_back(mk(u,mk(w,i)));
        }
        dfs(1,0,-1);
        hld(1,-1,-1);
        segtree obj(n-1,baseArray);
        for(ll i=1;i<=n;i++)
            pa[i][0]=nd[i].par;
        for(ll i=1;i<ln;i++)
            for(ll j=1;j<=n;j++)
                if(pa[j][i-1]!=-1)
                    pa[j][i]=pa[pa[j][i-1]][i-1];
        while(1){
            string s;
            cin>>s;
            if(s[0]=='D') break;
            ll a,b;
            cin>>a>>b;
            if(s[0]=='Q')
                cout << max(query(obj,a,lca(a,b)),query(obj,b,lca(a,b))) << "\n";
            else{
                obj.update(1,1,n-1,nd[otherEnd[a]].posInBase,b);
            }
        }
    }
}