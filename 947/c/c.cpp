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

const int LIM = 32;

class Trie_Node
{
private:
    vector<Trie_Node *> child;
    int cnt;

public:
    Trie_Node(/* args */)
    {
        cnt = 0;
        child.resize(2, nullptr);
    }
    void insert(int s)
    {
        Trie_Node *curr = this;
        for (int i = LIM - 1; i >= 0; i--)
        {
            curr->cnt++;
            int c = (s >> i) & 1;
            if (curr->child[c] == nullptr)
                curr->child[c] = new Trie_Node;
            curr = curr->child[c];
        }
        curr->cnt++;
    }
    void erase(int s)
    {
        Trie_Node *curr = this;
        for (int i = LIM - 1; i >= 0; i--)
        {
            curr->cnt--;
            int c = (s >> i) & 1;
            assert(curr->child[c] != nullptr);
            assert(curr->child[c]->cnt);
            // if (curr->child[c] == nullptr)
            //     curr->child[c] = new Trie_Node;
            curr = curr->child[c];
        }
        curr->cnt--;
    }
    int find(int s)
    {
        Trie_Node *curr = this;
        int res = 0;
        db("find", s);
        for (int i = LIM - 1; i >= 0; i--)
        {
            db(s, i, curr->cnt, res);
            if (curr->child[0] != nullptr)
            {
                db(curr->child[0], curr->child[0]->cnt);
            }
            if (curr->child[1] != nullptr)
            {
                db(curr->child[1], curr->child[1]->cnt);
            }
            // curr->cnt--;
            int c = (s >> i) & 1;
            if (curr->child[c] != nullptr && curr->child[c]->cnt)
            {
                res = res * 2 + c;
                assert(curr->child[c] != nullptr);
                assert(curr->child[c]->cnt);
                curr = curr->child[c];
            }
            else
            {
                c = 1 - c;
                res = res * 2 + c;
                assert(curr->child[c] != nullptr);
                assert(curr->child[c]->cnt);
                curr = curr->child[c];
            }
        }
        // curr->cnt--;
        return res;
    }
};

void solveCase()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a)
    {
        cin >> x;
    }
    Trie_Node t;
    for (size_t i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        t.insert(k);
    }
    for (auto &x : a)
    {
        auto res = t.find(x);
        cout << (res ^ x) << ' ';
        t.erase(res);
    }
    cout << '\n';
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