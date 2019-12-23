ll x, y;
ll extendedeuc(ll a, ll b){
	if (b==0){
		x=1;
		y=0;
	}
	else{
		extendedeuc(b, a%b);
		ll t=x;
		x=y;
		y=t-y*(a/b);
	}
}
int main(){
    ll a, b, c;
    cin >> a >> b >> c;
 	if (c%gcd(a, b)!=0){
 		cout << "-1";
 		return 0;
 	}
 	extendedeuc(a, b);
 	cout << -x*(c)/gcd(a,b) <<" "<<-y*c/gcd(a, b);
    return 0;
}