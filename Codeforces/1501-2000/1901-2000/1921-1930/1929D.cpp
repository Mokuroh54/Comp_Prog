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

#define add(a, b) ((a + b) >= MOD ? a + b - MOD : a + b)
#define sub(a, b) ((a - b) >= 0 ? a - b : a + MOD - b)
#define mult(a, b) ((a * b) % MOD)
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
#define divide(a, b) ((a * power(b, MOD - 2)) % MOD)

#define maxeq(x, y) if (x < y) x = y
#define mineq(x, y) if (x > y) x = y
#define addeq(x, y) x = add(x, y)
#define subeq(x, y) x = sub(x, y)
#define multeq(x, y) x = mult(x, y)
#define diveq(x, y) x = divide(x, y)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 300010;
int N;
vector<int> nbs[MAXN];
ll dp[MAXN][2][3];

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        nbs[i].clear();
        dp[i][0][1] = dp[i][0][2] = dp[i][1][0] = dp[i][1][1] = 0;
    }
}

void DFS(int a, int p) {
    dp[a][1][0] = 1;

    if (size(nbs[a]) > 1 || (a == 1 && size(nbs[a]))) dp[a][0][1] = 1;

    for (int nb : nbs[a]) if (nb != p) {
        DFS(nb, a);
        multeq(dp[a][0][1], add(1, add(dp[nb][1][0], dp[nb][0][1])));
        addeq(dp[a][1][1], add(dp[nb][1][0], dp[nb][0][1]));
        addeq(dp[a][0][2], add(dp[nb][0][2], dp[nb][1][1]));
    }

    if (size(nbs[a]) > 1 || (a == 1 && size(nbs[a]))) subeq(dp[a][0][1], 1);

    // cout << a << " " << dp[a][0][1] << " " << dp[a][0][2] << " " 
    //      << dp[a][1][0] << " " << dp[a][1][1] << endl;
}

void solve() {
    cin >> N;
    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    DFS(1, 1);
    cout << add(1, add(add(dp[1][0][1], dp[1][0][2]), add(dp[1][1][0], dp[1][1][1]))) << endl;
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