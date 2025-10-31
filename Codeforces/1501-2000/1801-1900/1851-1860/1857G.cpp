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

struct KRT {
    int sz;
    vector<int> p;
    vector<ll> csz;
    vector<pii> nbs[2];

    KRT() {KRT(0);}
    KRT(int n) {
        sz = n;
        nbs[0].resize(sz + 1);
        nbs[1].resize(sz + 1);
        p.resize(sz + 1);
        csz.resize(sz + 1);
        for (int i = 1; i <= sz; i++) {
            p[i] = i;
            csz[i] = 1;
        }
    }

    int root(int a) {
        if (a == p[a]) return a;
        return p[a] = root(p[a]);
    }

    int combine(int a, int b, int c) {
        a = root(a), b = root(b);
        if (a == b) return 0;

        sz++;
        p.pb(sz);
        p[a] = p[b] = sz;
        
        csz.pb(csz[a] + csz[b]);
        nbs[0].pb(pii(a, c));
        nbs[1].pb(pii(b, c));
        return 1;
    }
};

const int MAXN = 200010;
int N, S;
struct Edge {
    int a, b, c;
} edgelist[MAXN];
int sz[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        sz[i] = 0;
        edgelist[i] = {0, 0, 0};
    }
}

bool Comp(const Edge& e1, const Edge& e2) {
    return e1.c < e2.c;
}

void solve() {
    cin >> N >> S;
    int biggy = 0;
    for (int i = 1; i < N; i++) cin >> edgelist[i].a >> edgelist[i].b >> edgelist[i].c;

    sort(edgelist + 1, edgelist + N, Comp);

    KRT krump(N);
    for (int i = 1; i < N; i++) krump.combine(edgelist[i].a, edgelist[i].b, edgelist[i].c);

    ll ans = 1;
    for (int i = 2 * N - 1; i > N; i--) {
        // cout << "consdering edge with weight " << krump.nbs[0][i].SS << endl;
        ll edgepairs = krump.csz[krump.nbs[0][i].FF] * krump.csz[krump.nbs[1][i].FF];
        // cout << S - krump.nbs[0][i].SS + 1 << " " << edgepairs - 1 << endl;
        multeq(ans, power(S - krump.nbs[0][i].SS + 1, sub(edgepairs, 1)));
    }
    cout << ans << endl;
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