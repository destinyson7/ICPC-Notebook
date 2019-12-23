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
struct node{
    ll val;
    node *l, *r;
    node(){
        l=r=NULL;
    }
    node(node *left, node *right, ll v){
        l=left;
        r=right;
        val=v;
    }
};
struct psegtree{
    void build(vector<ll>&ar, node *root, ll l, ll r){
        if(l==r){
            root->val=ar[l];
            return;
        }
        ll b=(l+r)/2;
        root->l=new node(NULL, NULL, 0);
        root->r=new node(NULL, NULL, 0);
        build(ar,root->l, l, b);
        build(ar,root->r, b+1, r);
        root->val=root->l->val+root->r->val;
    }
    void upgrade(node *pre,node *cur,ll l,ll r,ll idx,ll val){
        if(l==r){
            cur->val=val;
            return;
        }
        ll b=(l+r)/2;
        if(idx<=b){
            cur->r = pre->r;
            cur->l = new node(NULL, NULL, 0);
            upgrade(pre->l,cur->l,l,b,idx,val);
        }
        else{
            cur->l=pre->l;
            cur->r=new node(NULL, NULL, 0);
            upgrade(pre->r,cur->r,b+1,r,idx,val);
        }
        cur->val=cur->l->val+cur->r->val;
    }
    ll get(node *root,ll l,ll r,ll st,ll en){
        if(l>r || en<l || st>r){
            return 0;
        }
        if(l>=st && r<=en){
            return root->val;
        }
        ll b=(l+r)/2;
        return get(root->l,l,b,st,en)+get(root->r,b+1,r,st,en);
    }
};