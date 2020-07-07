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

struct Trie
{
    int canWinForSure, canLoseForSure;
    vector<Trie *> child;
    Trie()
    {
        child.resize(26, nullptr);
        canWinForSure = canLoseForSure = -1;
    }
    void insert(string &s)
    {
        auto curr = this;
        for (auto &x : s)
        {
            if (curr->child[x - 'a'] == nullptr)
                curr->child[x - 'a'] = new Trie();
            curr = curr->child[x - 'a'];
        }
    }
    void dfs()
    {
        canWinForSure = canLoseForSure = false;
        for (auto &x : child)
        {
            if (x != nullptr)
            {
                x->dfs();
                canWinForSure = canWinForSure || (!(x->canWinForSure));
                canLoseForSure = canLoseForSure || (!(x->canLoseForSure));
            }
        }
        if (count(all(child), nullptr) == 26)
        {
            canWinForSure = false;
            canLoseForSure = true;
        }
    }
};

class Solution
{
private:
public:
    Solution() {}
    ~Solution() {}
    void solveCase()
    {
        int n, k;
        cin >> n >> k;
        Trie root;
        for (size_t i = 0; i < n; i++)
        {
            string s;
            cin >> s;
            root.insert(s);
        }
        root.dfs();
        // cout << root.canWinForSure << ' ' << root.canLoseForSure << '\n';
        db(root.canWinForSure, root.canLoseForSure);
        if (!root.canWinForSure)
            cout << "Second\n";
        else if (root.canLoseForSure)
            cout << "First\n";
        else if (k & 1)
            cout << "First\n";
        else
            cout << "Second\n";
    }
};

int32_t main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
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
