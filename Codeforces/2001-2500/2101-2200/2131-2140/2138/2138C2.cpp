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
int N, K;
int dsz[MAXN], leaved[MAXN], spoogy[MAXN];
int c[510];

void reset_tc() {
    for (int i = 0; i <= N; i++) c[i] = dsz[i] = leaved[i] = spoogy[i] = 0;
}

void solve() {
    cin >> N >> K;
    dsz[0] = 1;
    for (int i = 2; i <= N; i++) {
        int n;
        cin >> n;
        spoogy[i] = spoogy[n] + 1;
        dsz[spoogy[i]]++;
        leaved[n]++;
    }
    int D = INF;
    for (int i = 1; i <= N; i++) if (!leaved[i]) mineq(D, spoogy[i]);
    // cout << "D is: " << D << endl;
    int req = 0;
    for (int i = 0; i <= D; i++) req += dsz[i];
    // cout << req << endl;

    vector<int> special;
    for (int i = 0; i <= D; i++) {
        if (dsz[i] <= 500) c[dsz[i]]++;
        else special.pb(dsz[i]);
    }

    bitset<MAXN> dp;
    dp[0] = 1;
    for (int i = 1; i <= 500; i++) {
        for (int j = 0; j < 20; j++) {
            if ((1 << j) <= c[i]) {
                dp |= dp << ((1 << j) * i);
                c[i] -= 1 << j;
            }
        }
        if (c[i]) dp |= dp << (c[i] * i);
    }
    for (int j : special) dp |= dp << j;
    // cout << "friends: " << dp.count() << endl;

    if (2 * K <= N) K = N - K;
    // cout << K << endl;

    int ans = 0;
    for (int i = max(0, req + K - N); i <= K; i++) if (dp[i]) ans = 1;

    // cout << "friends: " << dp.count() << endl;

    if (ans) cout << D + 1 << endl;
    else cout << D << endl;
    
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