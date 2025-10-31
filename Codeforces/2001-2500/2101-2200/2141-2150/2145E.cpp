/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ >(.)__ >(.)__
 (___/  (___/  (___/
I am dum duck

Tooting Bec
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second

#define ll long long
#define ld long double
#define ull unsigned ll

#define endl "\n"
#define EPS 1e-9

#define size(v) (int) v.size()
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
// #define cout cerr

ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 0;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<ld> cd;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<pii> vpii;

#define add(a, b) (((a) + (b)) >= MOD ? (a) + (b) - MOD : (a) + (b))
#define sub(a, b) (((a) - (b)) >= 0 ? (a) - (b) : (a) + MOD - (b))
#define mult(a, b) (((a) * (b)) % MOD)
inline ll power(ll a, ll b) {
    ll n = a;
    ll ans = 1;

    for (int i = 0; i < 64; i++) {
        if (b & 1) ans = (ans * n) % MOD;
        n = (n * n) % MOD;
        b >>= 1;
    }

    return ans;
}
#define divide(a, b) mult(a, power(b, MOD - 2))

#define maxeq(x, y) x = x > y ? x : y
#define mineq(x, y) x = x < y ? x : y
#define addeq(x, y) x = add(x, y)
#define subeq(x, y) x = sub(x, y)
#define multeq(x, y) x = mult(x, y)
#define diveq(x, y) x = divide(x, y)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct ST {
    struct Node {
        ll sum = 0;
        ll minv = 0;
        ll maxv = 0;
        ll lazy = 0;

        void merge(Node& b, Node& c) {
            sum = b.sum + c.sum;
            minv = min(b.minv, c.minv);
            maxv = max(b.maxv, c.maxv);
        }
    };
    vector<Node> seg;

    ST(int n) {
        seg.resize(n * 4 + 1);
    }

    void apply(int cid, ll v, int ss, int se) {
        seg[cid].lazy += v;
        seg[cid].sum += v * (se - ss + 1);
        seg[cid].minv += v;
        seg[cid].maxv += v;
    }

    void push(int cid, int ss, int se) {
        if (seg[cid].lazy && ss != se) {
            int mid = (ss + se) / 2;
            apply(cid * 2, seg[cid].lazy, ss, mid);
            apply(cid * 2 + 1, seg[cid].lazy, mid + 1, se);
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
        if (a <= mid) update(a, b, v, cid * 2, ss, mid);
        if (b > mid) update(a, b, v, cid * 2 + 1, mid + 1, se);
        seg[cid].merge(seg[cid * 2], seg[cid * 2 + 1]);
    }

    Node query(int a, int b, int cid, int ss, int se) {
        if (a > b) return Node();
        if (a <= ss && se <= b) return seg[cid];

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        Node ans = {0, LINF, -LINF, 0};
        if (a <= mid) {
            Node lans = query(a, b, cid * 2, ss, mid);
            ans.merge(ans, lans);
        }
        if (b > mid) {
            Node rans = query(a, b, cid * 2 + 1, mid + 1, se);
            ans.merge(ans, rans);
        }
        seg[cid].merge(seg[cid * 2], seg[cid * 2 + 1]);
        return ans;
    }

    int walker(int cid, int ss, int se) {
        if (ss == se) return ss;

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        int ret;
        if (seg[cid * 2].minv >= 0) ret = walker(cid * 2 + 1, mid + 1, se);
        else ret = walker(cid * 2, ss, mid);
        return ret;
    }

    void clear(int cid, int ss, int se) {
        seg[cid] = Node();
        if (ss == se) return;

        int mid = (ss + se) / 2;
        clear(cid * 2, ss, mid);
        clear(cid * 2 + 1, mid + 1, se);
    }
};

const int MAXN = 500010;
int A, D;
int N;
int a[MAXN], d[MAXN];

void reset_tc() {

}

void solve() {
    cin >> A >> D;
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> a[i];
    for (int i = 1; i <= N; i++) cin >> d[i];

    int V = 2000000;
    ST st(V);
    for (int i = 1; i <= N; i++) 
        st.update(min(max(a[i] - A, 0) + max(d[i] - D, 0), V), V, 1, 1, 0, V);
    for (int i = 0; i <= V; i++) st.update(i, V, -1, 1, 0, V);
    
    int Q;
    cin >> Q;
    while (Q--) {
        int i, na, nd;
        cin >> i >> na >> nd;

        int o = min(max(a[i] - A, 0) + max(d[i] - D, 0), V);
        a[i] = na;
        d[i] = nd;
        int n = min(max(a[i] - A, 0) + max(d[i] - D, 0), V);

        if (o < n) st.update(o, n - 1, -1, 1, 0, V);
        else if (o > n) st.update(n, o - 1, 1, 1, 0, V);

        // for (int i = 0; i <= N; i++) cout << st.query(i, i, 1, 0, V).maxv << " ";
        // cout << endl;

        cout << st.walker(1, 0, V) << endl;
    }

    reset_tc();
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    T = 1;
    // cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 