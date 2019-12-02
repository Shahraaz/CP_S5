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

struct MyStack
{
    int cnt = 0, allOpens = 0;
    deque<int> s, minValue, maxValue;
    void push(int x)
    {
        s.push_back(x);
        cnt += x;
        if (x == 1)
            allOpens++;
        minValue.push_back(minValue.size() ? min(minValue.back(), cnt) : cnt);
        maxValue.push_back(maxValue.size() ? max(maxValue.back(), cnt) : cnt);
    }
    void pop()
    {
        if (s.size() == 0)
            return;
        cnt -= s.back();
        if (s.back() == 1)
            allOpens--;
        s.pop_back();
        minValue.pop_back();
        maxValue.pop_back();
    }
    int top()
    {
        return s.back();
    }
    bool isCorrect()
    {
        return (minValue.size() == 0) || (minValue.back() >= 0);
    }
    int depth()
    {
        return (maxValue.size() ? maxValue.back() : 0);
    }
};

ostream &operator<<(ostream &out, MyStack p)
{
    out << "cnt " << p.cnt << " allOpens " << p.allOpens << '\n';
    out << "s {";
    for (auto elem : p.s)
        out << elem << ' ';
    out << "}\n";
    out << "Minvalue {";
    for (auto elem : p.minValue)
        out << elem << ' ';
    out << "}\n";
    out << "Maxvalue {";
    for (auto elem : p.maxValue)
        out << elem << ' ';
    out << "}\n";
    return out;
}

void solveCase(int caseNo)
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    MyStack left, right;
    for (int i = 0; i < n; ++i)
        right.push(0);
    left.push(0);
    int pos = 0;
    for (int i = 0; i < n; ++i)
    {
        switch (s[i])
        {
        case 'L':
            if (pos > 0)
            {
                pos--;
                right.push(-left.top());
                left.pop();
            }
            break;
        case 'R':
            pos++;
            left.push(-right.top());
            right.pop();
            break;
        case '(':
            left.pop();
            left.push(1);
            break;
        case ')':
            left.pop();
            left.push(-1);
            break;
        default:
            left.pop();
            left.push(0);
            break;
        }
        db(s[i]);
        db(left, right);
        if (left.isCorrect() && right.isCorrect() && (left.cnt == right.cnt))
            cout << max({left.depth(), right.depth(), left.cnt}) << ' ';
        else
            cout << "-1 ";
        // cout << '\n';
    }
    cout << '\n';
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