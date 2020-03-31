#include <bits/stdc++.h>
using namespace std;
#define mem(x, y) memset(x, y, sizeof(x))
#define bitcount __builtin_popcountll
#define mod 1000000007
#define N 1000009
#define fast                 \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);
#define ss(s) cin >> s;
#define si(x) scanf("%d", &x);
#define sl(x) cin >> x;
#define pb push_back
#define mp make_pair
#define all(v) v.begin(), v.end()
#define S second
#define F first
#define ll long long
int n, m;
vector<int> arr[N];
int arr1[N];
vector<pair<int, int>> adj[100008]; //max-size
void graph(int n)
{
    for (int i = 1; i <= n; i++)
    {
        int x = arr[i][0];
        int y = arr[i][1];
        adj[x].push_back(mp(y, arr1[i])); //arr1[i] stores th color of the edge
        adj[y].push_back(mp(x, arr1[i]));
    }
}
int col[N];
bool vis[N];
int main()
{
    //fast                          //uncomment on submission
    cin >> n >> m;
    assert(n >= 2 && n <= 100000);
    assert(m >= 2 && m <= 100000);
    for (int i = 1; i <= n; i++)
        cin >> arr1[i];
    for (int i = 1; i <= m; i++)
    {
        int sz;
        cin >> sz;
        for (int j = 0; j < sz; j++)
        {
            int y;
            cin >> y;
            arr[y].push_back(i);
        }
    }
    graph(n);
    mem(col, -1);
    mem(vis, false);
    bool p = true;
    for (int i = 1; i <= m; i++)
    {
        if (!vis[i] && adj[i].size())
        {
            col[i] = 0;
            vis[i] = true;
            queue<int> q;
            q.push(i);

            while (q.size())
            {
                int node = q.front();
                q.pop();

                for (auto pi : adj[node])
                {
                    int co = col[node];
                    if (pi.S == 0)
                    { //if the edge is 0 then give the opposite color.
                        co = 1 - co;
                    }
                    if (vis[pi.F] && col[pi.F] != co)
                    {
                        p = false;
                    }
                    if (!vis[pi.F])
                    {
                        col[pi.F] = co;
                        vis[pi.F] = true;
                        q.push(pi.F);
                    }
                }
            }
        }
    }

    if (!p)
        cout << "NO";
    else
        cout << "YES";
}