#include<bits/stdc++.h>
#define ll long long int
using namespace std;

struct node{
	ll w,u,v;
};
struct parent{
	ll pa,rk;
};
bool compare(const node &a, const node &b){
	return a.w <= b.w;
}
ll find(auto &ar, ll x){
	if(ar[x].pa!=x){
		ar[x].pa=find(ar,ar[x].pa);
	}
	return ar[x].pa;
}
void unio(auto &ar, ll x , ll y){
	if(ar[x].rk < ar[y].rk){
		ar[x].pa=y;
		return;
	}
	if(ar[x].rk > ar[y].rk){
		ar[y].pa=x;
		return;
	}
	ar[x].pa=y;
	ar[y].rk++;
	return;
}

	int main(){
		ll n,m;
		cin >> n >> m;
		vector<node >ar(m);
		for(ll i=0;i<m;i++){
			cin >> ar[i].u >> ar[i].v >> ar[i].w;
		}
		sort(ar.begin(),ar.end(),compare);
		ll sum=0;
		vector<parent >par(n+1);
		for(ll i=1;i<=n;i++){
			par[i].pa=i;
			par[i].rk=0;
		}
		for(ll i=0,j=0;i<m;i++){
			ll x=find(par, ar[i].u);
			ll y=find(par, ar[i].v);
			if(x!=y){
				sum+=ar[i].w;
				unio(par,x,y);
				j++;
			}
			if(j == n-1){
				break;
			}
		}
		cout << sum << "\n";
		return 0;
	}