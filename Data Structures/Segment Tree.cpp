// SPOJ GSS3 // 1-based indexing
typedef struct node{
    ll ans, pref, suff, sum;
} node;
ll a[L];
node seg[4*L];
node merge(node a, node b){
    node x;
    // Merge Function
    return x;
}
void build(ll pos, ll tl, ll tr){
    if(tl == tr){
        seg[pos] = a[tl]; // Leaf Node
        return;
    }
    ll mid = tl + (tr-tl)/2;
    build(2*pos, tl, mid);
    build(2*pos+1, mid+1, tr);
    seg[pos] = merge(seg[2*pos], seg[2*pos+1]);
}
void update(ll pos, ll tl, ll tr, ll idx, ll val){
    if(tl == tr){
        seg[pos] = val; // Assign updated Value
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