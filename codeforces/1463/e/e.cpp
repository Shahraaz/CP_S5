#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/debug.h"
#else
#define db(...)
#endif

#define all(v) v.begin(), v.end()
#define pb push_back
using ll = long long;
const int NAX = 2e5 + 5, MOD = 1000000007;

class UnionFind
{ // OOP style
private:
    vector<int> p, rank, setSize; // remember: vi is vector<int>
    int numSets;

public:
    UnionFind(int N)
    {
        setSize.assign(N, 1);
        numSets = N;
        rank.assign(N, 0);
        p.assign(N, 0);
        for (int i = 0; i < N; i++)
            p[i] = i;
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    bool unionSet(int i, int j)
    {
        if (!isSameSet(i, j))
        {
            numSets--;
            int x = findSet(i), y = findSet(j);
            // rank is used to keep the tree short
            if (rank[x] > rank[y])
            {
                p[y] = x;
                setSize[x] += setSize[y];
            }
            else
            {
                p[x] = y;
                setSize[y] += setSize[x];
                if (rank[x] == rank[y])
                    rank[y]++;
            }
            return true;
        }
        return false;
    }
    int numDisjointSets() { return numSets; }
    int sizeOfSet(int i) { return setSize[findSet(i)]; }
};

void no()
{
    cout << 0 << '\n';
    exit(0);
}

void solveCase()
{
    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n);
    vector<int> left(n, -1), right(n, -1);
    for (size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        if (x == 0)
            continue;
        --x;
        adj[x].pb(i);
    }
    for (size_t i = 0; i < n; i++)
    {
        db(i, adj[i]);
    }
    UnionFind U(n);
    for (size_t i = 0; i < k; i++)
    {
        int x, y;
        cin >> x >> y;
        --x, --y;
        if (right[x] != -1 || left[y] != -1 || !U.unionSet(x, y))
            no();
        right[x] = y;
        left[y] = x;
    }
    vector<int> degree(n);
    for (int prereq = 0; prereq < n; prereq++)
        for (auto &next : adj[prereq])
            if (!U.isSameSet(prereq, next))
                degree[U.findSet(next)]++;
    queue<int> Q;
    for (int course = 0; course < n; course++)
        if (course == U.findSet(course))
            if (degree[course] == 0)
                Q.push(course);
    vector<int> vis(n);
    vector<int> res;
    while (Q.size())
    {
        auto top = Q.front();
        db(top, left[top], right[top]);
        db(degree);
        Q.pop();
        while (left[top] != -1)
            top = left[top];
        while (top != -1)
        {
            db(top, right[top]);
            for (auto next : adj[top])
            {
                next = U.findSet(next);
                --degree[next];
                if (degree[next] == 0)
                    Q.push(next);
            }
            res.pb(top);
            top = right[top];
        }
    }
    if (res.size() != n)
        no();
    vector<int> invpos(n, -1);
    for (size_t i = 0; i < n; i++)
        invpos[res[i]] = i;
    for (size_t i = 0; i < n; i++)
    {
        db(invpos[i]);
        db(i, adj[i]);
        for (auto &next : adj[i])
        {
            if (invpos[i] > invpos[next])
                no();
        }
    }
    for (auto &x : res)
        cout << x + 1 << ' ';
    cout << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}