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
int N;
vector<int> nbs[MAXN];
int dist[MAXN][2];
int in_dia[MAXN];
vector<int> dia;
int D;

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        nbs[i].clear();
        dist[i][0] = dist[i][1] = 0;
        in_dia[i] = 0;
    }
    D = 0;
    dia.clear();
}

void DFS(int a, int p, int run) {
    for (int nb : nbs[a]) if (nb != p) {
        dist[nb][run] = dist[a][run] + 1;
        DFS(nb, a, run);
        if (in_dia[nb]) {
            in_dia[a] = 1;
            dia.pb(a);
        }
    }
}

void DFS2(int a, int p) {
    for (int nb : nbs[a]) if (nb != p) {
        DFS2(nb, a);
        if (in_dia[nb]) {
            in_dia[a] = 1;
            dia.pb(a);
        }
    }
    if (dist[a][1] == D && !size(dia)) {
        dia.pb(a);
        in_dia[a] = 1;
    }
}

void solve() {
    cin >> N;
    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    DFS(1, 0, 0);
    int maxdist = 1;
    for (int i = 1; i <= N; i++) {
        if (dist[i][0] > dist[maxdist][0]) maxdist = i;
    }

    // cout << maxdist << endl;

    DFS(maxdist, 0, 1);

    for (int i = 1; i <= N; i++) {
        D = max(D, dist[i][1]);
    }
    
    DFS2(maxdist, 0);

    // for (int n : dia) cout << n << " ";
    // cout << endl;

    // cout << D << " " << size(dia) << endl;
    assert(size(dia) == D + 1);

    int o1, o2, o3;
    o1 = o2 = o3 = 0;
    for (int i = 1; i < size(dia) - 1; i++) {
        if (size(nbs[dia[i]]) > 2 && !o1) {
            o1 = dia[i - 1];
            o2 = dia[i];
            o3 = dia[i + 1];
            if (i - 1 + 1 < (size(dia) - 1) - (i + 1) + 1) {
                swap(o1, o3);
            }
            int buddy = 0;
            for (int nb : nbs[o2]) if (nb != o1 && nb != o3) buddy = nb;
            o3 = buddy;
        }
    }

    if (o1) cout << o1 << " " << o2 << " " << o3 << endl;
    else cout << -1 << endl;
    
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