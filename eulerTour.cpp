#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define endl "\n"

const ll L = 1e5+5;
vector <ll> arr(L);
vector <ll> seg(4*L);
vector <ll> adj[L];
vector <ll> visited(L);
vector < pair <ll, ll> > store(L);

void make(ll i, ll tl, ll tr)
{
	if(tl==tr)
	{
		seg[i] = arr[tl];
	}

	else
	{
		ll mid = tl + (tr-tl)/2;

		make(i<<1, tl ,mid);
		make(i<<1|1, mid+1, tr);

		seg[i] = seg[i<<1] + seg[i<<1|1];
	}
}

ll query(ll i, ll tl, ll tr, ll l, ll r)
{
	if(r<tl || l>tr)
	{
		return 0;
	}

	if(l<=tl && tr<=r)
	{
		return seg[i];
	}

	ll mid = tl + (tr-tl)/2;

	return query(i<<1, tl, mid, l, r) + query(i<<1|1, mid+1, tr, l, r);
}

void update(ll i, ll tl, ll tr, ll idx, ll val)
{
	if(tl==tr)
	{
		seg[i] = val;
	}

	else
	{
		ll mid = tl + (tr-tl)/2;

		if(tl<=idx && idx<=mid)
		{
			update(i<<1, tl, mid, idx, val);
		}

		else
		{
			update(i<<1|1, mid+1, tr, idx, val);
		}

		seg[i] = seg[i<<1] + seg[i<<1|1];
	}
}

ll cTime = 0;
void eulerTour(ll s)
{
	visited[s] = true;

	store[s].ff = cTime;

	for(auto i: adj[s])
	{
		if(!visited[i])
		{
			cTime++;
			eulerTour(i);
		}
	}

	store[s].ss = cTime;
}

int main()
{
	// ios_base::sync_with_stdio(false);
	// cin.tie(NULL); cout.tie(NULL);

	ll n, m;
	cin >> n >> m;

	for(ll i=0; i<m; i++)
	{
		ll u, v;
		cin >> u >> v;

		adj[u].pb(v);
	}

	for(ll i=1; i<=n; i++)
	{
		cin >> arr[i];
	}

	make(1, 1, n);

	// ll s;
	// cin >> s;

	eulerTour(1);

	for(ll i=1; i<=n; i++)
	{
		cout << i << ": " << store[i].ff << " " << store[i].ss << endl;
	}

	ll Q;
	cin >> Q;

	// cout << Q << endl;

	while(Q--)
	{
		ll node, type;
		cin >> node >> type;

		if(type==1)
		{
			ll val;
			cin >> val;

			update(1, 1, n, node, val);
		}

		else
		{
			cout << query(1, 1, n, store[node].ff+1, store[node].ss+1) << endl;
		}
	}

	

	return 0;
}