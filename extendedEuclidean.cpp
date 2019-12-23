#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll gcd(ll a, ll b)
{
	if (b==0)
	{
		return a;
	}
	return gcd(b, a%b);
}
ll x, y;
ll extendedeuc(ll a, ll b)
{
	if (b==0)
	{
		x=1;
		y=0;
	}
	else
	{
		extendedeuc(b, a%b);
		ll t=x;
		x=y;
		y=t-y*(a/b);
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll a, b, c;
    cin >> a >> b >> c;
 	if (c%gcd(a, b)!=0)
 	{
 		cout << "-1";
 		return 0;
 	}
 	extendedeuc(a, b);
 	cout << -x*(c)/gcd(a,b) <<" "<<-y*c/gcd(a, b);
    // cout << gcd(a, b);
    return 0;
}