#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define all(a) a.begin(), a.end()
#define sz(a) (ll)(a.size())
#define endl "\n"

const ll L = 1e5+5;

vector < pair <ll, ll> > adj[L];
vector <ll> parent(L);
vector <ll> unionSize(L);

vector < pair <ll, pair <ll, ll> > > weights;

ll find(ll s)
{
    if(parent[s]==s)
    {
        return s;
    }

    return parent[s]=find(parent[s]);
}

void unionSet(ll x, ll y)
{
    ll a = find(x);
    ll b = find(y);

    if(unionSize[a] > unionSize[b])
    {
        swap(x, y);
    }

    parent[a] = b;
    unionSize[b] += unionSize[a];
}

ll kruskals(ll M)
{
    ll ans = 0;

    for(ll i=0; i<M; i++)
    {
        ll u = weights[i].ss.ff;
        ll v = weights[i].ss.ss;
        ll w = weights[i].ff;

        if(find(u)!=find(v))
        {
            ans+=w;
            unionSet(u, v);
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll N, M;
    cin >> N >> M;

    for(ll i=0; i<L; i++)
    {
        parent[i] = i;
        unionSize[i] = 1;
    }

    for(ll i=0; i<M; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;

        adj[u].pb(mp(v, w));
        adj[v].pb(mp(u, w));

        weights.pb(mp(w, mp(u, v)));
    }

    sort(weights.begin(), weights.end());

    cout << kruskals(M) << endl;

    return 0;
}