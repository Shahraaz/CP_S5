// Optimise
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/home/shahraaz/bin/debug.h"
#else
#define db(...)
#endif

using ll = long long;
#define f first
#define s second
#define pb push_back
#define all(v) v.begin(), v.end()

const int NAX = 2e5 + 5, MOD = 1000000007;

void solveCase()
{
    string str;
    int n;
    cin >> n;
    cin >> str;
    // int n = str.length();
    vector<int> len(n);
    deque<pair<int, char>> Q;
    deque<pair<int, char>> PQ;
    for (size_t i = 0; i < n;)
    {
        int j = i;
        // int len = 0;
        while (j < n && str[j] == str[i])
            ++j;
        len[i] = j - i;
        Q.pb({i, str[i]});
        if (len[i] > 1)
            PQ.pb({i, len[i]});
        i = j;
    }
    int opers = 0;
    while (Q.size() || PQ.size())
    {
        while (PQ.size() && len[PQ.front().f] <= 1)
            PQ.pop_front();
        while (Q.size() && len[Q.front().f] == 0)
            Q.pop_front();
        db(PQ);
        db(Q);
        db(len);
        if (PQ.empty())
        {
            if (Q.empty())
                break;
            len[Q.front().f]--;
        }
        else
        {
            len[PQ.front().f]--;
        }
        opers++;
        while (Q.size() && len[Q.front().f] == 0)
            Q.pop_front();
        if (Q.empty())
            break;
        auto idx = Q.front().f;
        len[idx] = 0;
        Q.pop_front();
        if (PQ.size() && PQ.front().f == idx)
            PQ.pop_front();
    }
    cout << opers << '\n';
}

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
