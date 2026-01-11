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
int N, Q;
int c[MAXN];
vector<int> nbs[MAXN];
set<int> bcl[4];
int bc[MAXN];
int par[MAXN];

void DFS(int a, int p) {
    par[a] = p;
    for (int nb : nbs[a]) if (nb != p) DFS(nb, a);
}

void reset_tc() {
    for (int i = 0; i <= N; i++) {
        c[i] = bc[i] = par[i] = 0;
        nbs[i].clear();
    }
    for (int j = 0; j < 4; j++) bcl[j].clear();
}

void solve() {
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> c[i];
    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    DFS(1, 0);

    for (int i = 1; i <= N; i++) {
        for (int nb : nbs[i]) if (nb != par[i]) {
            if (c[nb]) bc[i]++;
        }
        if (c[i]) bcl[min(bc[i], 3)].insert(i);
    }

    while (Q--) {
        int a;
        cin >> a;

        if (c[a]) {
            bcl[min(bc[a], 3)].erase(a);
            if (c[par[a]]) bcl[min(bc[par[a]], 3)].erase(par[a]);
            bc[par[a]]--;
            if (c[par[a]]) bcl[min(bc[par[a]], 3)].insert(par[a]);
        }
        else {
            bcl[min(bc[a], 3)].insert(a);
            if (c[par[a]]) bcl[min(bc[par[a]], 3)].erase(par[a]);
            bc[par[a]]++;
            if (c[par[a]]) bcl[min(bc[par[a]], 3)].insert(par[a]);
        }
        c[a] = 1 - c[a];

        int bcl2 = size(bcl[2]) == 0;
        if (size(bcl[2]) == 1 && !c[par[*bcl[2].begin()]]) bcl2 = 1;

        // for (int j = 0; j < 4; j++) cout << size(bcl[j]) << " ";
        // cout << endl;

        if (!size(bcl[3]) && bcl2 && size(bcl[0]) == size(bcl[2]) + 1) cout << "Yes" << endl;
        else cout << "No" << endl;
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