
typedef pair<int, ll> pil;
struct DQ
{
    deque<pil> Q;
    int window;
    DQ()
    {
    }
    DQ(int w)
    {
        window = w;
    }
    void insert(ll value, int idx)
    {
        db(value,idx);
        if (Q.empty())
            Q.pb(mp(idx, value));
        else
        {
            while (!Q.empty() && Q.back().s <= value)
                Q.pop_back();
            while (!Q.empty() && Q.front().f <= idx - window)
                Q.pop_front();
            Q.pb(mp(idx, value));
        }
    }
    ll top()
    {
        return Q.front().s;
    }
};
