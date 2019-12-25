ll N = 1000;//small n is log2(number of elements in a)
void SumOverSubsets(ll a[], ll n){ 
	ll sos[1 << n]={0}; 	
	ll dp[N][N];  
	for(ll x=0; x<(1LL<<n); x++){ 
		for(ll i=0; i<n; i++){ 
			if(x & (1 << i)){ 
				if(i==0) 
				dp[x][i]=a[x]+a[x^(1<<i)]; 
				else 
				dp[x][i]=dp[x][i-1]+dp[x^(1<<i)][i-1]; 
			} 
			else{ // i-th bit is not set 
				if (i == 0) 
					dp[x][i] = a[x]; 
				else
					dp[x][i] = dp[x][i-1]; 
			} 
		} 
		sos[x] = dp[x][n - 1]; 
	} 
	for (ll i = 0; i < (1 << n); i++) 
		cout << sos[i] << " "; 
}