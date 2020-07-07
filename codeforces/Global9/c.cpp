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

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n;
        cin >> n;
        vector<int> a(n);
        for (size_t i = 0; i < n; i++)
            cin >> a[i];
        db(a);
        stack<int> st;
        vector<int> minPossible(n, -1);
        for (size_t i = 0; i < n; i++)
        {
            int x = a[i];
            // cin >> x;
            // v.pb(x);
            st.push(x);
            while (st.size() >= 2)
            {
                auto top1 = st.top();
                st.pop();
                auto top2 = st.top();
                st.pop();
                if (top1 < top2)
                    st.push(top1);
                else
                {
                    st.push(top2);
                    st.push(top1);
                    break;
                }
            }
            if (st.size() == 1)
                minPossible[i] = st.top();
        }
        vector<int> maxPossible(n, -1);
        // queue<int> st;
        while (st.size())
            st.pop();

        for (int i = n - 1; i >= 0; i--)
        {
            int x = a[i];
            // cin >> x;
            // v.pb(x);
            st.push(x);
            while (st.size() >= 2)
            {
                auto top1 = st.top();
                st.pop();
                auto top2 = st.top();
                st.pop();
                if (top1 < top2)
                    st.push(top2);
                else
                {
                    st.push(top2);
                    st.push(top1);
                    break;
                }
            }
            if (st.size() == 1)
                maxPossible[i] = st.top();
        }
        db(minPossible);
        db(maxPossible);
        for (int i = 0; i < n; i++)
        {
            // bool ok = true;
            if (i > 0)
            {
                if (minPossible[i - 1] != -1 && minPossible[i - 1] < maxPossible[i])
                {
                    db(i);
                    cout << "YES\n";
                    return;
                }
            }
            else
            {
                if (maxPossible[i] != -1)
                {
                    db(i);
                    cout << "YES\n";
                    return;
                }
            }
        }
        cout << "NO\n";
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    cin >> t;
    Solution mySolver;
    for (int i = 1; i <= t; ++i)
    {
        mySolver.solveCase();
#ifdef LOCAL
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}
