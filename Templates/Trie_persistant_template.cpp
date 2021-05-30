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

struct StringTrie
{
    StringTrie *chi[26];
    int dat;
    StringTrie()
    {
        for (size_t i = 0; i < 26; i++)
            chi[i] = nullptr;
        dat = -1;
    }
    StringTrie(StringTrie *old)
    {
        for (size_t i = 0; i < 26; i++)
            chi[i] = old->chi[i];
        dat = old->dat;
    }
    StringTrie *set(string &s, int val, int pos = 0)
    {
        StringTrie *rt = new StringTrie(this);
        if (pos >= s.size())
            rt->dat = val;
        else
        {
            int v = s[pos] - 'a';
            if (!chi[v])
                chi[v] = new StringTrie();
            rt->chi[v] = chi[v]->set(s, val, pos + 1);
        }
        return rt;
    }
    int get(string &s, int pos = 0)
    {
        if (pos < s.size())
        {
            int v = s[pos] - 'a';
            if (!chi[v])
                return -1;
            return chi[v]->get(s, pos + 1);
        }
        return dat;
    }
};

struct BinaryTrie
{
    BinaryTrie *chi[2];
    int dat;
    BinaryTrie()
    {
        for (size_t i = 0; i < 2; i++)
            chi[i] = nullptr;
        dat = 0;
    }
    BinaryTrie(BinaryTrie *old)
    {
        for (size_t i = 0; i < 2; i++)
            chi[i] = old->chi[i];
        dat = old->dat;
    }
    BinaryTrie *add(int s, int val, int pos = 30)
    {
        BinaryTrie *rt = new BinaryTrie(this);
        rt->dat += val;
        if (pos >= 0)
        {
            int v = (s >> pos) & 1;
            if (!chi[v])
                chi[v] = new BinaryTrie();
            rt->chi[v] = chi[v]->add(s, val, pos - 1);
        }
        return rt;
    }
    int get(int &s, int pos = 30)
    {
        if (pos < 0)
            return 0;
        int v = (s >> pos) & 1;
        if (v)
        {
            int ans = 0;
            if (chi[0])
                ans += chi[0]->dat;
            if (chi[1])
                ans += chi[1]->get(s, pos - 1);
            return ans;
        }
        return chi[0] ? chi[0]->get(s, pos - 1) : 0;
    }
};

void solveCase()
{
    int q;
    cin >> q;
    StringTrie **st = new StringTrie *[q + 5];
    BinaryTrie **bt = new BinaryTrie *[q + 5];
    st[0] = new StringTrie();
    bt[0] = new BinaryTrie();
    for (int i = 1; i <= q; i++)
    {
        string op;
        cin >> op;
        if (op == "set")
        {
            string str;
            int val;
            cin >> str >> val;
            int x = st[i - 1]->get(str);
            st[i] = st[i - 1]->set(str, val);
            if (x >= 0)
            {
                bt[i] = bt[i - 1]->add(x, -1);
                bt[i] = bt[i]->add(val, 1);
            }
            else
                bt[i] = bt[i - 1]->add(val, 1);
        }
        else if (op == "remove")
        {
            string str;
            cin >> str;
            int x = st[i - 1]->get(str);
            st[i] = st[i - 1]->set(str, -1);
            if (x >= 0)
                bt[i] = bt[i - 1]->add(x, -1);
            else
                bt[i] = bt[i - 1];
        }
        else if (op == "undo")
        {
            int x;
            cin >> x;
            st[i] = st[i - x - 1];
            bt[i] = bt[i - x - 1];
        }
        else
        {
            st[i] = st[i - 1];
            bt[i] = bt[i - 1];
            string str;
            cin >> str;
            int x = st[i]->get(str);
            if (x >= 0)
                cout << bt[i]->get(x) << endl;
            else
                cout << -1 << endl;
        }
    }
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