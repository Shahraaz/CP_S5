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
    int n, k;
    cin >> n >> k;
    string str;
    cin >> str;
    int max_uniq_cnt = n - k + 1;
    int bits_to_check = ceil(log2((max_uniq_cnt + 1) * 2)) + 2;
    bits_to_check = min(bits_to_check, k);
    db(n, k, str);
    db(max_uniq_cnt, bits_to_check);
    set<int> vis;
    int lptr = 0, rptr = 0;
    while (rptr < n)
    {
        while ((rptr - lptr + 1) > k)
            ++lptr;
        while (lptr < rptr && str[lptr] == '1')
            ++lptr;
        db(lptr, rptr);
        if ((rptr - lptr + 1) <= bits_to_check)
        {
            int curr = 0;
            for (size_t i = lptr; i <= rptr; i++)
                curr = curr * 2 + ('1' ^ '0' ^ str[i]) - '0';
            if (rptr >= k - 1)
            {
                vis.insert(curr);
                db(rptr, bitset<20>(curr));
            }
        }
        rptr++;
    }
    int res = 0;
    db(vis);
    for (size_t i = 0; i < (1 << bits_to_check); i++)
        if (vis.find(i) == vis.end())
        {
            string str;
            int i1 = i;
            while (i1)
            {
                str += (i1 & 1) + '0';
                i1 /= 2;
            }
            if (str.size() > k)
                continue;
            while (str.size() < k)
                str += '0';
            reverse(all(str));
            cout << "YES\n"
                 << str << '\n';
            return;
        }
    cout << "NO\n";
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