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
int N, K;
ll w[MAXN];
int c[MAXN];
vector<int> nbs[MAXN];
set<int> ducks[MAXN];
set<int> fucked[MAXN];
int loc[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        loc[i] = c[i] = w[i] = 0;
        nbs[i].clear();
        ducks[i].clear();
        fucked[i].clear();
    }
}

// merge b into a
void stl(int a, int b) {
    int a0 = a;
    if (size(ducks[loc[a]]) < size(ducks[loc[b]])) {
        swap(loc[a], loc[b]);
    }

    for (int n : ducks[loc[b]]) {
        if (ducks[loc[a]].count(n)) fucked[a0].insert(n);
        else ducks[loc[a]].insert(n);
    }
}

ll DFS(int a, int p) {
    ll ans = 0;
    for (int nb: nbs[a]) if (nb != p) {
        ans += DFS(nb, a);
        stl(a, nb);
    }

    if (size(fucked[a]) > 1 || (size(fucked[a]) == 1 && c[a] && c[a] != *fucked[a].begin())) 
        ans += w[a];

    if (size(fucked[a]) == 1 && !c[a]) c[a] = *fucked[a].begin();
    else if (size(ducks[loc[a]]) && !c[a]) c[a] = *ducks[loc[a]].begin();
    
    if (c[a]) ducks[loc[a]].insert(c[a]);

    return ans;
}

void recolor(int a, int p) {
    if (!c[a]) c[a] = c[p];
    for (int nb : nbs[a]) if (nb != p) recolor(nb, a);
}

void solve() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> w[i];
    for (int i = 1; i <= N; i++) cin >> c[i];
    for (int i = 1; i <= N; i++) loc[i] = i;

    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    cout << DFS(1, 0) << endl;
    recolor(1, 0);
    for (int i = 1; i <= N; i++) cout << c[i] << " ";
    cout << endl;

    reset_tc();
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    c[0] = 1;

    int T;
    // T = 1;
    cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 