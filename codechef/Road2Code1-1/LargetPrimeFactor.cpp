#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

bool isPrime(long long n)
{
    if(n <= 2)
        return n == 2;
    if(n%2 == 0)
        return false;
    for(long long i = 3;i*i<=n;i+=2)
        if(n%i == 0)
            return false;
    return true;
}


int main(){
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        long n;
        cin >> n;
        if(isPrime(n))
            cout << n << '\n';
        else {
            long long res = 0;
            for(long long i = 2;i*i<=n;i+=1)
            {
                if(n%i == 0)
                {
                    res = max(res,i);
                    while(n%i==0)
                        n /= i;
                }
            }
            if(n > 1)
                res = max(res,(long long)n);
            cout << res << '\n';
        }
    }
    return 0;
}

