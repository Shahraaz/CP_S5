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

const int NAX = 2e6 + 10, MOD = 1000000007;

vector<int> Tree(2 * NAX), a(2 * NAX), b(2 * NAX);

void update(int node, int left, int right, int pos, char ch)
{
    if (left == right)
    {
        switch (ch)
        {
        case '(':
            a[node] = 1;
            b[node] = 0;
            Tree[node] = 0;
            break;
        case ')':
            a[node] = 0;
            b[node] = 1;
            Tree[node] = 0;
            break;
        default:
            a[node] = 0;
            b[node] = 0;
            Tree[node] = 0;
            break;
        }
        return;
    }
    int mid = (left + right) / 2;
    if (pos <= mid)
        update(2 * node, left, mid, pos, ch);
    else
        update(2 * node + 1, mid + 1, right, pos, ch);
    Tree[node] = 
}

void solveCase(int caseNo)
{
    int curr = 0, n;
    cin >> n;
    vector<char> str(NAX);
    for (int i = 0; i < n; ++i)
    {
        char ch;
        cin >> ch;
        if (ch == 'R')
            curr++;
        else if (ch == 'L')
        {
            if (curr == 0)
                continue;
            else
                curr--;
        }
        else
        {
            if (ch == '(')
            {
            }
            else if (ch == ')')
            {
            }
            else
            {
            }
        }
    }
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
    for (int i = 0; i < t; ++i)
        solveCase(i);
#ifdef TIME
    cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
    return 0;
}