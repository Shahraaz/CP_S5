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
    int check, car;
    cin >> check >> car;
    vector<int> checkes(check);
    map<int, int> checkPoints;
    for (auto &x : checkes)
    {
        checkPoints[x]++;
        cin >> x;
    }
    vector<pair<int, int>> cars(car);
    for (auto &x : cars)
        cin >> x.first;
    for (auto &x : cars)
        cin >> x.second;
    sort(all(cars));
    map<int, int> carPoints;
    for (size_t i = 0; i + 1 < check; i++)
    {
        int fptr = checkes[i];
        int rptr = checkes[i + 1];
        auto st = lower_bound(all(cars), make_pair(fptr, -MOD)) - cars.begin();
        auto en = lower_bound(all(cars), make_pair(rptr, +MOD)) - cars.begin();
        vector<pair<int, int>> leftgoing, rigtgoing;
        for (size_t j = st; j < en; j++)
        {
            int xcord = cars[j].first;
            if (checkPoints.find(xcord) != checkPoints.end())
                continue;
            if (carPoints[xcord]++)
            {
                cout << "NO\n";
                return;
            }

            if (cars[j].second < 0) // going left
            {
                if (rigtgoing.size())
                {
                    cout << "NO\n";
                    return;
                }
                leftgoing.pb({abs(fptr - xcord), abs(cars[j].second)});
            }
            else
            {
                rigtgoing.pb({abs(rptr - xcord), abs(cars[j].second)});
            }
        }
        for (size_t i = 0; i + 1 < leftgoing.size(); i++)
        {
            if (leftgoing[i].first * 1LL * leftgoing[i + 1].second <= leftgoing[i + 1].first * 1LL * leftgoing[i].second)
                ;
            else
            {
                cout << "NO\n";
                return;
            }
        }
        for (size_t i = 0; i + 1 < rigtgoing.size(); i++)
        {
            if (rigtgoing[i].first * 1LL * rigtgoing[i + 1].second >= rigtgoing[i + 1].first * 1LL * rigtgoing[i].second)
                ;
            else
            {
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";
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