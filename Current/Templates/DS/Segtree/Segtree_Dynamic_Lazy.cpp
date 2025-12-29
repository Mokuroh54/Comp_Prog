struct ST {
    struct Node {
        ll sum = 0;
        ll minv = 0;
        ll maxv = 0;
        ll lazy = 0;
        int lc = -1, rc = -1;

        void merge(Node& b, Node& c) {
            sum = b.sum + c.sum;
            minv = min(b.minv, c.minv);
            maxv = max(b.maxv, c.maxv);
        }

        bool isLeaf() {
            return lc == -1 && rc == -1;
        }
    };
    vector<Node> seg;

    ST() {
        create();
    }

    int create() {
        seg.pb(Node());
        return size(seg) - 1;
    }

    void apply(int cid, ll v, int ss, int se) {
        seg[cid].lazy += v;
        seg[cid].sum += v * (se - ss + 1);
        seg[cid].minv += v;
        seg[cid].maxv += v;
    }

    void push(int cid, int ss, int se) {
        if (ss != se) {
            int mid = (ss + se) / 2;
            if (seg[cid].lc == -1) seg[cid].lc = create();
            apply(seg[cid].lc, seg[cid].lazy, ss, mid);
            if (seg[cid].rc == -1) seg[cid].rc = create();
            apply(seg[cid].rc, seg[cid].lazy, mid + 1, se);
        }
        seg[cid].lazy = 0;
    }

    void update(int a, int b, ll v, int cid, int ss, int se) {
        if (a > b) return;
        if (a <= ss && se <= b) {
            apply(cid, v, ss, se);
            return;
        }

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        if (a <= mid) {
            if (seg[cid].lc == -1) seg[cid].lc = create();
            update(a, b, v, seg[cid].lc, ss, mid);
        }
        if (b > mid) {
            if (seg[cid].rc == -1) seg[cid].rc = create();
            update(a, b, v, seg[cid].rc, mid + 1, se);
        }

        seg[cid].merge(seg[seg[cid].lc], seg[seg[cid].rc]);
    }

    Node query(int a, int b, int cid, int ss, int se) {
        if (a <= ss && se <= b) return seg[cid];

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        Node ans = Node();
        if (a <= mid && seg[cid].lc != -1) {
            Node lans = query(a, b, seg[cid].lc, ss, mid);
            ans.merge(ans, lans);
        }
        if (b > mid && seg[cid].rc != -1) {
            Node rans = query(a, b, seg[cid].rc, mid + 1, se);
            ans.merge(ans, rans);
        }
        seg[cid].merge(seg[seg[cid].lc], seg[seg[cid].rc]);

        return ans;
    }
};