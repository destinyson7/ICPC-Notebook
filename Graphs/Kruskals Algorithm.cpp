ll find(ll s){
    if(parent[s]==s){
        return s;
    }
    return parent[s]=find(parent[s]);
}
void unionSet(ll x, ll y){
    ll a = find(x);
    ll b = find(y);
    if(unionSize[a] > unionSize[b]){
        swap(x, y);
    }
    parent[a] = b;
    unionSize[b] += unionSize[a];
}
ll kruskals(ll M){
    ll ans = 0;
    for(ll i=0; i<M; i++){
        ll u = weights[i].ss.ff;
        ll v = weights[i].ss.ss;
        ll w = weights[i].ff;

        if(find(u)!=find(v))
        {
            ans+=w;
            unionSet(u, v);
        }
    }
    return ans;
}
int main(){
    ll N, M;
    cin >> N >> M;
    for(ll i=0; i<L; i++)
    {
        parent[i] = i;
        unionSize[i] = 1;
    }
    for(ll i=0; i<M; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;

        adj[u].pb(mp(v, w));
        adj[v].pb(mp(u, w));

        weights.pb(mp(w, mp(u, v)));
    }
    sort(weights.begin(), weights.end());
    cout << kruskals(M) << endl;
}