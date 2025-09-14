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

const int MAXN = 200010;
int N, M;
ll V;
int arr[MAXN];
int vis[MAXN];
int d[MAXN];
vector<int> nbs[MAXN];
vector<int> cycles[MAXN];
int updog[MAXN];
int evengelion[MAXN];
int familyv[MAXN];
int trust[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        arr[i] = vis[i] = d[i] = updog[i] = 0;
        evengelion[i] = familyv[i] = trust[i] = 0;
        nbs[i].clear();
        cycles[i].clear();
    }
}

void DFS(int a, int p) {
    if (vis[a]) {
        cycles[a].pb(p);
        if (!updog[p] || d[a] < d[updog[p]]) updog[p] = a;
        return;
    }
    vis[a] = 1;
    d[a] = d[p] + 1;

    for (int nb : nbs[a]) if (nb != p) {
        // if (!vis[nb]) cout << a << " " << nb << endl;
        DFS(nb, a);
        if (!updog[a] || d[updog[a]] > d[updog[nb]]) updog[a] = updog[nb];
    }
}

void DFS2(int a, int p) {
    for (int nb : nbs[a]) if (d[nb] == d[a] + 1) {
        // cout << a << " " << nb << endl;
        DFS2(nb, a);

        if (d[updog[nb]] < d[updog[a]]) updog[a] = updog[nb];
    }
}

void solve() {
    cin >> N >> M >> V;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    for (int i = 1; i <= N; i++) updog[i] = i;

    DFS(1, 0);

    for (int i = 1; i <= N; i++) for (int cyc : cycles[i]) {
        if (!evengelion[i] && ((d[cyc] - d[i]) & 1)) evengelion[i] = 2;
        if (!((d[cyc] - d[i]) & 1)) evengelion[i] = 1;
    }

    for (int i = 1; i <= N; i++) familyv[i] = V;

    DFS2(1, 0);

    for (int i = 1; i <= N; i++) {
        while (updog[updog[i]] != updog[i]) 
            updog[i] = updog[updog[i]];
    }

    ll ans = 1;
    for (int i = 1; i <= N; i++) {
        trust[updog[i]]++;
        if (arr[i] != -1) {
            if (familyv[updog[i]] != V && arr[i] != familyv[updog[i]]) ans = 0;
            else familyv[updog[i]] = arr[i];
        }
    }

    // for (int i = 1; i <= N; i++) cout << updog[i] << " ";
    // cout << endl;

    // for (int i = 1; i <= N; i++) cout << evengelion[i] << " ";
    // cout << endl;

    for (int i = 1; i <= N; i++) {
        if (!evengelion[updog[i]]) 
            evengelion[updog[i]] = evengelion[i];
        if (evengelion[updog[i]] == 2 && evengelion[i] == 1) 
            evengelion[updog[i]] = evengelion[i];
    }

    // for (int i = 1; i <= N; i++) cout << (trust[i] > 1 ? evengelion[i] : 0) << " ";
    // cout << endl;

    // for (int i = 1; i <= N; i++) cout << trust[i] << " ";
    // cout << endl;

    for (int i = 1; i <= N; i++) if (updog[i] == i) {
        if (trust[i] > 1) {
            // cout << "trust: " << i << endl;
            // cout << trust[i] << " " << evengelion[i] << endl;
            if (evengelion[i] == 1) {
                if (familyv[i] != V && familyv[i]) ans = 0;
            }
            else if (evengelion[i] == 2) {
                if (familyv[i] == V) multeq(ans, V);
            }
        }
        else if (arr[i] == -1) {
            // cout << "let go: " << i << endl;
            multeq(ans, V);
        }
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