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

int a[NAX];
int freq[101];
int maxr[101];

void solveCase()
{
    int n;
    cin >> n;
    for (size_t i = 0; i < n; ++i)
    {
        cin >> a[i];
        ++freq[a[i]];
    }
    auto maxfreq = *max_element(freq, freq + 101);
    if (count(freq, freq + 101, maxfreq) > 1)
    {
        cout << n << '\n';
        return;
    }
    int maxlen = 0;
    int maxidx = max_element(freq, freq + 101) - freq;
    for (size_t i = 1; i < 101; ++i)
    {
        if (i == maxidx)
            continue;
        memset(maxr, -1, sizeof maxr);
        int cnt = 0;
        for (int j = n - 1; j >= 0; --j)
        {
            auto it = maxr[cnt];
            if (it != -1)
                maxlen = max(maxlen, it - j);
            else
                maxr[cnt] = j;
            if (a[j] == maxidx)
                ++cnt;
            else if (a[j] == i)
                --cnt;
        }
        db(i, maxr);
        auto it = maxr[cnt];
        if (it != -1)
            maxlen = max(maxlen, it + 1);
    }
    cout << maxlen << '\n';
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