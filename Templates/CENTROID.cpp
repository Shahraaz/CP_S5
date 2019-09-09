struct CentroidDecomposition
{
	vector<vector<int>> &Adj;
	vector<int> subTreeSize, parentInCentroid;
	vector<bool> Computed;
	int root, n, currentTreeSize;
	CentroidDecomposition(vector<vector<int>> &tree) : Adj(tree)
	{
		n = Adj.size();
		parentInCentroid.assign(n, -1);
		subTreeSize.assign(n, 0);
		Computed.assign(n, false);
		decompose(0, -1);
	}
	void dfs(int node, int parent)
	{
		currentTreeSize++;
		subTreeSize[node] = 1;
		for (auto child : Adj[node])
		{
			if (child == parent || Computed[child])
				continue;
			dfs(child, node);
			subTreeSize[node] += subTreeSize[child];
		}
	}
	int getCentroid(int node, int parent)
	{
		for (auto child : Adj[node])
			if (child != parent && !Computed[child])
				if (subTreeSize[child] > currentTreeSize / 2)
					return getCentroid(child, node);
		return node;
	}
	void decompose(int node, int parent)
	{
		currentTreeSize = 0;
		dfs(node, node);
		int centroid = getCentroid(node, node);
		parentInCentroid[centroid] = (parent == -1) ? centroid : parent;
		Computed[centroid] = true;
		for (auto child : Adj[centroid])
			if (!Computed[child])
				decompose(child, centroid);
	}
};
