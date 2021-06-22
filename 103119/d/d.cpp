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

set<string> wanted;

void solveCase()
{
    wanted.insert("ATK");
    wanted.insert("ATK Rate");
    wanted.insert("Crit DMG Rate");
    wanted.insert("Crit Rate");
    string str;
    using ld = long double;
    vector<vector<pair<string, ld>>> options(5);
    ld atk = 0;
    ld atk_rate = 0;
    ld crit_dmg_rate = 50;
    ld crit_rate = 5;
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            getline(cin, str);
            auto it = str.find('+');
            int n = str.size();
            // db(str, it, n);
            auto pref = str.substr(0, it);
            auto suff = str.substr(it + 1);
            // db(pref, suff);
            if (suff.back() == '%')
                suff.pop_back();
            options[i].push_back({pref, stold(suff)});
            if (pref == "ATK")
                atk += stold(suff);
            else if (pref == "ATK Rate")
                atk_rate += stold(suff);
            else if (pref == "Crit DMG Rate")
                crit_dmg_rate += stold(suff);
            else if (pref == "Crit Rate")
                crit_rate += stold(suff);
        }
        db(i, options[i]);
    }
    ld ATK = 1500 * (1 + atk_rate / 100) + atk;
    crit_rate = min((ld)100, crit_rate);
    ll res = (ATK * (1 - crit_rate / 100) + ATK * (1 + crit_dmg_rate / 100) * crit_rate / 100);
    cout << fixed << setprecision(10) << res << '\n';
    return;
    // int den = 1;
    // ld num = 0;
    // function<void(int, ld, ld, ld, ld)> solve = [&](int idx, ld atk, ld atk_rate, ld crit_dmg_rate, ld crit_rate) -> void
    // {
    //     if (idx == 5)
    //     {
    //         ld ATK = 1500 * (1 + atk_rate / 100) + atk;
    //         num = max(num, ATK * (1 - crit_rate / 100) + ATK * (1 + crit_dmg_rate / 100) * crit_rate / 100);
    //         // den++;
    //         return;
    //     }
    //     solve(idx + 1, atk, atk_rate, crit_dmg_rate, crit_rate);
    //     for (auto &x : options[idx])
    //     {
    //         if (x.first == "ATK")
    //             solve(idx + 1, atk + x.second, atk_rate, crit_dmg_rate, crit_rate);
    //         else if (x.first == "ATK Rate")
    //             solve(idx + 1, atk, atk_rate + x.second, crit_dmg_rate, crit_rate);
    //         else if (x.first == "Crit DMG Rate")
    //             solve(idx + 1, atk, atk_rate, crit_dmg_rate + x.second, crit_rate);
    //         else if (x.first == "Crit Rate")
    //             solve(idx + 1, atk, atk_rate, crit_dmg_rate, min((ld)100, crit_rate + x.second));
    //         else
    //             solve(idx + 1, atk, atk_rate, crit_dmg_rate, crit_rate);
    //     }
    // };
    // solve(0, 0, 0, 50, 5);
    // db(num, den);
    // cout << fixed << setprecision(10) << num / den << '\n';
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