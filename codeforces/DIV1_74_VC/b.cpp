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

#define int ll

const int NAX = 2e5 + 5, MOD = 1000000007;

struct Solution
{
    Solution() {}
    void solveCase();
};

const int HBox = 0, VBox = 1, Widget = 2;

struct My_widget
{
    int curr_type;
    int border, spacing;
    int w, h;
    My_widget(int type, int w = 0, int h = 0)
    {
        this->curr_type = type;
        border = spacing = 0;
        this->w = w;
        this->h = h;
    }
    void set_border(int x)
    {
        this->border = x;
    }
    void set_spacing(int x)
    {
        this->spacing = x;
    }
};

ostream &operator<<(ostream &out, const My_widget &w)
{
    if (w.curr_type == HBox)
        out << "HBox ";
    else if (w.curr_type == VBox)
        out << "VBox ";
    else
        out << "Widger ";
    out << w.w << ' ' << w.h << ' ' << w.border << ' ' << w.spacing << '\n';
    return out;
}

vector<My_widget> my_widget;
vector<int> adj[NAX];
int degree[NAX];

vector<int> make_int_list(string t)
{
    int num = -1;
    vector<int> ret;
    for (auto &x : t)
    {
        if ('0' <= x && x <= '9')
        {
            if (num == -1)
                num = x - '0';
            else
                num = num * 10 + x - '0';
        }
        else
        {
            if (num != -1)
                ret.pb(num);
            num = -1;
        }
    }
    if (num != -1)
        ret.pb(num);
    else
        num = -1;
    // db(t, ret);
    return ret;
}

ll width[NAX], height[NAX];

void dfs(int node, int par)
{
    for (auto &x : adj[node])
    {
        if (x == par)
            continue;
        dfs(x, node);
        if (my_widget[node].curr_type == Widget)
        {
            exit(1);
        }
        else if (my_widget[node].curr_type == HBox)
        {
            height[node] = max(height[node], height[x]);
            width[node] += width[x];
        }
        else
        {
            width[node] = max(width[node], width[x]);
            height[node] += height[x];
        }
    }
    if (my_widget[node].curr_type == Widget)
    {
        width[node] = my_widget[node].w;
        height[node] = my_widget[node].h;
    }
    else if (my_widget[node].curr_type == HBox)
    {
        if (adj[node].size())
            width[node] += my_widget[node].spacing * (adj[node].size() - 1LL);
    }
    else
    {
        if (adj[node].size())
            height[node] += my_widget[node].spacing * (adj[node].size() - 1LL);
    }
    height[node] += my_widget[node].border * 2;
    width[node] += my_widget[node].border * 2;
}

void Solution::solveCase()
{
    int n;
    cin >> n;
    vector<string> name_from_idx;
    map<string, int> idx_from_name;
    string str;
    cin.ignore();
    while (getline(cin, str))
    {
        // db(str);
        // stringstream sin(str);
        vector<string> expression;
        if (count(all(str), ' '))
        {
            auto it = find(all(str), ' ') - str.begin();
            expression.pb(str.substr(0, it));
            expression.pb(str.substr(it + 1));
        }
        else
            expression.pb(str);
        // db(expression.size(), expression);
        if (expression.size() == 0)
            continue;
        if (expression.size() == 1)
        {
            auto it = find(all(expression[0]), '.');
            auto identifier = expression[0].substr(0, it - expression[0].begin());
            // db(identifier);
            auto intermediate = expression[0].substr(it - expression[0].begin() + 1);
            // db(intermediate);
            it = find(all(intermediate), '(');
            auto operation = intermediate.substr(0, it - intermediate.begin());
            // db(operation);
            auto params = intermediate.substr(it - intermediate.begin());
            // db(identifier, operation, params);
            auto idxx = idx_from_name[identifier];
            if (operation == "set_border")
                my_widget[idxx].set_border(make_int_list(params)[0]);
            else if (operation == "set_spacing")
                my_widget[idxx].set_spacing(make_int_list(params)[0]);
            else if (operation == "pack")
            {
                params = params.substr(1);
                params.pop_back();
                db(params);
                // degree[idxx]++;
                adj[idx_from_name[params]].pb(idxx);
            }
        }
        else
        {
            auto type = expression[0];
            auto identifier = expression[1];
            auto it = find(all(identifier), '(');
            // auto operation = identifier.substr(0, it - identifier.begin());
            // db(operation);
            auto params = identifier.substr(it - identifier.begin());
            // db(type, operation, params)
            auto numer_params = make_int_list(params);
            if (type[0] == 'W')
                my_widget.pb(My_widget(Widget, numer_params[0], numer_params[1]));
            else if (type[0] == 'H')
                my_widget.pb(My_widget(HBox));
            else
                my_widget.pb(My_widget(VBox));
            // identifier.substr(0, find(all(identifier), '(') - identifier.begin());
            string temp = "";
            for (auto &x : identifier)
            {
                if (x == '(')
                    break;
                temp += x;
            }
            identifier = temp;
            db(identifier, params, numer_params);
            idx_from_name[identifier] = name_from_idx.size();
            name_from_idx.pb(identifier);
        }
    }
    db(idx_from_name);
    db(name_from_idx);
    db(my_widget);
    queue<int> Q;
    vector<int> degree2(n);
    for (size_t i = 0; i < my_widget.size(); i++)
    {
        // sort(all(adj[i]));
        // adj[i].erase(unique(all(adj[i])), adj[i].end());
        // db(i, adj[i]);
        for (auto &x : adj[i])
        {
            degree[x]++;
            degree2[x]++;
        }
        // degree[i] = adj[i].size();
        // if (degree[i] == 0)
        //     Q.push(i);
    }
    for (size_t i = 0; i < my_widget.size(); i++)
    {
        db(i, degree[i]);
        if (degree[i] == 0)
            Q.push(i);
    }
    while (Q.size())
    {
        auto top = Q.front();
        Q.pop();
        db(top, name_from_idx[top], width[top], height[top]);
        if (my_widget[top].curr_type == Widget)
        {
            width[top] = my_widget[top].w;
            height[top] = my_widget[top].h;
        }
        else if (my_widget[top].curr_type == HBox)
        {
            if (degree2[top])
                width[top] += my_widget[top].spacing * (degree2[top] - 1LL);
        }
        else
        {
            if (degree2[top])
                height[top] += my_widget[top].spacing * (degree2[top] - 1LL);
        }
        if (degree2[top])
        {
            height[top] += my_widget[top].border * 2;
            width[top] += my_widget[top].border * 2;
        }
        db(top, name_from_idx[top], width[top], height[top]);
        for (auto &x : adj[top])
        {
            degree[x]--;
            if (degree[x] == 0)
                Q.push(x);
            if (my_widget[x].curr_type == Widget)
            {
                exit(1);
            }
            else if (my_widget[x].curr_type == HBox)
            {
                height[x] = max(height[x], height[top]);
                width[x] += width[top];
            }
            else
            {
                width[x] = max(width[x], width[top]);
                height[x] += height[top];
            }
        }
    }
    // dfs(i, i);
    db("---");
    for (auto &x : idx_from_name)
    {
        cout << x.f << ' ' << width[x.s] << ' ' << height[x.s] << '\n';
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
