#include<bits/stdc++.h>
using namespace std;
#define ll long long int


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

    string c,t;
    cin>>c>>t;

    ll l=t.length();
    vector<ll>p(l);
    p[0]=0;
    for(ll i = 1, j = 0; i < l; i++){
        while(j > 0 && t[i] != t[j]){
            j = p[j-1];
        }
        if(t[i] == t[j])
            j++;
        p[i] = j;
    }

    ll n = c.length(), ans=0;
    for(ll i = 0,j = 0; i < n; i++){
        if(c[i] == t[j]){
            if(j == l-1){
                ans++;
                j = p[j];
                continue;
            }
            j++;
        }
        else if(j > 0){
            j = p[j-1];
            i--;
        }
    }
}