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
    if (n % k)
    {
        cout << -1 << '\n';
        return;
    }
    vector<int> cnt(26);
    for (auto &c : str)
        cnt[c - 'a']++;
    auto get = [&](char c) -> int
    {
        return (k - cnt[c - 'a'] % k) % k;
    };
    int sum = 0;
    for (size_t i = 0; i < 26; i++)
        sum += get('a' + i);
    if (sum == 0)
    {
        cout << str << '\n';
        return;
    }
    for (int i = n - 1; i >= 0; i--)
    {
        sum -= get(str[i]);
        cnt[str[i] - 'a']--;
        sum += get(str[i]);
        for (size_t j = str[i] - 'a' + 1; j < 26; j++)
        {
            sum -= get('a' + j);
            cnt[j]++;
            sum += get('a' + j);
            if (i + sum + 1 <= n)
            {
                cout << str.substr(0, i);
                cout << char(j + 'a');
                string en = "";
                for (size_t i = 0; i < 26; i++)
                {
                    int c = get('a' + i);
                    while (c--)
                        en += char('a' + i);
                }
                while (en.size() + i + 1 < n)
                    en += "a";
                sort(all(en));
                cout << en << '\n';
                return;
            }
            sum -= get('a' + j);
            cnt[j]--;
            sum += get('a' + j);
        }
    }
    assert(false);
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