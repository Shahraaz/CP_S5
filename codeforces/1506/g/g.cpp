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

struct Bit
{
    int size;
    vector<int> table;
    Bit(int size)
    {
        this->size = size;
        table.resize(size);
    }
    void update(int i, int delta)
    {
        while (i < size)
        {
            table[i] += delta;
            i = i | (1 + i);
        }
    }
    int sum(int i)
    {
        int ret = 0;
        while (i >= 0)
        {
            ret += table[i];
            i = (i & (i + 1)) - 1;
        }
        return ret;
    }
    int rangeSum(int i, int j)
    {
        if (i == 0)
            return sum(j);
        return sum(j) - sum(i - 1);
    }
    void print()
    {
#ifdef LOCAL
        for (int i = 0; i < size; i++)
            cout << rangeSum(i, i) << ' ';
        cout << '\n';
#else

#endif
    }
};

void solveCase()
{
    string str;
    cin >> str;
    map<char, int> cnt;
    vector<deque<int>> poses(26);
    int n = str.size();
    vector<int> is_res(n, 0), ha_hogya(26);
    for (size_t i = 0; i < str.size(); i++)
    {
        cnt[str[i] - 'a']++;
        poses[str[i] - 'a'].pb(i);
    }
    while (true)
    {
        int todel = -1;
        int lim = n;
        for (size_t i = 0; i < lim; i++)
        {
            int cidx = str[i] - 'a';
            db(char('a' + cidx), poses[cidx]);
            if (poses[cidx].size() && poses[cidx].front() == i)
            {
                if (poses[cidx].size() > 1)
                    lim = min(lim, poses[cidx].back());
                if (todel == -1 || todel < cidx)
                    todel = cidx;
                if (poses[cidx].size() == 1)
                    break;
            }
        }
        db(todel, char(todel + 'a'));
        if (todel == -1)
        {
            for (size_t i = 0; i < 26; i++)
            {
                if (cnt[i])
                {
                    if (todel == -1 || poses[i].front() < poses[todel].front())
                        todel = i;
                }
            }
            if (todel == -1)
                break;
        }
        int idx = poses[todel].front();
        db(todel, char(todel + 'a'), idx);
        is_res[idx] = 1;
        for (int i = 26 - 1; i >= 0; i--)
        {
            while (poses[i].size() && poses[i].front() <= idx)
            {
                int idx2 = poses[i].front();
                cnt[str[idx2] - 'a']--;
                poses[i].pop_front();
            }
        }
        while (poses[todel].size())
        {
            poses[todel].pop_front();
            cnt[todel]--;
        }
    }
    db(is_res);
    for (size_t i = 0; i < n; i++)
    {
        if (is_res[i])
            cout << str[i];
    }
    cout << '\n';
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