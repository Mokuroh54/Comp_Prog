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
ll MOD = 998244353;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<ld> cd;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<pii> vpii;

inline ll add(ll a, ll b) {
    return (a + b >= MOD ? a + b : a + b);
}
inline ll sub(ll a, ll b) {
    return (a - b >= 0 ? a - b : a - b + MOD);
}
inline ll mult(ll a, ll b) {
    return (a * b) % MOD;
}
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
inline ll divide(ll a, ll b) {
    return mult(a, power(b, MOD - 2));
}

#define maxeq(x, y) x = x > y ? x : y
#define mineq(x, y) x = x < y ? x : y
#define addeq(x, y) x = add(x, y)
#define subeq(x, y) x = sub(x, y)
#define multeq(x, y) x = mult(x, y)
#define diveq(x, y) x = divide(x, y)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 200010;

struct Trie {
    vector<int> trie;
    vector<int> lc;
    vector<int> rc;

    Trie() {
        create();
    }

    int create() {
        trie.pb(0);
        lc.pb(-1);
        rc.pb(-1);
        return size(trie) - 1;
    }
 
    void update(int a, int t, int cid) {
        trie[cid]++;
        if (t == -1) return;
        if ((1 << t) & a) {
            if (rc[cid] == -1) rc[cid] = create();
            update(a, t - 1, rc[cid]);
        }
        else {
            if (lc[cid] == -1) lc[cid] = create();
            update(a, t - 1, lc[cid]);
        }
    }

    ll query(int t, int cid, int used) {
        if (t == -1) {
            // cout << 1ll * trie[cid] * (used + 1) << endl;
            return 1ll * trie[cid] * trie[cid] * (used + 1);
        }

        ll lv = (lc[cid] != -1 ? trie[lc[cid]] : 0);
        ll rv = (rc[cid] != -1 ? trie[rc[cid]] : 0);

        ll ret = lv * rv * (2 * used + 3);

        if (lc[cid] != -1) ret += query(t - 1, lc[cid], used);
        if (rc[cid] != -1) ret += query(t - 1, rc[cid], used + 1);

        return ret;
    }
};

int N;
Trie t;
int arr[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) arr[i] = 0;
    t = Trie();
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= N; i++) t.update(arr[i], 30, 0);

    cout << divide(t.query(30, 0, 0) % MOD, mult(N, N)) << endl;
    reset_tc();
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    // T = 1;
    cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 