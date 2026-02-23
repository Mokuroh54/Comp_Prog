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
int N, M, K, Q;
vector<int> treasure[MAXN];
ll dp[MAXN][4];
int kl[MAXN][4];

int on[MAXN];
int l[MAXN];
int r[MAXN];

void reset_tc() {

}

void solve() {
    cin >> N >> M >> K >> Q;
    for (int i = 1; i <= K; i++) {
        int x, y;
        cin >> x >> y;
        treasure[x].pb(y);
    }

    for (int i = 1; i <= N; i++) sort(treasure[i].begin(), treasure[i].end());

    int done_duck = 0;
    for (int i = 1; i <= N; i++) if (size(treasure[i])) done_duck = i;

    for (int i = 1; i <= Q; i++) {
        int n;
        cin >> n;
        on[n] = 1;
    }

    int lg = 0;
    for (int i = 1; i <= M; i++) {
        if (on[i]) lg = i;
        l[i] = lg;
    }
    int rg = 0;
    for (int i = M; i >= 1; i--) {
        if (on[i]) rg = i;
        r[i] = rg;
    }

    int fs = 0;
    for (int i = M; i >= 1; i--) if (on[i]) fs = i;

    for (int i = 1; i <= N; i++) dp[i][0] = dp[i][1] = dp[i][2] = dp[i][3] = LINF;
    dp[0][0] = -1;
    kl[0][0] = 1;

    for (int i = 1; i <= done_duck; i++) {
        if (!size(treasure[i])) {
            for (int j = 0; j < 4; j++) if (dp[i - 1][j] < LINF) dp[i][j] = dp[i - 1][j] + 1;
            for (int j = 0; j < 4; j++) kl[i][j] = kl[i - 1][j];
            if (i == 1) {
                kl[i][0] = fs;
                dp[i][0] += fs - 1;
            }
            continue;
        }
        
        kl[i][0] = l[treasure[i][0]];
        kl[i][1] = r[treasure[i][0]];
        kl[i][2] = l[treasure[i].back()];
        kl[i][3] = r[treasure[i].back()];

        // for (int j = 0; j < 4; j++) cout << kl[i - 1][j] << " ";
        // cout << endl;

        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) if (kl[i - 1][k] && kl[i][j]) {
                // cout << "hi " << j << " " << k << endl;
                mineq(dp[i][j], dp[i - 1][k] + 1 + abs(kl[i - 1][k] - treasure[i][0]) + 
                                                abs(treasure[i].back() - treasure[i][0]) +
                                                (i == done_duck ? 0 : abs(kl[i][j] - treasure[i].back())));
                mineq(dp[i][j], dp[i - 1][k] + 1 + abs(kl[i - 1][k] - treasure[i].back()) + 
                                                abs(treasure[i].back() - treasure[i][0]) +
                                                (i == done_duck ? 0 : abs(kl[i][j] - treasure[i][0])));
                
            }
        }
        // cout << endl;
    }

    cout << min({dp[done_duck][0], dp[done_duck][1], dp[done_duck][2], dp[done_duck][3]}) << endl;

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