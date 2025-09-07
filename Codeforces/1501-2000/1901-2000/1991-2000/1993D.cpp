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

const int MAXN = 500010;
int N, K;
int arr[MAXN];
int narr[MAXN];
int dp[MAXN];

void reset_tc() {

}

int solve(int mid) {
    for (int i = 1; i <= N; i++) {
        if (arr[i] >= mid) narr[i] = 1;
    }

    int tans = 0;
    for (int i = 1; i <= N; i++) {
        if (i % K != 1) dp[i] = max(dp[i], dp[i - 1] + narr[i]);
        else dp[i] = narr[i];

        if (i > K) dp[i] = max(dp[i], dp[i - K]);
        // cout << dp[i] << " ";
        if (i % K == N % K) tans = max(tans, dp[i]);
    }
    // cout << endl;

    return tans;
}

void solve() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    int ans = 0;
    int lb = 1, ub = INF;
    while (lb <= ub) {
        int mid = (lb + ub) / 2;

        int rem = (N - 1) % K + 1;
        int tans = solve(mid);

        // cout << rem << " " << (rem + 1) / 2 << endl;
        // cout << tans << " " << (rem + 1) / 2 << endl;

        // cout << rem << " " << tans << endl;

        if (tans >= (rem + 2) / 2) {
            ans = mid;
            lb = mid + 1;
        }
        else ub = mid - 1;

        for (int i = 1; i <= N; i++) narr[i] = dp[i] = 0;
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