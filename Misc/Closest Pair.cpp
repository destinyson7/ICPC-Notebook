const ll N=1e5+5,inf=1e18;
pll pnts [N];
int compare(pll a, pll b){ 
        return a.px<b.px; 
}
double closest_pair(int n){
    sort(pnts,pnts+n,compare);
    double best=inf;
    set<pll> box;
    box.insert(pnts[0]);
    int left = 0;
    for (int i=1;i<n;++i){
        while (left<i && pnts[i].px-pnts[left].px > best)
            box.erase(pnts[left++]);
        ll cnt=0;
        cout<<pnts[i].px<<" "<<pnts[i].py<<endl;
        for(auto it=box.lower_bound(make_pair(pnts[i].py-best, pnts[i].px-best));it!=box.end() && pnts[i].py+best>=it->py;it++){
        	cnt++;
            best = min(best, sqrt(pow(pnts[i].py - it->py, 2.0)+pow(pnts[i].px - it->px, 2.0)));
        }
        box.insert(pnts[i]);
    }
    return best;
}
int main(){
	ll n;
	cin >> n;
	lp(i,0,n){
		ll a,b;
		cin >> a >> b;
		pnts[i].px=a;
		pnts[i].py=b;
	}	 
	cout<<closest_pair(n)<<endl;   
}