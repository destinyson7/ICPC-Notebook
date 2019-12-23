#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define INF LLONG_MAX
#define sz(ar) (ll)ar.size()


// ------------------------------ DFS ------------------------------

#define N 100001
vector<ll>visit(N, 0);
void dfs(auto &ar, ll x){
	visit[x] = 1;
	for(auto i:ar[x]){
		if(visit[i] == 1)
			continue;
		dfs(ar, i);
	}
}

// ------------------------------ BFS ------------------------------

#define N 100001
vector<ll>visit(N, 0);
void bfs(auto &ar, ll x){
	queue<ll>q;
	visit[x] = 1;
	q.push(x);
	while(!q.empty()){
		x=q.front(); q.pop();
		for(auto i:ar[x]){
			if(visit[i] == 1) continue;
			visit[i] = 1;
			q.push(i);
		}
	}
}

// ------------------------------ PRIMS ------------------------------

#define N 100001
vector<ll>visit(N, 0);
vector<ll>par(N, 0);
ll n;
void prims(auto &ar){
	priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>>pq;
	ll cnt = 0;
	pq.push(make_pair(1, 0));
	par[1] = 0;
	while(!pq.empty()){
		auto p = pq.top(); pq.pop();
		if(visit[p.first] == 1) continue;
		visit[p.first] = 1;
		if(cnt == n) return;
		for(auto i:ar[p.first]){
			if(visit[i.first] == 1) continue;
			par[i.first] = p.first;
			pq.push(make_pair(i.first, i.second));
		}
	}
}

// ------------------------------ DIJKSTRA ------------------------------

#define N 100001
vector<ll>path(N, INF);
vector<ll>visit(N, 0);
void dijk(auto &ar, ll x){
	priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>>pq;
	pq.push(make_pair(x, 0));
	path[x] = 0;
	while(!pq.empty()){
		auto p=pq.top(); pq.pop();
		if(visit[p.first] == 1) continue;
		visit[p.first] = 1;
		for(auto i:ar[p.first]){
			if(visit[i.first] == 1){
				continue;
			}
			if(path[i.first] > path[p.first] + i.second){
				path[i.first] = path[p.first] + i.second;
				pq.push(make_pair(i.first, path[i.first]));
			}
		}
	}
}

// ------------------------------ BELLMAN FORD ------------------------------


#define N 100001
struct edge{
	ll u,v,w;
};
vector<ll>path(N, INF);
vector<ll>par(N, 0);
ll n;
ll bellman_ford(auto &ar, ll x){
	ll m = sz(ar);
	path[x] = 0;
	for(ll i=1; i < n; i++){
		for(ll j = 0; j < m; j++){
			if(path[ar[j].v] > path[ar[j].u] + ar[j].w){
				path[ar[j].v] = path[ar[j].u] + ar[j].w;
				par[ar[j].v] = ar[j].u;
			}
		}
	}
	for(ll i = 0; i < m; i++){
		if(ar[i].v > ar[i].u + ar[i].w)
			return 0;
	}
	return 1;
}

// ------------------------------ Floyd Warshal ------------------------------

#define N 1001
ll graph[N][N];
ll n;
void floydWarshal(){
	for(ll k = 1; k <= n; k++){
		for(ll i = 1; i <= n; i++){
			for(ll j = 1; j <= n; j++){
				if(graph[i][j] > graph[i][k] + graph[k][j]){
					graph[i][j] = graph[i][k] + graph[k][j];
				}
			}
		}
	}
}

// ------------------------------ Shortest Path in DAG ------------------------------

#define N 100001
vector<ll>visit(N, 0);
stack<ll>st;
void st_dfs(auto &ar, ll x){
	visit[x] = 1;
	for(auto i:ar[x]){
		if(visit[i.first] == 0){
			st_dfs(ar, i.first);
		}
	}
	st.push(x);
}
void toposort(auto &ar){
	ll n = sz(ar)-1;
	for(ll i=1; i <= n; i++){
		if(visit[i] == 0)
			st_dfs(ar, i);
	}
}
vector<ll>path(N, INF);
void shortpathDAG(auto &ar, ll x){
	toposort(ar);
	path[x] = 0;
	while(!st.empty()){
		auto t = st.top(); st.pop();
		if(t == x){
			st.push(x);
			break;
		}
	}
	while(!st.empty()){
		auto t = st.top(); st.pop();
		for(auto i:ar[t]){
			if(path[i.first] > path[t] + i.second){
				path[i.first] = path[t] + i.second;
			}
		}
	}
}

// ------------------------------ Jhonson Algo ------------------------------

#define N 1001
vector<ll>path(N, INF);
vector<ll>par(N, 0);
ll n;
ll bellman_ford(auto &ar, ll x){
	path[x]=0;
	for(ll i = 0; i < n; i++){
		for(ll j = 0; j <= n; j++){
			for(auto it:ar[j]){
				if(path[it.first] > path[j] + it.second){
					path[it.first] = path[j] + it.second;
					par[it.first] = j;
				}
			}
		}
	}
	for(ll j = 0; j <= n; j++){
		for(auto it:ar[j]){
			if(path[it.first] > path[j] + it.second){
				return 0;
			}
		}
	}
	return 1;
}
ll spath[N][N];
vector<ll>visit(N, 0);
void dijk(auto &ar, ll x){
	priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>>pq;
	pq.push(make_pair(x, 0));
	spath[x][x]=0;
	while(!pq.empty()){
		auto p = pq.top(); pq.pop();
		if(visit[p.first] == 1) continue;
		visit[p.first] = 1;
		for(auto i:ar[p.first]){
			if(visit[i.first] == 1){
				continue;
			}
			if(spath[x][i.first] > spath[x][p.first] + i.second){
				spath[x][i.first] = spath[x][p.first] + i.second;
				pq.push(make_pair(i.first, spath[x][i.first]));
			}
		}
	}
}
ll jhonson(auto &ar){
	for(ll i = 1; i <= n; i++){
		ar[0].pb(make_pair(i, 0));
	}
	if(!bellman_ford(ar, 0)){
		return 0;
	}
	for(ll i = 1; i <= n; i++){
		for(auto &j:ar[i]){
			j.second += path[i]-path[j.first];
		}
	}
	for(ll i = 1; i <= n; i++){
		for(ll j = 1; j <= n; j++){
			visit[j] = 0;
			spath[i][j] = INF;
		}
		dijk(ar, i);
	}
	return 1;
}



int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
}