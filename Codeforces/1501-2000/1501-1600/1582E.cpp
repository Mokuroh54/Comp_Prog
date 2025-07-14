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

const int MAXN = 100010;
const int MAXS = 460;
int N;
ll arr[MAXN];
ll psum[MAXN];
ll dp[MAXN][MAXS];

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j * (j + 1) / 2 <= N; j++) dp[i][j] = 0;
    }
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= N; i++) psum[i] = arr[i] + psum[i - 1];

    for (int i = N; i >= 1; i--) dp[i][1] = max(dp[i + 1][1], arr[i]);
    int high = 1;
    for (int j = 2; j * (j + 1) / 2 <= N; j++) {
        for (int i = N - j; i >= 1; i--) {
            if ((dp[i + j][j - 1] && psum[i + j - 1] - psum[i - 1] < dp[i + j][j - 1])) {
                dp[i][j] = psum[i + j - 1] - psum[i - 1];
                high = j;
                // cout << i << " " << j << endl;
            }
            if (dp[i + 1][j]) {
                if (dp[i][j]) dp[i][j] = max(dp[i][j], dp[i + 1][j]);
                else dp[i][j] = dp[i + 1][j];
                high = j;
                // cout << i << " " << j << endl;
            }
        }
    }

    cout << high << endl;
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