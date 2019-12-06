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

struct suffixArrays
{
    vector<int> sort_cyclic_shifts(string s)
    {
        /*
        Let us now focus on the implementation of the algorithm. We will write a function that takes a string s
        and returns the permutations of the sorted cyclic shifts.
        */
        int n = s.size();
        const int alphabet = 256;
        /*
        At the beginning (in the 0-th iteration) we must sort the cyclic substrings of length 1,
        that is we have to sort all characters of the string and divide them into equivalence classes
        (same symbols get assigned to the same class). 
        This can be done trivially, for example, by using counting sort.
        For each character we count how many times it appears in the string,
        and then use this information to create the array p[].
        After that we go through the array p[] and construct c[] by comparing adjacent characters.
    */
        vector<int> p(n), c(n), cnt(max(alphabet, n));
        for (int i = 0; i < n; ++i)
            cnt[s[i]]++;
        for (int i = 1; i < alphabet; ++i)
            cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; ++i)
            p[--cnt[s[i]]] = i;
        c[p[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; ++i)
        {
            if (s[p[i]] != s[p[i - 1]])
                classes++;
            c[p[i]] = classes - 1;
        }
        /*
        Now we have to talk about the iteration step. Let's assume we have already performed the k−1-th step and computed the values of the arrays p[] and c[] for it. We want to compute the values for the k-th step in O(n) time. Since we perform this step O(logn) times, the complete algorithm will have a time complexity of O(nlogn)

        .

        To do this, note that the cyclic substrings of length 2k
        consists of two substrings of length 2k−1 which we can compare with each other in O(1) using the information from the previous phase - the values of the equivalence classes c[]. Thus, for two substrings of length 2k starting at position i and j, all necessary information to compare them is contained in the pairs (c[i], c[i+2k−1]) and (c[j], c[j+2k−1]).
        …si…si+2k−1−1length=2k−1, class=c[i]si+2k−1…si+2k−1length=2k−1, class=c[i+2k−1]length=2k…sj…sj+2k−1−1length=2k−1, class=c[j]sj+2k−1…sj+2k−1length=2k−1, class=c[j+2k−1]length=2k…

        This gives us a very simple solution: sort the substrings of length 2k
        by these pairs of numbers. This will give us the required order p[]. However a normal sort runs in O(nlogn) time, with which we are not satisfied. This will only give us an algorithm for constructing a suffix array in O(nlog2n)

        times.

        How do we quickly perform such a sorting of the pairs? Since the elements of the pairs do not exceed n

        , we can use counting sort again. However sorting pairs with counting sort is not the most efficient. To achieve a better hidden constant in the complexity, we will use another trick.

        We use here the technique on which radix sort is based: to sort the pairs we first sort them by the second element, and then by the first element (with a stable sort, i.e. sorting without breaking the relative order of equal elements). However the second elements were already sorted in the previous iteration. Thus, in order to sort the pairs by the second elements, we just need to subtract 2k−1
        from the indices in p[] (e.g. if the smallest substring of length 2k−1 starts at position i, then the substring of length 2k with the smallest second half starts at i−2k−1

        ).

        So only by simple subtractions we can sort the second elements of the pairs in p[]

        . Now we need to perform a stable sort by the first elements. As already mentioned, this can be accomplished with counting sort.

        The only thing left is to compute the equivalence classes c[]
        , but as before this can be done by simply iterating over the sorted permutation p[]

        and comparing neighboring pairs.

        Here is the remaining implementation. We use temporary arrays pn[]
        and cn[] to store the permutation by the second elements and the new equivalent class indices.
*/
        vector<int> pn(n), cn(n);
        for (int h = 0; (1 << h) < n; ++h)
        {
            for (int i = 0; i < n; ++i)
            {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0)
                    pn[i] += n;
            }
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int i = 0; i < n; ++i)
                cnt[c[pn[i]]]++;
            for (int i = 1; i < classes; ++i)
                cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; --i)
                p[--cnt[pn[i]]] = pn[i];
            cn[p[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; ++i)
            {
                pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
                pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
                if (cur != prev)
                    ++classes;
                cn[p[i]] = classes + 1;
            }
            c.swap(cn);
        }
        return p;
    }

    /*
        The algorithm requires O(nlogn) time and O(n) memory. However if we take the size of the alphabet k into account, then it uses O((n+k)logn) time and O(n+k)

        memory.

        For simplicity we used the complete ASCII range as alphabet. If we know that the string only contains a subset of characters, e.g. only lowercase letters, then this implementation can obviously be optimized. However not by much, since the alphabet size only appears with a factor of O(logn)

        in the complexity.

        Also note, that this algorithm only sorts the cycle shifts. As mentioned at the beginning of this section we can generate the sorted order of the suffixes by appending a character that is smaller than all other characters of the string, and sorting this resulting string by cycle shifts, e.g. by sorting the cycle shifts of s+$
        . This will obviously give the suffix array of s, however prepended with |s|.
*/

    vector<int> suffix_array_construction(string s)
    {
        s += '$';
        auto sorted_shifts = sort_cyclic_shifts(s);
        sorted_shifts.erase(sorted_shifts.begin());
        return sorted_shifts;
    }

    /*
Applications
Finding the smallest cyclic shift

The algorithm above sorts all cyclic shifts (without appending a character to the string), and therefore p[0]

gives the position of the smallest cyclic shift.
Finding a substring in a string

The task is to find a string s
inside some text t online - we know the text t beforehand, but not the string s. We can create the suffix array for the text t in O(|t|log|t|) time. Now we can look for the substring s in the following way. The occurrence of s must be a prefix of some suffix from t. Since we sorted all the suffixes we can perform a binary search for s in p. Comparing the current suffix and the substring s within the binary search can be done in O(|s|) time, therefore the complexity for finding the substring is O(|s|log|t|). Also notice that if the substring occurs multiple times in t, then all occurrences will be next to each other in p

. Therefore the number of occurrences can be found with a second binary search, and all occurrences can be printed easily.


*/
};

void solveCase(int caseNo)
{
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