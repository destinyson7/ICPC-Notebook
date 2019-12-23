// SPOJ CNTPRIME // 1-based indexing
ll a[L]; ll seg[4*L]; ll lazy[4*L];
ll merge(ll a, ll b){
    return (a+b);
}
void build(ll pos, ll tl, ll tr){
    if(tl == tr){
        if(isPrime[a[tl]])
            seg[pos] = 1;
        return;
    }
    ll mid = tl + (tr-tl)/2;
    build(2*pos, tl, mid);
    build(2*pos+1, mid+1, tr);
    seg[pos] = merge(seg[2*pos], seg[2*pos+1]);
}
void update(ll pos, ll tl, ll tr, ll l, ll r, ll val){
    if(lazy[pos] != 0){
        if(isPrime[lazy[pos]])
            seg[pos] = tr-tl+1;
        else
            seg[pos] = 0;
        if(tl != tr){
            lazy[2*pos] = lazy[pos];
            lazy[2*pos+1] = lazy[pos];
        }
        lazy[pos] = 0;
    }
    if(tl > r || tr < l)
        return;
    if(tl >= l && tr <= r){
        if(isPrime[val])
            seg[pos] = tr-tl+1;
        else
            seg[pos] = 0;
        if(tl != tr){
            lazy[2*pos] = val;
            lazy[2*pos+1] = val;
        }
        lazy[pos] = 0;
        return;
    }
    ll mid = tl + (tr-tl)/2;
    update(2*pos, tl, mid, l, r, val);
    update(2*pos+1, mid+1, tr, l, r, val);
    seg[pos] = merge(seg[2*pos], seg[2*pos+1]);
}
ll query(ll pos, ll tl, ll tr, ll l, ll r){
    if(lazy[pos] != 0)
        // same as update
    if(l > tr || r < tl)
        return 0;
    if(tl >= l && tr <= r)
        return seg[pos];
    ll mid = tl + (tr-tl)/2;
    return merge(query(2*pos, tl, mid, l, r), query(2*pos+1, mid+1, tr, l, r));
}