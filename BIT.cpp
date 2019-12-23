/*kquery using bit*/
/*1 base indexing*/

/* 
Problem Statement:
Given a sequence of n numbers a1, a2, ..., an and a number of k- queries.
A k-query is a triple (i, j, k) (1 ≤ i ≤ j ≤ n). For each k-query
(i, j, k), you have to return the number of elements greater than k in
the subsequence ai, ai+1, ..., aj.

Input

    Line 1: n (1 ≤ n ≤ 30000).
    Line 2: n numbers a1, a2, ..., an (1 ≤ ai ≤ 109).
    Line 3: q (1 ≤ q ≤ 200000), the number of k- queries.
    In the next q lines, each line contains 3 numbers i, j, k 
    representing a k-query (1 ≤ i ≤ j ≤ n, 1 ≤ k ≤ 109).

Output

    For each k-query (i, j, k), print the number of elements greater
    than k in the subsequence ai, ai+1, ..., aj in a single line.

*/

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

struct M
{
   	ll key;
   	ll key2;
   	ll key3;	
   	ll key4;
};
bool cmp(struct M a, struct M b)
{
	if(a.key==b.key) return b.key4<=a.key4;
  	return (a.key >  b.key);
}
bool cmp2(struct M a,struct M b)
{
	return a.key4<b.key4;
}

ll bit[30002];


ll update(ll idx,ll n)
{
	while(idx<=n)
	{
		bit[idx]+=1;
		idx=idx+(idx&(-idx	));
	}
}

ll query(ll idx)
{
	ll sum=0;
	while(idx>0)
	{
		sum+=bit[idx];
		idx=idx-(idx&(-idx));
	}
	return sum;
}

inline int in(){int N=0;register char c=getchar();while( c < 48 || c > 57 ){c=getchar();}while(c>47 && c< 58){N = (N << 3) + (N << 1) + (c - 48);c=getchar();}return N;}

struct M Ssp[230000];
int main()
{

	ll n;
	n=in();
	ll q;
	for (int i = 0; i < n; ++i)
	{
		ll a; 
		a=in();
		Ssp[i].key=a;
		Ssp[i].key2=0;
		Ssp[i].key4=i;
		Ssp[i].key3=0;
	}
	q=in();

	for (int i = 0; i < q; ++i)
	{
		ll l,r,k;
		l=in();
		r=in();
		k=in();
		Ssp[i+n].key=k;
		Ssp[i+n].key2=l;
		Ssp[i+n].key3=r;
		Ssp[i+n].key4=i+n;
	}

	sort(Ssp, Ssp+n+q, cmp);

	for (int i = 0; i < n+q; ++i)
	{
		if(!Ssp[i].key2)
		{
			
			update(Ssp[i].key4+1,n);
		}
		else
		{
			// cout <<Ssp[i].key3<<" "<<Ssp[i].key2<<" "<<i<<endl;
			Ssp[i].key=query(Ssp[i].key3)-query(Ssp[i].key2-1);
		}
	}
	// cerr <<"xxx"<<endl;
	sort(Ssp, Ssp+n+q, cmp2);
	for (int i = 0; i < n+q; ++i)
	{
		if(	Ssp[i].key2)
		{
			printf("%lld\n",Ssp[i].key);
		}
	}
}