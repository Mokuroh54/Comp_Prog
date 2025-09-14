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

const int MAXN = 3010;
int N, K;
int arr[MAXN];
int s0[MAXN][MAXN], e0[MAXN][MAXN], s1[MAXN][MAXN], e1[MAXN][MAXN];
int pref[MAXN];
int l[MAXN];
int ans[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) for (int j = 0; j <= N; j++) {
        s0[i][j] = e0[i][j] = s1[i][j] = e1[i][j] = 0;
    }
    for (int i = 0; i <= N; i++) arr[i] = pref[i] = l[i] = ans[i] = 0;
}

void solve() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        char c;
        cin >> c;
        arr[i] = c - '0';
    }

    int sum = 0;
    for (int i = 1; i <= N; i++) {
        sum += arr[i];
        if (sum && !pref[sum]) pref[sum] = i;

        for (int j = 0; j <= sum; j++) {
            s0[i][j] = i - pref[sum - j];
        }
    }
    for (int i = 1; i <= N; i++) pref[i] = 0;

    sum = 0;
    for (int i = 1; i <= N; i++) {
        sum += 1 - arr[i];
        if (sum && !pref[sum]) pref[sum] = i;

        for (int j = 0; j <= sum; j++) {
            s1[i][j] = i - pref[sum - j];
        }
    }
    for (int i = 1; i <= N; i++) pref[i] = 0;
    pref[0] = N + 1;

    sum = 0;
    for (int i = N; i >= 1; i--) {
        sum += arr[i];
        if (sum && !pref[sum]) pref[sum] = i;

        for (int j = 0; j <= sum; j++) {
            e0[i][j] = pref[sum - j] - i;
        }
    }
    for (int i = 1; i <= N; i++) pref[i] = 0;

    sum = 0;
    for (int i = N; i >= 1; i--) {
        sum += 1 - arr[i];
        if (sum && !pref[sum]) pref[sum] = i;

        for (int j = 0; j <= sum; j++) {
            e1[i][j] = pref[sum - j] - i;
        }
    }
    for (int i = 1; i <= N; i++) pref[i] = 0;
    pref[0] = 0;

    for (int j = 0; j <= K; j++) {
        for (int i = 1; i <= N; i++) {
            maxeq(s0[i][j], s0[i - 1][j]);
            maxeq(s1[i][j], s1[i - 1][j]);
        }
        for (int i = N; i >= 1; i--) {
            maxeq(e0[i][j], e0[i + 1][j]);
            maxeq(e1[i][j], e1[i + 1][j]);
        }
    }

    int maxguy = 0;
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            // cout << i << " " << j << " " << s0[i][j] << " " << e1[i + 1][K - j] << endl;
            maxeq(l[s0[i][j]], e1[i + 1][K - j]);
            maxeq(l[e0[i + 1][j]], s1[i][K - j]);
            maxeq(maxguy, s0[i][j]);
            maxeq(maxguy, e0[i + 1][j]);
        }
    }

    for (int j = 1; j <= N; j++) {
        for (int i = 0; i <= maxguy; i++) {
            maxeq(ans[j], i * j + l[i]);
        }
        cout << ans[j] << " ";
    }
    cout << endl;

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