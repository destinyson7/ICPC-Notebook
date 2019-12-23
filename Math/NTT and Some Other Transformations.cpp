#define INF 1e16
//Fast Walsh–Hadamard transform (XOR)
#define poly vector<ll>
poly FWHT(poly P, bool inverse) {
    for (len = 1; 2 * len <= degree(P); len <<= 1) {
        for (i = 0; i < degree(P); i += 2 * len) {
            for (j = 0; j < len; j++) {
                u = P[i + j];
                v = P[i + len + j];
                P[i + j] = u + v;
                P[i + len + j] = u - v;
            }
        }
    } 
    if (inverse) {
        for (i = 0; i < degree(P); i++)
            P[i] = P[i] / degree(P);
    }
    return P;
}
// & operator
poly transform(poly P, bool inverse) {
    for (len = 1; 2 * len <= degree(P); len <<= 1) {
        for (i = 0; i < degree(P); i += 2 * len) {
            for (j = 0; j < len; j++) {
                u = P[i + j];
                v = P[i + len + j];
                
                if (!inverse) {
                    P[i + j] = v;
                    P[i + len + j] = u + v;
                } else {
                    P[i + j] = -u + v;
                    P[i + len + j] = u;
                }
            }
        }
    } 
    return P;
}
// NTT
// 				k		g
// 5767169      19      3
// 7340033      20      3
// 23068673     21      3
// 104857601    22      3
// 167772161    25      3
// 469762049    26      3
// 998244353    23      3
// 1004535809   21      3
// 2013265921   27      31
// 2281701377   27      3
const ll mod = 998244353;
ll inverse(ll x, ll y){
	ll rem = 1;
	while(y != 0){
		if(y % 2 == 1){
			rem=(rem * x) % mod;
		}
		x=(x * x) % mod;
		y /= 2;
	}
	return rem;
}
const ll root = 3;
const ll root_1 = inverse(root, mod - 2);
const ll root_pw = 1 << 23;
void ntt(vector<ll> &a, bool invert){
	ll n = a.size();
	for(ll i = 1, j = 0; i < n; i++){
		ll bit = n >> 1;
		for(; j & bit; bit >>= 1)
			j ^= bit;
		j ^= bit;
		if(i < j)
			swap(a[i], a[j]);
	}

	for(ll len = 2; len <= n; len <<= 1){
		ll wlen = invert ? root_1 : root;
		for(ll i = len; i < root_pw; i <<= 1)
			wlen = wlen * wlen % mod;
		
		for(ll i = 0; i < n; i += len){
			ll w = 1;
			for(ll j = 0; j < len / 2; j++){
				ll u = a[i + j], v = a[i + j + len / 2] * w % mod;
				a[i + j] = u + v < mod ? u + v : u + v - mod;
				a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + mod;
				w = w * wlen % mod;
			}
		}
	}

	if(invert){
		ll n_1 = inverse(n, mod - 2);
		for(ll &x:a)
			x = x * n_1 % mod;
	}
}
vector<ll> multiply(vector<ll> const &a, vector<ll> const &b){
	vector<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	ll n = 1;
	while(n < a.size() + b.size())
		n <<= 1;
	fa.resize(n, 0);
	fb.resize(n, 0);
	ntt(fa, false);
	ntt(fb, false);
	for(ll i = 0; i < n; i++)
		fa[i] = fa[i] * fb[i] % mod;
	ntt(fa, true);
	return fa;
}
int main(){
    ll t; cin>>t;
    while(t--){
        ll n;
        cin>>n;
        vector<ll>a(n+1), b(n+1);
        for(ll i=0;i<=n;i++){
            cin>>a[n-i];
        }
        for(ll i=0;i<=n;i++){
            cin>>b[n-i];
        }
        auto c = multiply(a, b);
        for(ll i=2*n;i>=0;i--){
            cout << c[i] << " ";
        }
        cout << "\n";
    }
}