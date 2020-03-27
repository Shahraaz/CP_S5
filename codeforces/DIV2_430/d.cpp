#include <iostream>
#include <iomanip>
#include <cstdio>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <ctime>
#include <cassert>
#include <algorithm>
#include <cmath>

//#include <unordered_set>
//#include <unordered_map>

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define for1(i, n) for (int i = 1; i < int(n); i++)
#define forft(i, from, to) for (int i = int(from); i < int(to); i++)
#define forr(i, n) for (int i = int(n) - 1; i >= 0; i--)
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define sz(a) int(a.size())
#define all(a) a.begin(), a.end()
#define ms(a, v) memset(a, v, sizeof(a))
#define correct(x, y, n, m) (x >= 0 && x < n && y >= 0 && y < m)

using namespace std;

template<typename T> T sqr(const T &x) {
    return x * x;
}

typedef long long ll;
typedef long long li;
typedef pair<int, int> pt;
typedef long double ld;
typedef pair<ld, ld> pd;

const int INF = int(1e9);
const ll INF_LL = ll(4e18);
const ll INF64 = ll(4e18);
const ll LINF = ll(4e18);
const ld EPS = 1e-9;
const ld PI = 3.14159265358979323846264338;

const int N = 3e5 + 10;
const int M = 20;

int n, m;
int a[N];

struct node {
    int nxt[2];
    int d;

    node() {
        nxt[0] = -1;
        nxt[1] = -1;
        d = 0;
    }
};

node t[N * M];
int len = 1;

bool read() {
    scanf("%d%d", &n, &m);

    forn(i, n) {
        scanf("%d", &a[i]);
    }

    return true;
}

void add(int v, int num, int pos) {
    if (pos < 0) {
        t[v].d = 1;
        return;
    }

    int nxt = ((num >> pos) & 1);

    if (t[v].nxt[nxt] == -1) {
        t[v].nxt[nxt] = len++;
    }

    add(t[v].nxt[nxt], num, pos - 1);
    t[v].d = 0;
    
    if (t[v].nxt[0] != -1) {
        t[v].d += t[t[v].nxt[0]].d;
    }
    
    if (t[v].nxt[1] != -1) {
        t[v].d += t[t[v].nxt[1]].d;
    }
}

void get(int v, int num, int pos, int &ans) {
    if (v == -1) {
        return;
    }

    int nxt = ((num >> pos) & 1);

    if (t[t[v].nxt[nxt]].d == (1 << pos)) {        
        nxt = 1 - nxt;
    }

    ans |= ((nxt ^ ((num >> pos) & 1)) << pos);
    get(t[v].nxt[nxt], num, pos - 1, ans);
}

void solve() {
    forn(i, n) {
        add(0, a[i], M - 1);
    }

    int c = 0;

    forn(i, m) {
        int k;
        scanf("%d", &k);
        c ^= k;

        int ans = 0;
        get(0, c, M - 1, ans);
        printf("%d\n", ans);
    }
}

int main() {
    srand((int) time(NULL));
    cout << setprecision(10) << fixed;
    
    read();
    solve();

    cerr << clock() << endl;

    return 0;
}