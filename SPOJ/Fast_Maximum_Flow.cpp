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

const int MAXN = 5010;

struct Edge{
    ll flow;
    ll cap;
    int s, d;
    int res;
};

extern vector<Edge> edges;
extern vector<int> nbs[MAXN];

struct Dinic {
    vector<int> vis;
    vector<int> level;
    vector<int> ptr;
    int s, t, n;

    Dinic(int tn, int ts, int tt) {
        vis.resize(tn + 1);
        level.resize(tn + 1);
        ptr.resize(tn + 1);
        s = ts, t = tt, n = tn;

    }

    int BFS() {
        for (int i = 1; i <= n; i++) level[i] = INF, vis[i] = 0, ptr[i] = 0;
        level[s] = 0;
        queue<int> search;
        search.push(s);
        int reached = 0;
        while (!search.empty()) {
            int n = search.front();
            search.pop();

            if (vis[n]) continue;
            vis[n] = 1;
            if (n == t) reached = 1;

            for (int nb : nbs[n]) if (edges[nb].flow < edges[nb].cap) {
                level[edges[nb].d] = min(level[edges[nb].d], level[n] + 1);
                search.push(edges[nb].d);
            }
        }
        return reached;
    }

    ll DFS(vector<int>& path, int a) {
        for (int i = ptr[a]; i < size(nbs[a]); i++) {
            int nb = nbs[a][i];
            if (level[edges[nb].d] == level[a] + 1 && 
                edges[nb].flow < edges[nb].cap) {
                path.pb(nb);
                ll v = DFS(path, edges[nb].d);
                if (edges[nb].d == t) return edges[nb].cap - edges[nb].flow;
                if (v != LINF) return min(v, edges[nb].cap - edges[nb].flow);
                else {
                    ptr[a]++;
                    path.ppb();
                }
            }
        }
        return LINF;
    }

    ll max_flow() {
        ll flow = 0;
        while (BFS()) {
            while (1) {
                vector<int> path;
                ll d = DFS(path, s);
                if (d != LINF) {
                    flow += d;
                    for (int e : path) {
                        edges[e].flow += d;
                        edges[edges[e].res].flow -= d;
                    }
                }
                else break;
            }
        }
        return flow;
    }
};

int N, M;
vector<Edge> edges;
vector<int> nbs[MAXN];

void reset_tc() {

}

void solve() {
    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        Edge e1 = {0, c, a, b};
        Edge e2 = {0, c, b, a};
        nbs[a].pb(size(edges));
        e1.res = size(edges) + 1;
        edges.pb(e1);
        nbs[b].pb(size(edges));
        e2.res = size(edges) - 1;
        edges.pb(e2);
    }

    Dinic d(N, 1, N);
    cout << d.max_flow() << endl;
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