typedef pair<long long, int> pil;
typedef vector<pair<int, long long>> __vil;
typedef vector<int> __vi;
typedef vector<__vil> __Graph;

pair<long long, __vi> Dijkstart(__Graph &input, int src, int dest)
{
	int n = input.size();
	vector<long long> Dist(n, LLONG_MAX), prev(n, -1);
	Dist[src] = 0;
	priority_queue<pil, vector<pil>, greater<pil>> Q;
	Q.push({src, 0});
	while (!Q.empty())
	{
		auto t = Q.top();
		Q.pop();
		if (Dist[t.s] != t.f)
			continue;
		if (t.s == dest)
			break;
		u = t.s;
		for (auto v : G[u])
			if (Dist[v.f] > (Dist[u] + v.s))
			{
				// db(v.f);
				prev[v.f] = u;
				Dist[v.f] = Dist[u] + v.s;
				Q.push({Dist[v.f], v.f});
			}
	}
	vector<int> Path;
	if (prev[src] == (-1))
		;
	else
	{
		u = dest;
		stack<int> S;
		S.push(u);
		while (prev[u] != (-1))
		{
			u = prev[u];
			S.push(u);
		}
		while (!S.empty())
		{
			Path.push_back(1 + S.top());
			Vis[S.top()] = true;
			S.pop();
		}
	}
	return {Dist[dest],Path}
}