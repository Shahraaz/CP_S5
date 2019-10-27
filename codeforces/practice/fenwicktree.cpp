struct Bit
{
    int size;
    vector<int> table;
    Bit(int size)
    {
        this->size = size;
        table.resize(size);
    }
    void update(int i, int delta)
    {
        while (i < size)
        {
            table[i] += delta;
            i += i & (-i);
        }
    }
    void sum(int i)
    {
        int ret = 0;
        while (i > 0)
        {
            sum += table[i];
            i -= i & (-i);
        }
        return ret;
    }
    int rangeSum(int i, int j)
    {
        return sum(j) - sum(i);
    }
};

///////////////

const int NNN = 1e5;
struct RangeBit
{
    int data[NNN];
    void update(int idx, int val)
    {
        while (idx < NNN)
        {
            data[idx] += val;
            idx += idx & (-idx);
        }
    }
    void update(int l, int r, int val)
    {
        update(l, val);
        update(r + 1, -val);
    }
    int query(int idx)
    {
        int res = 0;
        while (idx > 0)
        {
            res += data[idx];
            idx -= idx & (-idx);
        }
        return res;
    }
    int query(int l, int r)
    {
        return query(r) - query(l);
    }
};

struct LazyBit
{
    RangeBit bitAdd, bitSub;
    void update(int l, int r, int val)
    {
        bitAdd.update(l, r, val);
        bitSub.update(l, r, (l - 1) * val);
        bitSub.update(r + 1, (-r + l - 1) * val);
    }
    int query(int idx)
    {
        return idx * bitAdd.query(idx) - bitSub.query(idx);
    }
    int query(int l, int r)
    {
        return query(r) - query(l - 1);
    }
};