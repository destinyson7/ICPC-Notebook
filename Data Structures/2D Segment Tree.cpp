struct D2segtree{
    vector<segtree> seg;
    D2segtree(ll n, ll m, vector<vector<ll>> &ar){
        seg.resize(4*n+4);
        for(ll i=0; i<4*n+4; i++){
            seg[i].seg.resize(4*m+4);
        }
        vector<segtree>temp(n+1);
        for(ll i=1;i<=n;i++){
            temp[i].seg.resize(4*m+4);
            temp[i].build(ar[i], 1, 1, m);
        }
        build(temp, 1, 1, n, m);
    }
    segtree merge(ll m, segtree a, segtree b){
        segtree k(m);
        for(ll i=0; i<4*m+4; i++)
            k.seg[i].sum=a.seg[i].sum+b.seg[i].sum;
        return k;
    }
    void build(vector<segtree> &ar,ll pos,ll l,ll r,ll m){
        if(l==r){
            seg[pos]=ar[l];
            return;
        }
        ll b=(l+r)/2;
        build(ar,2*pos,l,b,m);
        build(ar,2*pos+1,b+1,r,m);
        seg[pos]=merge(m,seg[2*pos],seg[2*pos+1]);
        return;
    }
    ll query(ll n,ll m,ll x1,ll y1,ll x2,ll y2){
        return get(1, 1, n, m, y1, y2).get(1, 1, m, x1, x2).sum;
    }
    segtree get(ll pos,ll l,ll r,ll m,ll st,ll en){
        if(l>en || r<st || l>r){
            segtree k(m);
            return k;
        }
        if(st<=l && en>=r){
            return seg[pos];
        }
        ll b=(l+r)/2;
        return merge(m,get(2*pos,l,b,m,st,en),get(2*pos+1,b+1,r,m,st,en));
    }
    void update(ll pos,ll l,ll r,ll m,ll x,ll y,ll val){
        if(l==r){
            seg[pos].update(1,1,m,x,val);
            return;
        }
        ll b=(l+r)/2;
        if(y<=b){
            update(2*pos,l,b,m,x,y,val);
        }
        else{
            update(2*pos+1,b+1,r,m,x,y,val);
        }
        seg[pos]=merge(m,seg[2*pos],seg[2*pos+1]);
        return;
    }
};