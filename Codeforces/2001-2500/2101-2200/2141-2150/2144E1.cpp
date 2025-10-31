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

const int MAXN = 5010;
int N;
int arr[MAXN];
ll dpf[MAXN][MAXN];
ll fa[MAXN];
ll dpb[MAXN][MAXN];

void reset_tc() {
    for (int i = 0; i <= N + 1; i++) {
        arr[i] = fa[i] = 0;
        for (int j = 0; j <= N; j++) dpf[i][j] = 0;
        for (int j = 0; j <= N; j++) dpb[i][j] = 0;
    }
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    vector<int> seq;
    seq.pb(0);
    for (int i = 1; i <= N; i++) if (arr[i] > seq.back()) seq.pb(arr[i]);
    
    vector<int> seq2;
    seq2.pb(0);
    for (int i = N; i >= 1; i--) if (arr[i] > seq2.back()) seq2.pb(arr[i]);

    dpf[0][0] = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < size(seq); j++) {
            if (j > 0) {
                if (arr[i] == seq[j]) addeq(dpf[i][j], dpf[i - 1][j - 1]);
                if (arr[i] <= seq[j]) addeq(dpf[i][j], dpf[i - 1][j]);
                if (j == size(seq) - 1) addeq(fa[i], dpf[i][j]);
            }
            addeq(dpf[i][j], dpf[i - 1][j]);
        }
    }

    dpb[N + 1][0] = 1;
    for (int i = N; i >= 1; i--) {
        for (int j = 0; j < size(seq2); j++) {
            if (j > 0) {
                if (arr[i] == seq2[j]) addeq(dpb[i][j], dpb[i + 1][j - 1]);
                if (arr[i] <= seq2[j]) addeq(dpb[i][j], dpb[i + 1][j]);
            }
            addeq(dpb[i][j], dpb[i + 1][j]);
        }
    }

    // for (int i = 1; i <= N; i++) cout << dpf[i][size(seq) - 1] << " ";
    // cout << endl;
    // for (int i = 1; i <= N; i++) cout << dpb[i][size(seq2) - 2] << " ";
    // cout << endl;

    ll ans = 0;
    for (int i = 1; i <= N; i++) if (arr[i] == seq.back()) {
        addeq(ans, mult(fa[i], dpb[i + 1][size(seq2) - 2]));
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