// Optimise
#include <bits/stdc++.h>
using namespace std;

struct SuffixTree
{
    enum
    {
        N = 200010,
        ALPHA = 26
    }; // N ∼ 2∗maxlen+10
    int toi(char c) { return c - 'a'; }
    string a; // v = cur node , q = cur position
    int t[N][ALPHA], l[N], r[N], p[N], s[N], v = 0, q = 0, m = 2;
    void ukkadd(int i, int c)
    {
    suff:
        if (r[v] <= q)
        {
            if (t[v][c] == -1)
            {
                t[v][c] = m;
                l[m] = i;
                p[m++] = v;
                v = s[v];
                q = r[v];
                goto suff;
            }
            v = t[v][c];
            q = l[v];
        }
        if (q == -1 || c == toi(a[q]))
            q++;
        else
        {
            l[m + 1] = i;
            p[m + 1] = m;
            l[m] = l[v];
            r[m] = q;
            p[m] = p[v];
            t[m][c] = m + 1;
            t[m][toi(a[q])] = v;
            l[v] = q;
            p[v] = m;
            t[p[m]][toi(a[l[m]])] = m;
            v = s[p[m]];
            q = l[m];
            while (q < r[m])
            {
                v = t[v][toi(a[q])];
                q += r[v] - l[v];
            }
            if (q == r[m])
                s[m] = v;
            else
                s[m] = m + 2;
            q = r[v] - (q - r[m]);
            m += 2;
            goto suff;
        }
    }
    SuffixTree(string a) : a(a)
    {
        fill(r, r + N, a.size());
        memset(s, 0, sizeof s);
        memset(t, -1, sizeof t);
        fill(t[1], t[1] + ALPHA, 0);
        m = 2;
        q = 0;
        v = 0;
        s[0] = 1;
        l[0] = l[1] = -1;
        r[0] = r[1] = p[0] = p[1] = 0;
        for (size_t i = 0; i < a.size(); i++)
            ukkadd(i, toi(a[i]));
    }
    // example : find longest common substring ( uses ALPHA = 28)
    pair<int, int> best;
    int lcs(int node, int i1, int i2, int olen)
    {
        if (l[node] <= i1 && i1 < r[node])
            return 1;
        if (l[node] <= i2 && i2 < r[node])
            return 2;
        int mask = 0, len = node ? olen + (r[node] - l[node]) : 0;
        for (size_t c = 0; c < ALPHA; c++)
            if (t[node][c] != -1)
                mask |= lcs(t[node][c], i1, i2, len);
        if (mask == 3)
            best = max(best, {len, r[node] - len});
        return mask;
    }
    static pair<int, int> LCS(string s, string t)
    {
        SuffixTree st(s + (char)('z' + 1) + t + (char)('z' + 2));
        st.lcs(0, (s).size(), s.size() + 1 + t.size(), 0);
        return st.best;
    }
};

///////////////////////////////////////////////////////////////////////////////////

struct SuffixTree
{
    enum
    {
        N = 200010,
        ALPHA = 26
    }; // N ∼ 2∗maxlen+10
    int toi(char c) { return c; }
    string a; // v = cur node , q = cur position
    map<char, int> t[N];
    int l[N], r[N], p[N], s[N], v = 0, q = 0, m = 2;
    void ukkadd(int i, int c)
    {
    suff:
        if (r[v] <= q)
        {
            if (t[v].find(c) == t[v].end())
            {
                t[v][c] = m;
                l[m] = i;
                p[m++] = v;
                v = s[v];
                q = r[v];
                goto suff;
            }
            v = t[v][c];
            q = l[v];
        }
        if (q == -1 || c == a[q])
            q++;
        else
        {
            l[m + 1] = i;
            p[m + 1] = m;
            l[m] = l[v];
            r[m] = q;
            p[m] = p[v];
            t[m][c] = m + 1;
            t[m][a[q]] = v;
            l[v] = q;
            p[v] = m;
            t[p[m]][a[l[m]]] = m;
            v = s[p[m]];
            q = l[m];
            while (q < r[m])
            {
                v = t[v][a[q]];
                q += r[v] - l[v];
            }
            if (q == r[m])
                s[m] = v;
            else
                s[m] = m + 2;
            q = r[v] - (q - r[m]);
            m += 2;
            goto suff;
        }
    }
    SuffixTree(string a) : a(a)
    {
        fill(r, r + N, a.size());
        memset(s, 0, sizeof s);
        // memset(t, -1, sizeof t);
        // fill(t[1], t[1] + ALPHA, 0);
        for (char c = 0; c < 127; c++)
            t[1][c] = 0;
        m = 2;
        q = 0;
        v = 0;
        s[0] = 1;
        l[0] = l[1] = -1;
        r[0] = r[1] = p[0] = p[1] = 0;
        for (size_t i = 0; i < a.size(); i++)
            ukkadd(i, a[i]);
#ifdef LOCAL
        for (size_t i = 0; i <= 2 * a.size() + 1; i++)
        {
            if (i == 1)
                continue;
            db(i, l[i], r[i], s[i], p[i]);
            for (size_t j = 0; j < 127; j++)
                if (t[i].find(j) != t[i].end())
                {
                    // if (j < 26)
                    cout << char(j) << ": " << t[i][j] << ' ';
                    //     else
                    //         cout << '$' << ": " << t[i][j] << ' ';
                }
            cout << '\n';
        }
#endif
    }
    // example : find longest common substring ( uses ALPHA = 28)
    pair<int, int> best;
    int lcs(int node, int i1, int i2, int olen)
    {
        if (l[node] <= i1 && i1 < r[node])
            return 1;
        if (l[node] <= i2 && i2 < r[node])
            return 2;
        int mask = 0, len = node ? olen + (r[node] - l[node]) : 0;
        for (size_t c = 0; c < ALPHA; c++)
            if (t[node][c] != -1)
                mask |= lcs(t[node][c], i1, i2, len);
        if (mask == 3)
            best = max(best, {len, r[node] - len});
        return mask;
    }
    static pair<int, int> LCS(string s, string t)
    {
        SuffixTree st(s + (char)('z' + 1) + t + (char)('z' + 2));
        st.lcs(0, (s).size(), s.size() + 1 + t.size(), 0);
        return st.best;
    }
    bool find(string pattern)
    {
        auto node = 0;
        int ptr = 0;
        int len = 0;
        while (ptr < pattern.size())
        {
            db(node, ptr, l[node], r[node], len);
            if (ptr < r[node])
            {
                if (a[l[node] + len] == pattern[ptr])
                {
                    ++ptr;
                    ++len;
                }
                else
                {
                    return false;
                }
            }
            else if (t[node].find(pattern[ptr]) == t[node].end())
            {
                return false;
            }
            else
            {
                node = t[node][pattern[ptr]];
                len = 1;
                ++ptr;
            }
        }
        return ptr == pattern.size();
    }
};

//////////////////////////////////////////////////////////////////////////

const int N = 1000000,           // maximum possible number of nodes in suffix tree
    INF = 1000000000;            // infinity constant
string a;                        // input string for which the suffix tree is being built
int t[N][26],                    // array of transitions (state, letter)
    l[N],                        // left...
    r[N],                        // ...and right boundaries of the substring of a which correspond to incoming edge
    p[N],                        // parent of the node
    suffixLink[N],               // suffix link
    nodeOfCurrentSuffix,         // the node of the current suffix (if we're mid-edge, the lower node of the edge)
    positionOnString,            // position in the string which corresponds to the position on the edge (between l[nodeOfCurrentSuffix] and r[nodeOfCurrentSuffix], inclusive)
    numberOfNodes,               // the number of nodes
    currentCharecterInTheString; // the current character in the string

void ukkadd(int c)
{      // add character s to the tree
suff:; // we'll return here after each transition to the suffix (and will add character again)
    if (r[nodeOfCurrentSuffix] < positionOnString)
    { // check whether we're still within the boundaries of the current edge
        // if we're not, find the next edge. If it doesn't exist, create a leaf and add it to the tree
        if (t[nodeOfCurrentSuffix][c] == -1)
        {
            t[nodeOfCurrentSuffix][c] = numberOfNodes;
            l[numberOfNodes] = currentCharecterInTheString;
            p[numberOfNodes++] = nodeOfCurrentSuffix;
            nodeOfCurrentSuffix = suffixLink[nodeOfCurrentSuffix];
            positionOnString = r[nodeOfCurrentSuffix] + 1;
            goto suff;
        }
        nodeOfCurrentSuffix = t[nodeOfCurrentSuffix][c];
        positionOnString = l[nodeOfCurrentSuffix];
    } // otherwise just proceed to the next edge
    if (positionOnString == -1 || c == a[positionOnString] - 'a')
        positionOnString++; // if the letter on the edge equal c, go down that edge
    else
    {
        // otherwise split the edge in two with middle in node numberOfNodes
        l[numberOfNodes] = l[nodeOfCurrentSuffix];
        r[numberOfNodes] = positionOnString - 1;
        p[numberOfNodes] = p[nodeOfCurrentSuffix];
        t[numberOfNodes][a[positionOnString] - 'a'] = nodeOfCurrentSuffix;
        // add leaf numberOfNodes+1. It corresponds to transition through c.
        t[numberOfNodes][c] = numberOfNodes + 1;
        l[numberOfNodes + 1] = currentCharecterInTheString;
        p[numberOfNodes + 1] = numberOfNodes;
        // update info for the current node - remember to mark numberOfNodes as parent of tv
        l[nodeOfCurrentSuffix] = positionOnString;
        p[nodeOfCurrentSuffix] = numberOfNodes;
        t[p[numberOfNodes]][a[l[numberOfNodes]] - 'a'] = numberOfNodes;
        numberOfNodes += 2;
        // prepare for descent
        // positionOnString will mark where are we in the current suffix
        nodeOfCurrentSuffix = suffixLink[p[numberOfNodes - 2]];
        positionOnString = l[numberOfNodes - 2];
        // while the current suffix is not over, descend
        while (positionOnString <= r[numberOfNodes - 2])
        {
            nodeOfCurrentSuffix = t[nodeOfCurrentSuffix][a[positionOnString] - 'a'];
            positionOnString += r[nodeOfCurrentSuffix] - l[nodeOfCurrentSuffix] + 1;
        }
        // if we're in a node, add a suffix link to it, otherwise add the link to numberOfNodes
        // (we'll create numberOfNodes on next iteration).
        if (positionOnString == r[numberOfNodes - 2] + 1)
            suffixLink[numberOfNodes - 2] = nodeOfCurrentSuffix;
        else
            suffixLink[numberOfNodes - 2] = numberOfNodes;
        // add positionOnString to the new edge and return to add letter to suffix
        positionOnString = r[nodeOfCurrentSuffix] - (positionOnString - r[numberOfNodes - 2]) + 2;
        goto suff;
    }
}

void build()
{
    fill(r, r + N, (int)a.size() - 1);
    memset(t, -1, sizeof t);
    fill(t[1], t[1] + 26, 0);
    numberOfNodes = 2;
    nodeOfCurrentSuffix = 0;
    positionOnString = 0;
    // initialize data for the root of the tree
    suffixLink[0] = 1;
    l[0] = r[0] = -1;
    l[1] = r[1] = -1;
    // add the text to the tree, letter by letter
    for (currentCharecterInTheString = 0; currentCharecterInTheString < (int)a.size(); ++currentCharecterInTheString)
        ukkadd(a[currentCharecterInTheString] - 'a');
}
