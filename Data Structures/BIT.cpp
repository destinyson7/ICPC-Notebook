// 1-based indexing
/* Problem Statement:
Given a sequence of n numbers a1, a2,..., an and a number of k-queries.
A k-query is a triple (i, j, k) (1<=i<=j<=n). For each k-query
(i, j, k), you have to return the number of elements greater than k in
the subsequence ai, ai+1, ..., aj. */
struct M{
   	ll key, key2, key3, key4;
};
bool cmp(struct M a, struct M b){
	if(a.key==b.key) return b.key4<=a.key4;
  	return (a.key >  b.key);
}
bool cmp2(struct M a,struct M b){
	return a.key4<b.key4;
}
ll bit[30002];
ll update(ll idx,ll n){
	while(idx<=n){
		bit[idx]+=1;
		idx=idx+(idx&(-idx));
	}
}
ll query(ll idx){
	ll sum=0;
	while(idx>0){
		sum+=bit[idx];
		idx=idx-(idx&(-idx));
	}
	return sum;
}
struct M Ssp[230000];
int main(){
	ll n;cin >> n; ll q;
	for (int i = 0; i < n; ++i){
		ll a; cin >> a;
		Ssp[i].key=a;
		Ssp[i].key2=Ssp[i].key3=0;
		Ssp[i].key4=i;
	}
	cin >> q;
	for (int i = 0; i < q; ++i){
		ll l,r,k; cin>>l>>r>>k;
		Ssp[i+n].key=k;
		Ssp[i+n].key2=l;
		Ssp[i+n].key3=r;
		Ssp[i+n].key4=i+n;
	}
	sort(Ssp, Ssp+n+q, cmp);
	for (int i = 0; i < n+q; ++i){
		if(!Ssp[i].key2)
		update(Ssp[i].key4+1,n);
		else
		Ssp[i].key=query(Ssp[i].key3)-query(Ssp[i].key2-1);
	}
	sort(Ssp, Ssp+n+q, cmp2);
	for (int i = 0; i < n+q; ++i){
		if(Ssp[i].key2)
			printf("%lld\n",Ssp[i].key);
	}
}