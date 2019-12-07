struct Rabin_Karp
{
    const int maxSize = 1e6 + 10;
    const int p1 = 805306457, p2 = 53, p3 = 31;
    const int mod1 = 1610612741, mod2 = 1e9 + 7, mod3 = 1e9 + 9, m = 1e9 + 9;
    vector<long long> p_pow1, p_pow2, p_pow3;
    Rabin_Karp()
    {
        // p_pow1.resize(maxSize);
        // p_pow2.resize(maxSize);
        // p_pow3.resize(maxSize);
        // p_pow1[0] = p_pow2[0] = p_pow3[0] = 1;
        // for (int i = 1; i < (int)p_pow1.size(); i++)
        // {
        //     p_pow1[i] = (p_pow1[i - 1] * p1) % mod1;
        //     p_pow2[i] = (p_pow2[i - 1] * p2) % mod2;
        //     p_pow3[i] = (p_pow3[i - 1] * p3) % mod3;
        // }
    }
    vector<int> Z_function(string S)
    {
        int n = S.size();
        vector<int> z(n);
        int l = 0, r = 0;
        for (int i = 1; i < n; ++i)
        {
            if (i <= r)
                z[i] = min(r - i + 1, z[i - l]);
            while (i + z[i] < n && S[z[i]] == S[i + z[i]])
                ++z[i];
            if (i + z[i] - 1 > r)
                l = i, r = i + z[i] - 1;
        }
        return z;
    }

    vector<int> match(string s, string t)
    {
        int S = s.size(), T = t.size();
        vector<long long> h1(T + 1, 0), h2(T + 1, 0), h3(T + 1, 0);
        for (int i = 0; i < T; i++)
        {
            h1[i + 1] = (h1[i] + (t[i] - 'a' + 1) * p_pow1[i]) % mod1;
            h2[i + 1] = (h2[i] + (t[i] - 'a' + 1) * p_pow2[i]) % mod2;
            h3[i + 1] = (h3[i] + (t[i] - 'a' + 1) * p_pow3[i]) % mod3;
        }
        long long h_s1 = 0, h_s2 = 0, h_s3 = 0;
        for (int i = 0; i < S; i++)
        {
            h_s1 = (h_s1 + (s[i] - 'a' + 1) * p_pow1[i]) % mod1;
            h_s2 = (h_s2 + (s[i] - 'a' + 1) * p_pow2[i]) % mod2;
            h_s3 = (h_s3 + (s[i] - 'a' + 1) * p_pow3[i]) % mod3;
        }
        vector<int> occurences;
        for (int i = 0; i + S - 1 < T; i++)
        {
            long long cur_h1 = (h1[i + S] + mod1 - h1[i]) % mod1;
            long long cur_h2 = (h2[i + S] + mod2 - h2[i]) % mod2;
            long long cur_h3 = (h3[i + S] + mod3 - h3[i]) % mod3;
            if (cur_h1 == h_s1 * p_pow1[i] % mod1)
                if (cur_h2 == h_s2 * p_pow2[i] % mod2)
                    if (cur_h3 == h_s3 * p_pow3[i] % mod3)
                        occurences.push_back(i);
        }
        return occurences;
    }
};

Rabin_Karp R;
