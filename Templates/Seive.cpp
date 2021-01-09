const int _NSeive = 2e5 + 10;
vector<bool> isPrime(_NSeive, true);
void buildSeive()
{
    isPrime[1] = false;
    isPrime[0] = false;
    for (int i = 4; i < _NSeive; i += 2)
        isPrime[i] = false;
    for (int i = 3; i * i < _NSeive; i += 2)
        if (isPrime[i])
            for (int j = i * i; j < _NSeive; j += i)
                isPrime[j] = false;
}
