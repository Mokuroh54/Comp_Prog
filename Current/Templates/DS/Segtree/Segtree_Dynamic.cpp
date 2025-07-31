struct ST {
    struct Node {
        ll sum = 0;
        ll minv = 0;
        ll maxv = 0;
        
        int lc = -1;
        int rc = -1;

        void merge(Node& b, Node& c) {
            sum = b.sum + c.sum;
            minv = min(b.minv, c.minv);
            maxv = max(b.maxv, c.maxv);
        }
    };

    vector<Node> seg;

    ST() {
        create();
    }

    int create() {
        seg.pb({0, LINF, -LINF});
        return size(seg) - 1;
    }

    void addToNode(int cid, ll v) {
        seg[cid].sum += v;
        mineq(seg[cid].minv, v);
        maxeq(seg[cid].maxv, v);
    }

    void update(int a, ll v, int cid, int ss, int se) {
        if (ss == se) {
            addToNode(cid, v);
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) {
            if (seg[cid].lc == -1) seg[cid].lc = create();
            update(a, v, seg[cid].lc, ss, mid);
        }
        else {
            if (seg[cid].rc == -1) seg[cid].rc = create();
            update(a, v, seg[cid].rc, mid + 1, se);
        }

        if (seg[cid].lc > 0) seg[cid].merge(seg[cid], seg[seg[cid].lc]);
        if (seg[cid].rc > 0) seg[cid].merge(seg[cid], seg[seg[cid].rc]);
    }

    Node query(int a, int b, int cid, int ss, int se) {
        if (a <= ss && se <= b) return seg[cid];

        int mid = (ss + se) / 2;
        Node ans = {0, LINF, -LINF};
        if (a <= mid && seg[cid].lc != -1) {
            Node lans = query(a, b, seg[cid].lc, ss, mid);
            ans.merge(ans, lans);
        }
        if (b > mid && seg[cid].rc != -1) {
            Node rans = query(a, b, seg[cid].rc, mid + 1, se);
            ans.merge(ans, rans);
        }

        return ans;
    }

    void clear() {
        seg.clear();
    }
};
