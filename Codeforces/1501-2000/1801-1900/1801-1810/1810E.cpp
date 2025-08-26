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

struct DSU {
    vector<int> p, sz;

    DSU() {DSU(0);}
    DSU(int n) {
        p.resize(n + 1);
        sz.resize(n + 1);
        for (int i = 1; i <= n; i++) p[i] = i, sz[i] = 1;
    }

    int root(int a) {return p[a] = (a == p[a] ? a : root(p[a]));}
    int combine(int a, int b) {
        a = root(a), b = root(b);
        if (a == b) return 0;

        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return 1;
    }
};

int N, M;
int arr[MAXN];
vector<int> members[MAXN];
vector<int> nbs[MAXN];
int alive[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        arr[i] = alive[i] = 0;
        members[i].clear();
        nbs[i].clear();
    }
    members[0].clear();
}

void solve() {
    cin >> N >> M;
    DSU dsu(N);
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
        members[arr[i]].pb(i);
    }
    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    for (int n : members[0]) alive[n] = 1;
    for (int n : members[0]) for (int nb : nbs[n]) 
        if (arr[nb] == 0) dsu.combine(n, nb);

    for (int i = 1; i <= N; i++) {
        for (int n : members[i]) {
            // cout << n << endl;
            for (int nb : nbs[n]) if (arr[n] >= arr[nb]) {
                if ((alive[dsu.root(n)] && i <= dsu.sz[dsu.root(n)]) || 
                    (alive[dsu.root(nb)] && i <= dsu.sz[dsu.root(nb)])) {
                    // cout << "alive" << endl;
                    dsu.combine(n, nb);
                    alive[dsu.root(n)] = 1;
                }
                else {
                    dsu.combine(n, nb);
                    // if (too_big) cout << "too big" << endl;
                    alive[dsu.root(n)] = 0;
                }
            }
        }
    }

    if (dsu.sz[dsu.root(1)] == N && alive[dsu.root(1)]) cout << "YES" << endl;
    else cout << "NO" << endl;

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