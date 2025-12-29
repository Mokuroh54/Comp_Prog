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

const int MAXN = 100010;
extern vector<int> nbs[MAXN];

struct LCA {
    vector<int> in, out, depth, vis;
    vector<int> lift[32];
    int T = 0;

    LCA() {LCA(0);}
    LCA(int n) {
        in.resize(n + 1);
        out.resize(n + 1);
        depth.resize(n + 1);
        vis.resize(n + 1);
        for (int i = 0; i < 32; i++) lift[i].resize(n + 1);
    }

    void tour(int a, int p) {
        vis[a] = 1;
        depth[a] = depth[p] + 1;

        lift[0][a] = p;
        for (int j = 1; j < 32; j++) 
            lift[j][a] = lift[j - 1][lift[j - 1][a]];
        
        in[a] = ++T;
        for (int nb : nbs[a]) if (nb != p && !vis[nb]) tour(nb, a);
        out[a] = ++T;
    }
    bool is_anc(int a, int b) {return in[a] <= in[b] && out[b] <= out[a];}
    int lca(int a, int b) {
        if (is_anc(a, b)) return a;
        if (is_anc(b, a)) return b;

        for (int i = 31; i >= 0; i--) 
            if (!is_anc(lift[i][a], b)) a = lift[i][a];
                
        return lift[0][a];
    }
};

int N, M, K;
vector<int> nbs[MAXN];
int vis[MAXN];
int min_cyc_len = INF;
pii arbiter;
LCA lca;

void reset_tc() {

}

void solve() {
    cin >> N >> M >> K;
    lca = LCA(N);
    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    lca.tour(1, 0);
    for (int i = 1; i <= N; i++) {
        for (int nb : nbs[i]) {
            int a = lca.lca(i, nb);
            if (a != i && a != nb) {
                int clen = lca.depth[i] + lca.depth[nb] - 2 * lca.depth[a];
                if (clen < min_cyc_len) {
                    min_cyc_len = clen;
                    arbiter = pii(i, nb);
                }
            }
            else if (abs(lca.depth[i] - lca.depth[nb]) > 1) {
                int clen = abs(lca.depth[i] - lca.depth[nb]);
                if (clen < min_cyc_len) {
                    min_cyc_len = clen;
                    arbiter = pii(i, nb);
                }
            }
        }
    }

    if (min_cyc_len == INF) {
        vector<int> aah[2];
        for (int i = 1; i <= N; i++) aah[lca.depth[i] & 1].pb(i);
        
        cout << 1 << endl;
        if (size(aah[0]) >= (K + 1) / 2) {
            for (int i = 0; i < (K + 1) / 2; i++) cout << aah[0][i] << " ";
            cout << endl;
        }
        else {
            for (int i = 0; i < (K + 1) / 2; i++) cout << aah[1][i] << " ";
            cout << endl;
        }
        return;
    }

    int a = arbiter.FF;
    int b = arbiter.SS;
    int c = lca.lca(a, b);

    vector<int> up_from_a;
    vector<int> up_from_b;
    while (a != c) {
        up_from_a.pb(a);
        int guy = 0;
        for (int nb : nbs[a]) if (lca.depth[nb] == lca.depth[a] - 1) guy = nb;
        a = guy;
    }
    while (b != c) {
        up_from_b.pb(b);
        int guy = 0;
        for (int nb : nbs[b]) if (lca.depth[nb] == lca.depth[b] - 1) guy = nb;
        b = guy;
    }
    reverse(up_from_b.begin(), up_from_b.end());

    vector<int> total;
    for (int n : up_from_a) total.pb(n);
    total.pb(c);
    for (int n : up_from_b) total.pb(n);

    if (size(total) <= K) {
        cout << 2 << endl;
        cout << size(total) << endl;
        for (int n : total) cout << n << " ";
        cout << endl;
    }
    else {
        cout << 1 << endl;
        for (int i = 0; i < K; i += 2) cout << total[i] << " ";
        cout << endl;
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