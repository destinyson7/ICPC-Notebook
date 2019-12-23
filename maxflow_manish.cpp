#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
 
class Dinics {
public:
	typedef int flowType; // can use float/double
	static const flowType INF = 1e9; // maximum capacity
	static const flowType EPS = 0; // minimum capacity/flow change
 
private:
	int nodes, src, dest;
	vector<int> dist, q, work;
	struct Edge {
	  int to, rev;
	  flowType f, cap;
	};
	vector< vector<Edge> > g;
 
	bool dinic_bfs() {
	  fill(dist.begin(), dist.end(), -1);
	  dist[src] = 0;
	  int qt = 0;
	  q[qt++] = src;
	  for (int qh = 0; qh < qt; qh++) {
	    int u = q[qh];
	    for (int j = 0; j < (int) g[u].size(); j++) {
	      Edge &e = g[u][j];
	      int v = e.to;
	      if (dist[v] < 0 && e.f < e.cap) {
	        dist[v] = dist[u] + 1;
	        q[qt++] = v;
	      }
	    }
	  }
	  return dist[dest] >= 0;
	}
	int dinic_dfs(int u, int f) {
	  if (u == dest)
	    return f;
	  for (int &i = work[u]; i < (int) g[u].size(); i++) {
	    Edge &e = g[u][i];
	    if (e.cap <= e.f) continue;
	    int v = e.to;
	    if (dist[v] == dist[u] + 1) {
	      flowType df = dinic_dfs(v, min(f, e.cap - e.f));
	      if (df > 0) {
	        e.f += df;
	        g[v][e.rev].f -= df;
	        return df;
	      }
	    }
	  }
	  return 0;
	}
 
public:
	Dinics(int n): dist(n, 0), q(n, 0),
		work(n, 0), g(n), nodes(n) {}
 
	// s->t (cap); t->s (rcap)
	void addEdge(int s, int t, flowType cap, flowType rcap = 0) {
	  g[s].push_back({t, (int) g[t].size(), 0, cap});
	  g[t].push_back({s, (int) g[s].size() - 1, 0, rcap});
	}
	flowType maxFlow(int _src, int _dest) {
	  src = _src;
	  dest = _dest;
	  flowType result = 0;
	  while (dinic_bfs()) {
	    fill(work.begin(), work.end(), 0);
			flowType delta;
	    while ((delta = dinic_dfs(src, INF)) > EPS)
	      result += delta;
	  }
	  return result;
	}
};

vector<pair<ll,ll>> g[100];
int main()
{
	ll n,m,x;
	cin>>n>>m>>x;
	for(ll i=1;i<=m;i++)
	{
		ll u, v, c;
		cin>>u>>v>>c;
		g[u].push_back({v, c});
		// g[v].push_back({u, c});
	}
	double lb=0, ub=10000000, mid/*(lb+ub)/2*/;
	double ans=0;
	int cnt=100;
	while(cnt)
	{
		cnt--;
		mid=(lb+ub)/2;
		Dinics d(n);
		for (int i = 1; i < n+1; ++i)
		{
			for(auto j:g[i])
			{
				if (j.second/mid>1e7)
				{	
					d.addEdge(i-1, j.first-1, x);
				}
				else
				{
					d.addEdge(i-1, j.first-1, floor((j.second)/mid));
				}
			}
		}
		if(d.maxFlow(0, n-1)>=x)
		{
			lb=mid;
		}
		else
		{
			ub=mid;
		}
		ans=mid;
	}
	cout <<fixed<<setprecision(10)<< ans*x;
	return 0;
}