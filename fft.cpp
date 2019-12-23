#include <bits/stdc++.h>
using namespace std;
#define ll long long int

typedef complex<double> cd;
const double PI = acos(-1);
void fft(vector<cd> &a, bool invert){
    ll n=a.size();
    for(ll i=1,j=0; i<n; i++){
        ll bit=n>>1;
        for(; j&bit; bit>>=1)
            j ^= bit;
        j ^= bit;
        if(i < j)
            swap(a[i], a[j]);
    }

    for(ll len=2; len<=n; len <<= 1){
        double ang=2*PI/len*(invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for(ll i=0; i<n; i+=len){
            cd w(1);
            for(ll j=0; j<len/2; j++){
                cd u = a[i+j], v = a[i+j+len/2]*w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w *= wlen;
            }
        }
    }

    if(invert){
        for(cd & x : a)
            x /= n;
    }
}

vector<ll> multiply(vector<ll> const &a, vector<ll> const &b){
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    ll n=1;
    while(n < a.size()+b.size())
        n <<= 1;
    fa.resize(n,0);
    fb.resize(n,0);

    fft(fa, false);
    fft(fb, false);
    for(ll i=0; i<n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<ll> result(n);
    for(ll i=0; i<n; i++)
        result[i] = llround(fa[i].real());
    return result;
}

    int main(){
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);
        ll t;
        cin>>t;
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