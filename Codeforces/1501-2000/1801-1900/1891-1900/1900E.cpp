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
int N, M;
int cost[MAXN];
vector<int> nbs[MAXN];
vector<int> rnbs[MAXN];
set<int> nbs2[MAXN];
int vis[MAXN];
int T = 0;
int t[MAXN];
pii order[MAXN];
int owner[MAXN];
pll sccinfo[MAXN];
pll path[MAXN];
int in[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        nbs[i].clear();
        rnbs[i].clear();
        nbs2[i].clear();

        order[i] = sccinfo[i] = path[i] = {0, 0};

        t[i] = owner[i] = in[i] = vis[i] = cost[i] = 0;
    }
    T = 0;
}

void DFS(int a, int p, int mode, int r) {
    vector<int>& tnbs = (mode ? rnbs[a] : nbs[a]);

    if (vis[a]) return;
    vis[a] = 1;
    for (int nb : tnbs) if (nb != p) DFS(nb, a, mode, r);
    if (!mode) t[a] = ++T;
    else {
        owner[a] = r;
        sccinfo[r].FF++;
        sccinfo[r].SS -= cost[a];
    }
}

void solve() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> cost[i];
    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        rnbs[b].pb(a);
    }

    for (int i = 1; i <= N; i++) if (!vis[i]) DFS(i, 0, 0, i);
    for (int i = 1; i <= N; i++) order[i] = pii(-t[i], i);
    sort(order + 1, order + 1 + N);
    for (int i = 1; i <= N; i++) vis[i] = 0;

    for (int i = 1; i <= N; i++) if (!vis[order[i].SS]) {
        // cout << "love " << order[i].SS << endl;
        DFS(order[i].SS, 0, 1, order[i].SS);
    }

    for (int i = 1; i <= N; i++) for (int nb : nbs[i]) {
        if (owner[i] != owner[nb]) {
            in[owner[nb]] += 1 - nbs2[owner[i]].count(owner[nb]);
            nbs2[owner[i]].insert(owner[nb]);
            // cout << i << " " << nb << " " << owner[i] << " " << owner[nb] << endl;
        }
    }

    queue<int> ducks;
    for (int i = 1; i <= N; i++) if (i == owner[i] && !in[i]) {
        path[i] = sccinfo[i];
        ducks.push(i);
    }

    while (!ducks.empty()) {
        int n = ducks.front();
        // cout << "zisha at: " << n << endl;
        // cout << path[n].FF << " " << path[n].SS << endl;
        ducks.pop();

        for (int nb : nbs2[n]) {
            path[nb] = max(path[nb], pll(path[n].FF + sccinfo[nb].FF, path[n].SS + sccinfo[nb].SS));
            in[nb]--;
            if (!in[nb]) ducks.push(nb);
        }
    }

    pll ans = pll(0, 0);
    for (int i = 1; i <= N; i++) if (i == owner[i]) ans = max(ans, path[i]);

    cout << ans.FF << " " << -ans.SS << endl;

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