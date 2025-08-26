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
ll MOD = 1000000007;

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

struct Comb {
    vector<ll> fact, factinv;
    vector<vector<int>> stirling;
    /* 
    stirling numbers of the first kind
    s[i][j] = jth coefficient of x risepow i
    s[i][j] = number of permutations length i with j cycles
    */
    vector<vector<int>> stirling2;
    /*
    stirling numbers of the second kind
    s2[i][j] = jth coefficient of x fallpow i
    s2[i][j] = number of ways to partition i elements into j subsets
    */
 
    void get_fact(int x) {
        fact.resize(x + 1);
        factinv.resize(x + 1);
        fact[0] = 1;
        for (int i = 1; i <= x; i++) fact[i] = mult(i, fact[i - 1]);
        factinv[x] = divide(1, fact[x]);
        assert(mult(fact[x], factinv[x]) == 1);
        for (int i = x - 1; i >= 0; i--) {
            factinv[i] = mult(factinv[i + 1], i + 1);
            assert(mult(fact[i], factinv[i]) == 1);
        }
    }
 
    void gen_stirling(int i, int j) {
        stirling.resize(i + 1);
        for (auto& n : stirling) n.resize(j + 1);
        stirling[0][0] = 1;
        for (int n = 0; n <= i; n++) for (int k = 0; k <= n; k++) {
            if (n && k)
                stirling[n][k] = add(mult(sub(0, n - 1), stirling[n - 1][k]), stirling[n - 1][k - 1]);
        }
    }
 
 
    void gen_stirling2(int i, int j) {
        stirling2.resize(i + 1);
        for (auto& n : stirling2) n.resize(j + 1);
        for (int n = 0; n <= i; n++) for (int k = 0; k <= n; k++) {
            if (n == k) stirling2[n][k] = 1;
            if (n && k) 
                stirling2[n][k] = add(stirling2[n - 1][k - 1], mult(k, stirling2[n - 1][k]));
        }
    }
 
    ll choose(int a, int b) {
        return mult(fact[a], mult(factinv[b], factinv[a - b]));
    }
 
    ll fallpow(int a, int b) {
        return mult(fact[a], factinv[a - b]);
    }
 
    ll stars_bars(int n, int k) {
        return choose(n + k - 1, k - 1);
    }
};

Comb c;
int N, M;
int vis[MAXN];
vector<int> nbs[MAXN];

int rt = 1;

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        nbs[i].clear();
        vis[i] = 0;
    }
    rt = 1;
}

ll DFS(int a, int p, int df) {
    vis[a] = 1;
    ll ans = 1;
    int free = 0;
    for (int nb : nbs[a]) if (nb != p) {
        if (vis[nb]) return 0;
        if (size(nbs[nb]) > 1) free++;
        multeq(ans, DFS(nb, a, 1));
    }

    int effsize = (a == rt ? size(nbs[a]) : size(nbs[a]) - 1);

    if (free > df) return 0;
    else if (!free) return mult(ans, c.fact[effsize]);
    else { 
        return mult(mult(ans, df), c.fact[effsize - free]);
    }
}

void solve() {
    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    while (N > 2 && rt <= N && size(nbs[rt]) == 1) rt++;

    if (M >= N) cout << 0 << endl;
    else cout << mult(DFS(rt, 0, 2), 2) << endl;
    reset_tc();
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    c.get_fact(200000);

    int T;
    // T = 1;
    cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 