// SPOJ GSS3 // 1-based indexing
typedef struct node{
    ll ans, pref, suff, sum;
} node;
ll a[L];
node seg[4*L];
node merge(node a, node b){
    node x;
    x.ans = max(a.suff + b.pref, max(a.ans, b.ans));
    x.pref = max(a.pref, a.sum + b.pref);
    x.suff = max(b.suff, a.suff + b.sum);
    x.sum = a.sum + b.sum;
    return x;
}
void build(ll pos, ll tl, ll tr){
    if(tl == tr){
        seg[pos].ans = a[tl];
        seg[pos].pref = a[tl];
        seg[pos].suff = a[tl];
        seg[pos].sum = a[tl];
        return;
    }
    ll mid = tl + (tr-tl)/2;
    build(2*pos, tl, mid);
    build(2*pos+1, mid+1, tr);
    seg[pos] = merge(seg[2*pos], seg[2*pos+1]);
}
void update(ll pos, ll tl, ll tr, ll idx, ll val){
    if(tl == tr){
        seg[pos].sum = val;
        seg[pos].ans = val;
        seg[pos].pref = val;
        seg[pos].suff = val;
        return;
    }
    ll mid = tl + (tr - tl)/2;
    if(tl <= idx && idx <= mid){
        update(2*pos, tl, mid, idx, val);
    }
    else{
        update(2*pos+1, mid+1, tr, idx, val);
    }
    seg[pos] = merge(seg[2*pos], seg[2*pos+1]);
}
node query(ll pos, ll tl, ll tr, ll l, ll r){
    if(tl > r || tr < l){
        node x;
        x.sum = 0;
        x.ans = -1e15;
        x.pref = -1e15;
        x.suff = -1e15;
        return x;
    }
    if(tl >= l && tr <= r){
        return seg[pos];
    }
    ll mid = tl + (tr-tl)/2;
    return merge(query(2*pos, tl, mid, l, r), query(2*pos+1, mid+1, tr, l, r));
}
