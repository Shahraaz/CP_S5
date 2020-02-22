// Optimise
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int NAX_PRIME = 2e5 + 5;
bool is_composite[NAX_PRIME];
vector<int> primes;

void seive(int n = NAX_PRIME)
{
    fill(is_composite, is_composite + n, false);
    for (int i = 2; i < n; i++)
    {
        if (!is_composite[i])
            primes.push_back(i);
        for (size_t j = 0; j < primes.size() && ((ll)i * primes[j] < n); j++)
        {
            is_composite[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

void solveCase()
{
}

int32_t main()
{
    int t = 1;
    for (int i = 1; i <= t; ++i)
        solveCase();
    return 0;
}
