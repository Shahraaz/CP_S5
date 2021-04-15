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

int64_t solveCase(int N, const vector<int64_t> &a)
{
    // TODO: edit here
    set<pair<int64_t, int>> ss;
    for (size_t i = 0; i < a.size(); i++)
        ss.insert({a[i], i});
    while (a.size() > 1)
    {
        auto mini = *ss.begin();
        auto maxi = *ss.rbegin();
        if (mini.first == maxi.first)
            break;
        // ss.erase(mini);
        ss.erase(maxi);
        if(maxi.first % mini.first == 0)
            maxi.first = mini.first;
        else 
            maxi.first %= mini.first;
        ss.insert(maxi);
    }
    return ss.begin()->first;
}

// generated by oj-template v4.7.2 (https://github.com/online-judge-tools/template-generator)
int main()
{
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    constexpr char endl = '\n';
    int N;
    cin >> N;
    vector<int64_t> a(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> a[i];
    }
    auto ans = solveCase(N, a);
    cout << ans << endl;
    return 0;
}