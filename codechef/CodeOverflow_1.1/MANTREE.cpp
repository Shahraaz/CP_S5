/*
Problem Name: Mango Tree 
Problem Code: MANTREE
Problem Link: https://www.codechef.com/COFW2020/problems/MANTREE

Author Name: Shrey Kaushik
Author Link: https://www.codechef.com/users/shreyk5
*/
#include <bits/stdc++.h>
using namespace std;
long long int values[100001] = {0};
vector<int> vect[100001];

long long int dfs(int arr[], int s, bool visited[])
{
    visited[s] = true;

    for (int i = 0; i < vect[s].size(); i++)
    {
        if (visited[vect[s][i]] == false)
        {
            long long int g = dfs(arr, vect[s][i], visited);
            values[s] += g;
        }
    }
    values[s] += arr[s];
    return values[s];
}
int main()
{
    int n, q;

    cin >> n >> q;

    int arr[n + 1];

    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;

        vect[u].push_back(v);
        vect[v].push_back(u);
    }
    vector<long long int> quotient;

    while (q--)
    {
        int b_quo;
        cin >> b_quo;
        quotient.push_back(b_quo);
    }
    bool visited[n + 1] = {false};

    for (int i = 1; i <= n; i++)
    {
        if (visited[i] == false)
            dfs(arr, i, visited);
    }

    vector<pair<long long int, int>> p;

    for (int i = 1; i <= n; i++)
        p.push_back(make_pair(values[i], i));

    sort(p.begin(), p.end());

    for (int i = 0; i < quotient.size(); i++)
    {
        auto itr = lower_bound(p.begin(), p.end(), make_pair(quotient[i], (int)0));
        if (itr != p.end())
            cout << (*itr).second << endl;

        else
            cout << "-1" << endl;
    }
}
