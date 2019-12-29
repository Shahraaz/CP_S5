vector<int> Z_function(string S)
{
    int n = S.size();
    vector<int> z(n);
    int l = -1, r = -1;
    for (int i = 1; i < n; ++i)
    {
        if (i <= r)
            z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && S[z[i]] == S[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i];
    }
    return z;
}
