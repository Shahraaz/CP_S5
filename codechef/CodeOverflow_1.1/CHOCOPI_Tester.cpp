/*
Problem Name: Pick Chocolates
Problem Code: CHOCOPI
Problem Link: https://www.codechef.com/COFW2020/problems/CHOCOPI

Author Name: Mohammed Shahraaz Hussain
Author Link: https://www.codechef.com/users/shahraaz
*/
//by Himanshu Shukla
#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define ll long long
#define v32 vector<int>
#define v64 vector<ll>
#define s32 set<int>
#define s64 set<ll>
#define graph vector<s32>
#define p32 pair<int, int>
#define p64 pair<ll, ll>
#define fi first
#define se second
#define ln '\n'
#define debug(x) cout << (#x) << ": " << (x) << ln
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
inline ll add(ll a, ll b, ll m) { return (((a % m + b % m) % m + m) % m); }
inline ll mul(ll a, ll b, ll m) { return (((a % m * b % m) % m + m) % m); }
const double EPS = 1e-6;
const ll MOD = 1e9 + 7;
template <typename T, typename U>
ostream &operator<<(ostream &out, const pair<T, U> &p)
{
	out << '[' << p.fi << ", " << p.se << ']';
	return out;
}
template <template <typename, typename...> class ContainerType, typename ValueType, typename... Args>
void print_container(const ContainerType<ValueType, Args...> &c)
{
	cout << "{ ";
	for (const auto &v : c)
		cout << v << ' ';
	cout << '}' << ln;
}
 
struct median
{
	ll ans, suml, sumr, sum;
	priority_queue<int, vector<int>> mx;
	priority_queue<int, vector<int>, greater<int>> mn;
	median()
	{
		suml = sumr = 0, sum = 0;
		ans = -1e18;
	}
	void insert(ll item)
	{
		sum += item;
		if (item > ans)
		{
			mn.push(item);
			sumr += item;
		}
		else
		{
			mx.push(item);
			suml += item;
		}
		if (((int)mx.size() - (int)mn.size()) > 1)
		{
			ll temp = mx.top();
			mx.pop();
			suml -= temp;
			mn.push(temp);
			sumr += temp;
		}
		if (((int)mn.size() - (int)mx.size()) > 1)
		{
			ll temp = mn.top();
			mn.pop();
			sumr -= temp;
			mx.push(temp);
			suml += temp;
		}
		if ((mx.size() + mn.size()) % 2 == 1)
		{
			if (mn.size() > mx.size())
			{
				ll temp = mn.top();
				mn.pop();
				sumr -= temp;
				mx.push(temp);
				suml += temp;
			}
		}
		if (ans == -1e18)
			ans = item;
		else
			ans = mx.top();
	}
	ll getMedian()
	{
		return ans;
	}
	ll LeftSum()
	{
		return suml;
	}
	ll RightSum()
	{
		return sumr;
	}
	ll LeftSize()
	{
		return (ll)mx.size();
	}
	ll RightSize()
	{
		return (ll)mn.size();
	}
};
 
int main()
{
	FASTIO;
	int q;
	cin >> q;
	median M;
	while (q--)
	{
		int a;
		cin >> a;
		M.insert(a);
		ll ans = M.getMedian() * (M.LeftSize() - M.RightSize()) + M.RightSum() - M.LeftSum();
		ans *= 2;
		cout << ans << ln;
	}
	return 0;
}
 