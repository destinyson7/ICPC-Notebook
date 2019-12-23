#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define ld unsigned long long int
#define pi pair<ll,ll>
#define pb push_back
#define pf push_front
#define pu push
#define po pop
#define fi first
#define se second
#define mk make_pair
#define ve vector
#define lr(n) for(ll i=0;i<n;i++)
#define all(x) x.begin(),x.end()
#define be begin

ll mod = 998244353;
ll modularExp(ll x, ll y){
	ll rem = 1;
	while(y != 0){
		if(y % 2 == 1){
			rem = (rem * x) % mod;
		}
		x = (x * x) % mod;
		y /= 2;
	}
	return rem;
}

// ---------------------------------- Determinant (Source: geeksforgeeks)--------------------------------

#define N 30
ll determinant(ll ar[][N], ll n){
	ll n1,n2,d=1,ind,total=1;

	ll arr[n+1];

	for(ll i = 0; i < n; i++){
		ind=i;
		while(ar[ind][i] == 0 && ind < n){
			ind++;
		}
		if(ind == n){
			continue;
		}
		if(ind != i){
			for(ll j = 0; j < n; j++){
				swap(ar[ind][j], ar[i][j]);
			}
			d = d * pow(-1, ind - 1);
		}
		for(ll j = 0; j < n; j++){
			arr[j] = ar[i][j];
		}
		for(ll j = i + 1; j < n; j++){
			n1 = arr[i];
			n2 = ar[j][i];
			for(ll k = 0; k < n; k++){
				ar[j][k] = ((n1 * ar[j][k]) - (n2 * arr[k])) % mod;
				if(ar[j][k] < 0)
					ar[j][k] += mod;
			}
			total = (total * n1) % mod;
		}
	}
	for(ll i = 0; i < n; i++){
		d = (d * ar[i][i]) % mod;
	}
	return d * modularExp(total, mod - 2) % mod;
}





	int main(){
		ios_base::sync_with_stdio(0);
		cin.tie(0);
		cout.tie(0);
		ll t;
		cin>>t;
		while(t--){
			ll n,m,k;
			cin>>n>>m>>k;
			ll ar[30][30];
			ll deg[n]={0};
			for(ll i=0;i<30;i++){
				for(ll j=0;j<30;j++){
					ar[i][j]=0;
				}
			}
			for(ll i=0,u,v;i<m;i++){
				cin>>u>>v;
				u--,v--;
				deg[u]+=1;deg[v]+=1;
				ar[u][v]-=1;
				ar[v][u]-=1;
			}
			for(ll i=0;i<n;i++)
				ar[i][i]=deg[i]-k*n;
			for(ll i=0;i<n;i++){
				for(ll j=0;j<n;j++){
					ar[i][j]=(-ar[i][j])%mod;
					if(ar[i][j]<0)
						ar[i][j]+=mod;
				}
			}
			ll ans = modularExp(determinant(ar,n),k)*modularExp(k*n%mod,mod-3)%mod;
			cout << ans << "\n";
		}
		return 0;
	}