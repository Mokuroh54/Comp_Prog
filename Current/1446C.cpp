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

int INF = 1000000000;
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
 
    void insert(int i, int t, int cid) {
        trie[cid]++;
        if (t == -1) return;

        if (rc[cid] == -1) rc[cid] = create();
        if (lc[cid] == -1) lc[cid] = create();
        if ((1 << t) & i) insert(i, t - 1, rc[cid]);
        else insert(i, t - 1, lc[cid]);
    }

    int query(int t, int cid) {
        if (t == -1) return trie[cid];
        if (cid == -1) return 0;

        if (trie[lc[cid]] == 0) return query(t - 1, rc[cid]);
        else if (trie[rc[cid]] == 0) return query(t - 1, lc[cid]);
        else return 1 + max(query(t - 1, lc[cid]), query(t - 1, rc[cid]));
    }
};

int N;
int arr[MAXN];
int hi[MAXN];
Trie t;

void reset_tc() {

}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    for (int i = 1; i <= N; i++) t.insert(arr[i], 31, 0);

    cout << N - t.query(31, 0) << endl;

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