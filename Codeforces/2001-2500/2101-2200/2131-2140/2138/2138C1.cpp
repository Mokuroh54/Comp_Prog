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

const int MAXN = 1010;
int N, K;
vector<int> nbs[MAXN];
int dsz[MAXN];
int leaved[MAXN];
int D;
int dp[MAXN][MAXN];

void reset_tc() {
    D = 0;
    for (int i = 0; i <= N; i++) {
        dsz[i] = leaved[i] = 0;
        nbs[i].clear();
        for (int j = 0; j <= K; j++) dp[i][j] = 0;
    }
}

void DFS(int a, int p, int d) {
    dsz[d]++;
    D = max(d, D);
    for (int nb : nbs[a]) DFS(nb, a, d + 1);
    if (!size(nbs[a])) leaved[d + 1] = 1;
}

void solve() {
    cin >> N >> K;
    for (int i = 2; i <= N; i++) {
        int n;
        cin >> n;
        nbs[n].pb(i);
    }

    DFS(1, 0, 0);

    int ans = 1;
    // use 1 as root
    if (K < N) {
        dp[0][0] = 1; 
        int dsum = 1;
        for (int i = 1; i <= D; i++) {
            // cout << dsz[i] << " " << dsz[i - 1] << endl;
            if (leaved[i]) break;
            for (int k = 0; k <= K; k++) {
                if (k >= dsz[i] && dp[i - 1][k - dsz[i]]) dp[i][k] = 1;
                // cout << dsum - k << " " << N - K << endl;
                if (N - K - (dsum - k) >= dsz[i] && dp[i - 1][k]) dp[i][k] = 1;
                if (dp[i][k]) {
                    // cout << "can reach level " << i << " with " << k << " zeros " << endl;
                    ans = max(ans, i + 1);
                }
            }
            dsum += dsz[i];
        }
    }

    for (int i = 1; i <= D; i++) for (int k = 0; k <= K; k++) dp[i][k] = 0;

    // cout << "zroot" << endl;

    // use 0 as root
    dp[0][0] = 0;
    if (K) {
        dp[0][1] = 1;
        int dsum = 1;
        for (int i = 1; i <= D; i++) {
            if (leaved[i]) break;
            // cout << i << endl;
            for (int k = 1; k <= K; k++) {
                if (k >= dsz[i] && dp[i - 1][k - dsz[i]]) {
                    // cout << "trigger: " << i << " " << k << endl;
                    dp[i][k] = 1;
                    // cout << "dpv is: " << dp[i][k] << endl;
                }
                // cout << k << " zeros " << dsum - k << " " << N - K << endl;
                if (N - K - (dsum - k) >= dsz[i] && dp[i - 1][k]) {
                    // cout << "trigger: " << i << " " << k << endl;
                    dp[i][k] = 1;
                    // cout << "dpv is: " << dp[i][k] << " " << dp[i - 1][k] << endl;
                }
                if (dp[i][k]) {
                    // cout << "can reach level " << i << " with " << k << " zeros " << endl;
                    ans = max(ans, i + 1);
                }
            }
            dsum += dsz[i];
        }
    }
    dp[0][1] = 0;

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