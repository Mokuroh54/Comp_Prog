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

const int MAXN = 200010;
int N, Q;
ll K;
ll pos[MAXN];
ll delay[MAXN];
ll queries[MAXN];

map<ll, set<pll>> pos_res;
map<ll, set<pll>> neg_res;

int safe[MAXN][2];
int vis[MAXN][2];
int ans[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        pos[i] = delay[i] = queries[i] = 0;
        safe[i][0] = safe[i][1] = vis[i][0] = vis[i][1] = 0;
        ans[i] = 0;
    }

    pos_res.clear();
    neg_res.clear();
}

int DFS(int a, int dir) {
    // cout << a << " " << dir << endl;
    if (safe[a][dir]) return safe[a][dir];
    if (vis[a][dir]) return safe[a][dir] = -1;
    vis[a][dir] = 1;

    if (dir) {
        ll id = (pos[a] - delay[a] + K) % K;
        auto it = pos_res[id].upper_bound(pll(pos[a], a));
        if (it == pos_res[id].end()) safe[a][dir] = 1;
        else safe[a][dir] = DFS(it->SS, 1 - dir);
    }
    else {
        ll id = (pos[a] + delay[a]) % K;
        auto it = neg_res[id].lower_bound(pll(pos[a], a));
        if (it == neg_res[id].begin()) safe[a][dir] = 1;
        else safe[a][dir] = DFS((--it)->SS, 1 - dir);
    }

    // cout << a << " " << dir << " " << safe[a][dir] << endl;
    return safe[a][dir];
}

void solve() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> pos[i];
    for (int i = 1; i <= N; i++) cin >> delay[i];

    for (int i = 1; i <= N; i++) {
        pos_res[(pos[i] - delay[i] + K) % K].insert(pll(pos[i], i));
        neg_res[(pos[i] + delay[i]) % K].insert(pll(pos[i], i));
    }

    // for (int i = 1; i <= N; i++) cout << (pos[i] - delay[i] + K) % K << " ";
    // cout << endl;
    // for (int i = 1; i <= N; i++) cout << (pos[i] + delay[i]) % K << " ";
    // cout << endl;

    cin >> Q;
    for (int i = 1; i <= Q; i++) cin >> queries[i];

    for (int i = 1; i <= Q; i++) {
        // cout << queries[i] % K << endl;
        auto it = pos_res[queries[i] % K].lower_bound(pll(queries[i], 0));
        if (it == pos_res[queries[i] % K].end()) ans[i] = 1;
        else {
            // cout << "querying from " << it->SS << endl;
            ans[i] = DFS(it->SS, 0);
        }
    }

    for (int i = 1; i <= Q; i++) {
        if (ans[i] == 1) cout << "YES" << endl;
        else cout << "NO" << endl;
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
    // T = 1;
    cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 