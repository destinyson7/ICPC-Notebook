ll MAX=1e6;
struct wavelet_tree{
	ll lo,hi;
	wavelet_tree *l,*r;
	vector<ll>b;
	wavelet_tree(ll *from,ll *to,ll x,ll y){
		lo = x,hi = y;
		if(lo == hi || from >= to)return;
		ll mid = (lo+hi)/2;
		auto f = [mid](ll x){
			return x <= mid;
		};
		b.reserve(to-from+1);
		b.push_back(0);
		for(auto it = from; it!=to; it++)
			b.push_back(b.back() + f(*it));

		auto pivot = stable_partition(from, to, f);
		l = new wavelet_tree(from, pivot, lo, mid);
		r = new wavelet_tree(pivot, to, mid + 1, hi);
	}
	// kth smallest element in [l, r]
	ll kth(ll le,ll ri,ll k){
		if(le > ri) return 0;
		if(lo == hi) return lo;
		ll inLeft = b[ri] - b[le-1];
		ll lb = b[le-1]; //amt of nos in first (l-1) nos that go in left 
		ll rb = b[ri]; //amt of nos in first (r) nos that go in left
		if(k <= inLeft) return this->l->kth(lb+1, rb , k);
		return this->r->kth(le-lb, ri-rb, k-inLeft);
	}
	// count of nos in [l, r] less than or equal to k
	ll LTE(ll le,ll ri,ll k){
		if(le>ri || k < this->lo) return 0;
		if(this->hi <= k) return ri-le+1;
		ll lb = b[le-1],rb = b[ri];
		return this->l->LTE(lb+1,rb,k) + this->r->LTE(le-lb,ri-rb,k);
	}
	//count of nos in [l, r] equal to k
	int count(ll le,ll ri,ll k) {
		if(le > ri or k < lo or k > hi) return 0;
		if(lo == hi) return ri - le + 1;
		int lb = b[le-1], rb = b[ri], mid = (lo+hi)/2;
		if(k <= mid) return this->l->count(lb+1, rb, k);
		return this->r->count(le-lb, ri-rb, k);
	}
};
int main(){
	ll n; cin>>n;
	ll ar[n+1];
	wavelet_tree obj(ar+1,ar+n+1,1,MAX);
}