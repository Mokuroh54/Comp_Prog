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

const int MAXN = 300010;

extern vector<int> nbs[MAXN];

struct Tarjan {
    int T = 0;
    vector<int> t, low, vis;
    vector<int> aps;
    vector<vector<int>> bridges;

    Tarjan(int n) {
        t.resize(n + 1);
        low.resize(n + 1);
        vis.resize(n + 1);
        aps.resize(n + 1);
        bridges.resize(n + 1);
    }

    void calc(int a, int p) {
        if (DFS(a, p) > 1) aps.pb(a);
    }

    int DFS(int a, int p) {
        if (vis[a]) return 0;
        vis[a] = 1;

        t[a] = ++T;
        low[a] = T;

        int subgraphs = 0;
        for (int nb : nbs[a]) if (nb != p) {
            if (!vis[nb]) {
                DFS(nb, a);
                subgraphs++;
                if (t[a] < low[nb]) {
                    bridges[a].pb(nb);
                    bridges[nb].pb(a);
                }
                if (t[a] <= low[nb]) aps[a] = 1;
                low[a] = min(low[a], low[nb]);
            }
            else {
                DFS(nb, a);
                low[a] = min(low[a], t[nb]);
            }
        }

        return subgraphs;
    }
};

int N, M;
vector<int> nbs[MAXN];
int vis[MAXN];
Tarjan tar(0);

void reset_tc() {
}

pii DFS(int a, int p) {
    if (vis[a]) return pii(0, 0);
    vis[a] = 1;

    int bcounter = 0;
    int ans = 0;
    int lpath1 = 0;
    int lpath2 = 0;
    for (int nb : nbs[a]) if (nb != p) {
        pii v = DFS(nb, a);
        if (bcounter < size(tar.bridges[a]) && tar.bridges[a][bcounter] == nb) {
            bcounter++;
            v.SS++;
        }

        if (v.FF > ans) ans = v.FF;
        if (v.SS > lpath2) lpath2 = v.SS;
        if (lpath2 > lpath1) swap(lpath2, lpath1);
    }

    return pii(max(ans, lpath1 + lpath2), lpath1);
}

void solve() {
    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    tar = Tarjan(N);
    tar.calc(1, 0);

    cout << DFS(1, 0).FF << endl;

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