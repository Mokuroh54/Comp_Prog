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
int N, M, A, B, C;
ll arr[MAXN];
vector<int> nbs[MAXN];
int dista[MAXN];
int distb[MAXN];
int distc[MAXN];
int vis[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        dista[i] = distb[i] = distc[i] = 0;
        nbs[i].clear();
    }
    for (int i = 1; i <= M; i++) arr[i] = 0;
}

void solve() {
    cin >> N >> M >> A >> B >> C;
    for (int i = 1; i <= M; i++) cin >> arr[i];
    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    for (int i = 1; i <= N; i++) {
        if (i != A) dista[i] = INF;
        if (i != B) distb[i] = INF;
        if (i != C) distc[i] = INF;
    }

    queue<int> search;
    search.push(A);
    while (!search.empty()) {
        int n = search.front();
        search.pop();

        if (vis[n]) continue;
        vis[n] = 1;

        for (int nb : nbs[n]) {
            dista[nb] = min(dista[nb], dista[n] + 1);
            search.push(nb);
        }
    }
    for (int i = 1; i <= N; i++) vis[i] = 0;

    search.push(B);
    while (!search.empty()) {
        int n = search.front();
        search.pop();

        if (vis[n]) continue;
        vis[n] = 1;

        for (int nb : nbs[n]) {
            distb[nb] = min(distb[nb], distb[n] + 1);
            search.push(nb);
        }
    }
    for (int i = 1; i <= N; i++) vis[i] = 0;

    search.push(C);
    while (!search.empty()) {
        int n = search.front();
        search.pop();

        if (vis[n]) continue;
        vis[n] = 1;

        for (int nb : nbs[n]) {
            distc[nb] = min(distc[nb], distc[n] + 1);
            search.push(nb);
        }
    }
    for (int i = 1; i <= N; i++) vis[i] = 0;


    sort(arr + 1, arr + 1 + M);
    for (int i = 1; i <= M; i++) arr[i] += arr[i - 1];
    ll ans = LINF;
    for (int i = 1; i <= N; i++) {
        int stoprightnow = 0;
        for (int nb : nbs[i]) if (dista[nb] < dista[i] && distc[nb] < distc[i]) 
            stoprightnow = 1;
        if (stoprightnow) continue;
        ans = min(ans, arr[distb[i]] + arr[min(M, dista[i] + distb[i] + distc[i])]);
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