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

void solveCase()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> vecc(m);
    vector<int> row(n), col(n);
    set<int> freeinboth;
    for (auto &[x, y] : vecc)
    {
        cin >> x >> y;
        --x, --y;
        row[x]++;
        col[y]++;
    }
    auto alter_elem = [&](int x) {
        if (row[x] == 0 && col[x] == 0)
            freeinboth.insert(x);
        else
            freeinboth.erase(x);
    };
    for (size_t i = 0; i < n; i++)
    {
        if (row[i] == 0 && col[i] == 0)
            freeinboth.insert(i);
    }
    db(n, m);
    db(vecc);
    db(freeinboth);
    // assert(freeinboth.size());
    int res = 0;
    for (auto &[x, y] : vecc)
    {
        db(x, y);
        db(freeinboth);
        db(row);
        db(col);
        db(vecc);
        if (x == y)
            continue;
        if (col[x] == 0)
        {
            col[y]--;
            alter_elem(y);

            col[x]++;
            alter_elem(x);

            y = x;
            res++;
        }
        else if (row[y] == 0)
        {
            row[x]--;
            alter_elem(x);

            row[y]++;
            alter_elem(y);

            x = y;
            res++;
        }
        else
            continue;
    }
    for (auto &[x, y] : vecc)
    {
        db(x, y);
        db(freeinboth);
        db(row);
        db(col);
        db(vecc);
        if (x == y)
            continue;
        if (col[x] == 0)
        {
            col[y]--;
            alter_elem(y);

            col[x]++;
            alter_elem(x);

            res++;
            y = x;
        }
        else if (row[y] == 0)
        {
            row[x]--;
            alter_elem(x);

            row[y]++;
            alter_elem(y);

            res++;
            x = y;
        }
        else
        {
            assert(freeinboth.size());
            auto idx = *freeinboth.begin();
            freeinboth.erase(idx);

            row[x]--;
            alter_elem(x);

            col[y]--;
            alter_elem(y);

            col[idx] = 1, row[idx] = 1;
            ++res;
            ++res;
            x = y = idx;
        }
    }
    db(vecc);
    cout << res << '\n';
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
        solveCase();
    return 0;
}