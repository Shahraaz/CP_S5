#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

#define ff first

#define ss second

#define int long long

#define pb push_back

#define mp make_pair

#define pii pair<int, int>

#define vi vector<int>

#define mii map<int, int>

#define pqb priority_queue<int>

#define pqs priority_queue<int, vi, greater<int>>

#define setbits(x) __builtin_popcountll(x)

#define zrobits(x) __builtin_ctzll(x)

#define mod 1000000007

#define inf 1e18

#define ps(x, y) fixed << setprecision(y) << x

#define mk(arr, n, type) type *arr = new type[n];

#define w(x)  \
    int x;    \
    cin >> x; \
    while (x--)

#define FIO                       \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;

int get(string &s)
{
    int n = s.length();

    vi pre(n + 2, inf);
    vi suf(n + 2, inf);
    vi cnt(n + 1, 0);

    for (int i = 1; i <= n; ++i)
    {
        cnt[i] = cnt[i - 1];

        if (s[i - 1] == '(')
            cnt[i]++;
        else
            cnt[i]--;
    }

    for (int i = 1; i <= n; ++i)
        pre[i] = min(pre[i - 1], cnt[i]);

    for (int i = n; i >= 1; --i)
        suf[i] = min(suf[i + 1], cnt[i]);

    int ans = 0;

    for (int i = 1; i <= n; ++i)
    {
        bool c1 = (suf[i] >= cnt[i - 1]);
        bool c2 = (pre[i - 1] >= -cnt[n]);

        if (c1 & c2)
            ans++;
    }

    return ans;
}

int32_t main()
{
    FIO;
    int n;
    cin >> n;
    string s;
    cin >> s;
    int cnt = 0;

    for (char ch : s)
        if (ch == '(')
            cnt++;
        else
            cnt--;

    if (cnt)
    {
        cout << 0 << '\n';
        cout << 1 << ' ' << 1 << '\n';
        return 0;
    }

    int mx = get(s);
    pii ids = {1, 1};

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (s[i] == s[j])
                continue;

            swap(s[i], s[j]);

            int cur = get(s);

            if (cur >= mx)
                mx = cur, ids = {i + 1, j + 1};

            swap(s[i], s[j]);
        }
    }

    cout << mx << '\n'
         << ids.ff << ' ' << ids.ss << '\n';

    return 0;
}