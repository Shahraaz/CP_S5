//Optimise
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// #define MULTI_TEST
#ifdef LOCAL
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__);
#define pc(...) PC(#__VA_ARGS__, __VA_ARGS__);
template <typename T, typename U>
ostream &operator<<(ostream &out, const pair<T, U> &p)
{
    out << '[' << p.first << ", " << p.second << ']';
    return out;
}
template <typename Arg>
void PC(const char *name, Arg &&arg)
{
    while (*name == ',' || *name == ' ')
        name++;
    std::cerr << name << " { ";
    for (const auto &v : arg)
        cerr << v << ' ';
    cerr << " }\n";
}
template <typename Arg1, typename... Args>
void PC(const char *names, Arg1 &&arg1, Args &&... args)
{
    while (*names == ',' || *names == ' ')
        names++;
    const char *comma = strchr(names, ',');
    std::cerr.write(names, comma - names) << " { ";
    for (const auto &v : arg1)
        cerr << v << ' ';
    cerr << " }\n";
    PC(comma, args...);
}
template <typename Arg1>
void ZZ(const char *name, Arg1 &&arg1)
{
    std::cerr << name << " = " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void ZZ(const char *names, Arg1 &&arg1, Args &&... args)
{
    const char *comma = strchr(names + 1, ',');
    std::cerr.write(names, comma - names) << " = " << arg1;
    ZZ(comma, args...);
}
#else
#define db(...)
#define pc(...)
#endif

using ll = long long;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define f first
#define s second
#define pb push_back
auto TimeStart = chrono::steady_clock::now();

const int NAX = 2e5 + 10, MOD = 1000000007;

class Trie_Node
{
private:
    vector<Trie_Node *> child;

public:
    bool win, lose;
    Trie_Node(/* args */)
    {
        child.resize(26, nullptr);
        win = lose = false;
    }
    void insert(string s)
    {
        Trie_Node *curr = this;
        int len = s.length();
        for (int i = 0; i < len; ++i)
        {
            int c = s[i] - 'a';
            if (curr->child[c] == nullptr)
                curr->child[c] = new Trie_Node;
            curr = curr->child[c];
        }
    }
    void dfs()
    {
        bool isLeaf = true;
        for (auto child_Node : child)
            if (child_Node != nullptr)
            {
                isLeaf = false;
                child_Node->dfs();
                win |= !(child_Node->win);
                lose |= !(child_Node->lose);
            }
        if (isLeaf)
            lose = true;
    }
};

void answer(bool b)
{
    cout << (b?"First":"Second");
}

void solveCase(int caseNo)
{
    int n, k;
    cin >> n >> k;
    Trie_Node root;
    string s;
    for (int i = 0; i < n; ++i)
    {
        cin >> s;
        root.insert(s);
    }
    root.dfs();
    if (k == 1)
        answer(root.win);
    else if (!root.win)
        answer(root.win);
    else if (root.lose)
        answer(root.win);
    else if (k & 1)
        answer(root.win);
    else
        answer(!root.win);
}

int main()
{
#ifndef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t = 1;
#ifdef MULTI_TEST
    cin >> t;
#endif
    for (int i = 1; i <= t; ++i)
    {
        solveCase(i);
#ifdef TIME
        cerr << "Case #" << i << ": Time " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " s.\n";
        TimeStart = chrono::steady_clock::now();
#endif
    }
    return 0;
}