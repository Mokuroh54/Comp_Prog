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

const int MAXN = 100010;
int N, K;
int arr[MAXN];
ll dp[370][370];
ll tmp[370][370];
ll tmp2[370];
int pv[MAXN], nv[MAXN];

void reset_tc() {
    for (int m = 0; m <= K; m++) for (int s = 0; s <= K; s++)
        dp[m][s] = 0;
    
    for (int i = 0; i <= N + 1; i++) arr[i] = pv[i] = nv[i] = 0;
}

void solve() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    int id = 0;
    for (int i = 1; i <= N; i++) if (arr[i] > arr[id]) {
        nv[id] = i;
        pv[i] = id;
        id = i;
    }
    nv[id] = N + 1;
    pv[N + 1] = id;

    for (int i = id; i >= 1; i = pv[i]) {
        for (int m = 0; m <= K; m++) for (int s = m; s <= K; s++) 
            tmp[m][s] = -LINF;
        
        for (int s = 0; s <= K; s++) tmp2[s] = -LINF;
        
        for (int m = 0; m <= arr[i]; m++) for (int s = m; s <= K; s++) {
            maxeq(tmp2[s - m], dp[m][s] + 1ll * m * (nv[i] - i));
        }
        
        for (int m2 = 0; m2 < arr[i]; m2++) for (int s = 0; s <= K; s++) {
            maxeq(tmp[m2][s], tmp2[s]);
        }
        for (int m = 0; m <= K; m++) for (int s = m; s <= K; s++) {
            maxeq(dp[m][s], max(dp[m][s] + 1ll * m * (nv[i] - i), tmp[m][s]));
        }
    }

    cout << dp[0][0] << endl;
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