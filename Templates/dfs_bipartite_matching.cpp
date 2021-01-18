#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define f first
#define s second


struct dfs_bipartite_matching{
	int n, m, flow = 0;
	vector<vector<int>> adj;
	vector<int> pu, pv; // u is matched with pu[u] and v with pv[v], -1 if no match
	dfs_bipartite_matching(int n, int m): n(n), m(m), pu(n, -1), pv(m, -1), cur(n), adj(n){ }
	int insert(int from, int to){
		adj[from].push_back(to);
		return (int)adj[from].size() - 1;
	}
	int id = 0;
	vector<int> cur;
	bool dfs(int u){
		cur[u] = id;
		for(auto v: adj[u]) if(!~pv[v]){
			pu[u] = v, pv[v] = u;
			return true;
		}
		for(auto v: adj[u]) if(cur[pv[v]] != id && dfs(pv[v])){
			pu[u] = v, pv[v] = u;
			return true;
		}
		return false;
	}
	int solve(){ // O(VE)
		while(true){
			int augment = 0;
			++ id;
			for(int u = 0; u < n; ++ u) if(pu[u] == -1 && dfs(u)) ++ augment;
			if(!augment) break;
			flow += augment;
		}
		return flow;
	}
	int run_once(int v){
		if(pu[v] != -1) return 0;
		++ id;
		return dfs(v);
	}
	pair<vector<int>, vector<int>> minimum_vertex_cover(){
		solve();
		vector<int> L, R, visL(n), visR(m);
		function<void(int)> dfs = [&](int u){
			visL[u] = true;
			for(auto v: adj[u]) if(v != pu[u] && !visR[v]){
				visR[v] = true, R.push_back(v);
				if(~pv[v]) dfs(pv[v]);
			}
		};
		for(int u = 0; u < n; ++ u) if(!visL[u] && pu[u] == -1) dfs(u);
		for(int u = 0; u < n; ++ u) if(!visL[u]) L.push_back(u);
		return {L, R};
	}
};
 