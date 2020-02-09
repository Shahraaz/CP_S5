/*
This Page https://leetcode.com/playground/Mom8QGch
WhatsApp gourp https://tinyurl.com/road2code1-1 
https://github.com/Shahraaz/CP_S5/tree/master/codechef/Road2Code1-1
*/

/*
https://www.hackerrank.com/contests/projecteuler/challenges/euler003/problem
*/

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

int main() {
    std::cout << "Hello World!\n";
    if(isPrime(2) && !isPrime(1500) && isPrime(1e9+7) && isPrime(15485863) && !isPrime(15485863LL*15485863LL))
        cout << "You are a stud!";
    else 
        cout << "Try Again";
}