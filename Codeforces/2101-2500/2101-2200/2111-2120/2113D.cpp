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
int N;
int a[MAXN], b[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) a[i] = b[i] = 0;
    a[N + 1] = 0;
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> a[i];
    for (int i = 1; i <= N; i++) cin >> b[i];

    a[N + 1] = INF;

    int ans = 0;
    int lb = 1, ub = N;
    while (lb <= ub) {
        int mid = (lb + ub) >> 1;

        int fmin = N + 1, bmax = 0;
        for (int i = 1; i <= mid; i++) if (a[fmin] > a[i]) fmin = i;
        for (int i = mid + 1; i <= N; i++) if (a[bmax] < a[i]) bmax = i;

        int swapped = 0;
        if (a[fmin] < a[bmax]) {
            swapped = 1;
            swap(a[fmin], a[bmax]);
        }

        int score = 0;
        int apt = 1, bpt = 1;
        for (int i = 1; i <= N; i++) {
            if (a[apt] > b[bpt]) {
                score++;
                apt++;
            }
            else bpt++;
        }

        if (swapped) swap(a[fmin], a[bmax]);

        ans = max(ans, score);

        if (apt > mid) lb = mid + 1;
        else ub = mid - 1;
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