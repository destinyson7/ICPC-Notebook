ll N = 1000; 
void SumOverSubsets(ll a[], ll n) { 
	ll sos[1 << n] = {0}; 	
	ll dp[N][N];  
	for (ll x = 0; x < (1 << n); x++) { 
		for (ll i = 0; i < n; i++) { 
			if (x & (1 << i)) { 
				if (i == 0) 
					dp[x][i] = a[x] + a[x ^ (1 << i)]; 
				else // dp recurrence 
					dp[x][i] = dp[x][i - 1] + 
								dp[x ^ (1 << i)][i - 1]; 
			} 
			else{ // i-th bit is not set 
				if (i == 0) 
					dp[x][i] = a[x]; // base condition 
				else
					dp[x][i] = dp[x][i - 1]; // dp recurrence 
			} 
		} 
		sos[x] = dp[x][n - 1]; 
	} 
	for (ll i = 0; i < (1 << n); i++) 
		cout << sos[i] << " "; 
} 
int main(){ 
	ll n; cin>> n;
	ll a[n];
	for (int i = 0; i < n; ++i){
	 	cin >> a[i];
	} 
	SumOverSubsets(a, (ll)log2(n));	 
	return 0; 
} 
