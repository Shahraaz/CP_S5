class Trie_Node
{
private:
    vector<Trie_Node *> child;

public:
    Trie_Node(/* args */)
    {
        child.resize(26, nullptr);
    }
    void insert(string s)
    {
        Trie_Node *curr = this;
        int len = s.length();
        for (int i = 0; i < len; ++i)
        {
            int c = s[i] - 'a';
            if (curr->child[c] == nullptr)
                curr->child[c] = new Trie_Node;
            curr = curr->child[c];
        }
    }
};

class Trie
{
    unordered_map<char, Trie *> char_map;
    bool word_ends;

public:
    Trie()
    {
        word_ends = false;
    }

    void insert(string word)
    {
        if (word.length() == 0)
            return;

        Trie *temp = this;
        for (auto ch : word)
        {
            if (temp->char_map.find(ch) != temp->char_map.end())
            {
                temp = temp->char_map[ch];
            }
            else
            {
                temp->char_map[ch] = new Trie();
                temp = temp->char_map[ch];
            }
        }
        temp->word_ends = true;
    }

    bool search(string word)
    {
        if (word.length() == 0)
            return false;

        Trie *temp = this;

        for (auto ch : word)
        {
            if (temp->char_map.find(ch) == temp->char_map.end())
                return false;

            temp = temp->char_map[ch];
            if (temp->word_ends)
                return true;
        }

        return temp->word_ends;
    }

    bool startsWith(string prefix)
    {
        if (prefix.length() == 0)
            return true;

        Trie *temp = this;

        for (auto ch : prefix)
        {
            if (temp->char_map.find(ch) == temp->char_map.end())
                return false;
            temp = temp->char_map[ch];
        }

        return true;
    }
};

class StreamChecker
{
    Trie my_trie;
    string str = "";
    int w_len = 0;

public:
    StreamChecker(vector<string> &words)
    {
        for (auto w : words)
        {
            reverse(w.begin(), w.end());
            w_len = max(w_len, (int)w.length());
            my_trie.insert(w);
        }
    }

    bool query(char letter)
    {
        str = letter + str;

        if (str.length() > w_len)
            str.pop_back();
        bool res = my_trie.search(str);
        return res;
    }
};
