struct node
{
    int count;
    node *left, *right;

    node(int _count, node *_left, node *_right) : count(_count), left(_left), right(_right) {}
    node *insert(int l, int r, int w);
};

node *null = new node(0, NULL, NULL);

node *node::insert(int l, int r, int w)
{
    if (l <= w && w <= r)
    {
        if (l == r)
            return new node(this->count + 1, null, null);

        int mid = (l + r) / 2;

        return new node(this->count + 1, this->left->insert(l, mid, w), this->right->insert(mid + 1, r, w));
    }
    return this;
}

int query(node *a, node *b, int l, int r, int k)
{
    if (l == r)
        return l;

    int count = a->left->count - b->left->count;
    int m = (l + r) / 2;

    db(l, r, k, count);

    if (count >= k)
        return query(a->left, b->left, l, m, k);
    return query(a->right, b->right, m + 1, r, k - count);
}

const int LIM = 1e5 + 5;
node *root[LIM];
// null->left = null->right = null;
