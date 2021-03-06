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

int64_t solveCase(int n, const vector<int64_t> &a)
{
    // TODO: edit here
    int64_t ret = LLONG_MAX, curr = 0, sum = 0;
    int sgn = 1;
    for (size_t i = 0; i < n; i++)
    {
        sum += a[i];
        db(i, sum, a[i], sgn, curr);
        if (sum * sgn > 0)
        {
        }
        else
        {
            curr += abs(sgn - sum);
            db(abs(sgn - sum));
            sum = sgn;
            db(i, sum, curr);
        }
        sgn = -1 * sgn;
    }
    db(curr);
    ret = min(ret, curr);

    curr = 0, sum = 0;
    sgn = -1;
    for (size_t i = 0; i < n; i++)
    {
        sum += a[i];
        db(i, sum, a[i], sgn, curr);
        if (sum * sgn > 0)
        {
        }
        else
        {
            curr += abs(sgn - sum);
            db(abs(sgn - sum));
            sum = sgn;
            db(i, sum, curr);
        }
        sgn = -1 * sgn;
    }
    db(curr);
    ret = min(ret, curr);
    return ret;
}

// generated by oj-template v4.7.2 (https://github.com/online-judge-tools/template-generator)
int main()
{
#ifndef LOCAL
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    constexpr char endl = '\n';
    int n;
    cin >> n;
    vector<int64_t> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }
    auto ans = solveCase(n, a);
    cout << ans << endl;
    return 0;
}