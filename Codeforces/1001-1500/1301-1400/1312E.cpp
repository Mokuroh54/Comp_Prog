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

const int MAXN = 510;
int N;
int arr[MAXN];
pii dp[MAXN][MAXN];
int ans[MAXN][MAXN];

void reset_tc() {

}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    for (int i = 1; i <= N; i++) {
        ans[i][i] = 1;
        dp[i][i].FF = arr[i];
        dp[i][i].SS = 1;
    }
    for (int l = 2; l <= N; l++) {
        for (int i = 1; i + l - 1 <= N; i++) {
            int j = i + l - 1;
            ans[i][j] = INF;
            for (int k = i; k < j; k++) {
                // cout << i << " " << k << " " << j << endl;
                int vals_match = dp[i][k].FF != 0 && dp[i][k].FF == dp[k + 1][j].FF;
                int expandable = (dp[i][k].SS) && (dp[k + 1][j].SS);
                if (vals_match && expandable) {
                    dp[i][j].FF = dp[i][k].FF + 1;
                    dp[i][j].SS = 1;
                    mineq(ans[i][j], ans[i][k] + ans[k + 1][j] - 1);
                }
                else mineq(ans[i][j], ans[i][k] + ans[k + 1][j]);
            }
        }
    }

    cout << ans[1][N] << endl;

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