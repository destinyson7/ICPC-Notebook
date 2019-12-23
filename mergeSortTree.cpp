// Merge Sort Tree to calculate kth smallest number in a range
// Works for online queries

// Problem Codeforces 1262D2

#include <bits/stdc++.h>
using namespace std;
 
typedef long long int ll;
typedef pair <ll, ll> pll;

#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define all(a) a.begin(), a.end()
#define sz(a) (ll)(a.size())
#define endl "\n"
 
const ll L = 2e5+5;
 
bool cmp(pll a, pll b)
{
    if(a.ff == b.ff)
    {
        return a.ss < b.ss; 
    }
 
    return a.ff > b.ff;
}
 
ll kd[30][L] , a[L] , pos[L] , Real[L];
 
void init(ll d,ll b,ll e){
    if(b == e){
        kd[d][b] = pos[b];
        return;
    }
    ll m = (b + e) >> 1;
    init(d + 1,b,m);
    init(d + 1,m+1,e);
    ll i = b , j = m + 1;
    ll ptr = 0;
    while(i <= m && j <= e){
        if(kd[d + 1][i] < kd[d + 1][j]){
            kd[d][b + (ptr++)] = kd[d + 1][i++];
        }else{
            kd[d][b + (ptr++)] = kd[d + 1][j++];
        }
    }
    while(i <= m) kd[d][b + (ptr++)] = kd[d + 1][i++];
    while(j <= e) kd[d][b + (ptr++)] = kd[d + 1][j++];
}
 
inline ll find(ll d,ll b,ll e,ll x1,ll x2){
    return upper_bound(kd[d] + b,kd[d] + e + 1,x2) - lower_bound(kd[d] + b,kd[d] + e + 1,x1);
}
 
ll get(ll n,ll x1,ll x2,ll k){
    ll d = 0 , b = 1 , e = n;
    while(b != e){
        ll lll = find(d + 1,b,(b+e)/2,x1,x2);
        ll mm = ((b + e) >> 1LL);
        if(lll >= k){
            e = mm;
        }else{
            b = mm + 1;
            k -= lll;
        }
        ++d;
    }
    return b;
}
 
ll copy_it[L];
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
 
    ll n;
    cin >> n;
 
    vector <ll> a(n, 0);
    vector <pll> pq;
 
    for(ll i=0; i<n; i++)
    {
        ll t;
        cin >> t;
 
        copy_it[i] = t; 
        pq.pb(mp(t, i));
    }
 
    sort(all(pq), cmp);
 
    vector <ll> vals;
    for(ll i=1; i<=n; i++)
    {
        a[i] = pq[i-1].ss;
        vals.pb(a[i]);
    }
 
    sort(all(vals));
 
    for(ll i=1; i<=n; i++)
    {
        ll old = a[i];
        a[i] = lower_bound(all(vals), a[i]) - vals.begin() + 1;
        pos[a[i]] = i;
        Real[a[i]] = old;
    }
 
    init(0, 1, n);
 
    ll m;
    cin >> m;
 
    while(m--)
    {
        ll k, which;
        cin >> k >> which;
 
        cout << copy_it[Real[get(n, 1, k, which)]] << endl;
    }
 
    return 0;
}