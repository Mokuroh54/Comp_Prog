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

#define maxeq(x, y) x = x > y ? x : y
#define mineq(x, y) x = x < y ? x : y
#define addeq(x, y) x = add(x, y)
#define subeq(x, y) x = sub(x, y)
#define multeq(x, y) x = mult(x, y)
#define diveq(x, y) x = divide(x, y)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 5010;
int N, M;
ll X, Y;
int arr[MAXN];
int idx[MAXN];
ll dp[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) arr[i] = idx[i] = 0;
    for (int i = 0; i <= M; i++) dp[i] = 0;
    M = 0;
}

ll cost(int i, int j) {
    ll cost = X * (idx[i] - idx[j]);
    if (idx[i] - idx[j] == 1) mineq(cost, Y * 2);
    else mineq(cost, Y);
    return cost;
}

void solve() {
    cin >> N >> X >> Y;
    for (int i = 1; i <= N; i++) {
        char c;
        cin >> c;
        arr[i] = c - '0';
    }
    for (int i = 1; i <= N; i++) {
        char c;
        cin >> c;
        if (arr[i] != c - '0') idx[++M] = i;
    }

    for (int i = 2; i <= M; i++) {
        dp[i] = LINF;

        if (i & 1) {
            mineq(dp[i], dp[i - 1]);
            mineq(dp[i], dp[i - 2] + cost(i, i - 1));
                
        }
        else {
            mineq(dp[i], dp[i - 1] + Y);
            mineq(dp[i], dp[i - 2] + cost(i, i - 1));
        }
    }

    if (M & 1) cout << -1 << endl;
    else if (X >= Y) {
        if (M == 2 && idx[2] - idx[1] == 1) {
            if (N == 4 == idx[1] == 2) cout << min(Y * 3, X) << endl;
            else if (N >= 4) cout << min(Y * 2, X) << endl;
        }
        else cout << Y * M / 2 << endl;
    }
    else {
        if (dp[M] == LINF) cout << -1 << endl;
        else cout << dp[M] << endl;
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