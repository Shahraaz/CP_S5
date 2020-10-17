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
    string s;
    cin >> s;
    int n = s.size();
    int len[n];
    string res[n];

    deque<pair<char, int>> vecc;
    deque<char> next;
    string str;
    int currLen = 0;
    int ok = true;
    for (int i = n - 1; i >= 0; i--)
    {
        if (vecc.empty())
            next.push_front('0');
        else if (vecc[0].f == s[i])
        {
            auto prev = next.front();
            next.push_front(prev);
        }
        else
            next.push_front(vecc[0].f);

        vecc.push_front({s[i], i});
        currLen++;

        // db(i, vecc);
        if (vecc.size() > 1 && vecc[0].f == vecc[1].f && (vecc[0].s + 1) == vecc[1].s)
        {
            if (vecc.size() >= 3 && vecc[0].f <= next.front())
            {
            }
            else
            {
                vecc.pop_front();
                vecc.pop_front();
                next.pop_front();
                next.pop_front();
                currLen -= 2;
            }
        }

        db(i, vecc);
        len[i] = currLen;
        if (currLen <= 10)
        {
            for (auto &x : vecc)
                res[i] += x.f;
        }
        else
        {
            for (auto &x : vecc)
            {
                res[i] += x.f;
                if (res[i].size() == 5)
                    break;
            }
            string temp;
            for (int i = vecc.size() - 1; i >= 0; i--)
            {
                auto &x = vecc[i];
                temp += x.f;
                if (temp.size() == 2)
                    break;
            }
            reverse(all(temp));
            res[i] += "...";
            res[i] += temp;
        }
    }
    for (size_t i = 0; i < n; i++)
    {
        cout << len[i] << ' ' << res[i] << '\n';
    }
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
    {
        solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
