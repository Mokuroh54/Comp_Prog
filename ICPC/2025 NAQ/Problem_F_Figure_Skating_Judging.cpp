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
ll ducks[MAXN];

void reset_tc() {

}

void solve() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> ducks[i];
    sort(ducks + 1, ducks + 1 + N);

    double sum = 0;
    double sumsq = 0;
    for (int i = 1; i <= K; i++) {
        sum += (double) 1.0 * ducks[i];
        sumsq += (double) 1.0 * ducks[i] * ducks[i];
    }

    double best = sumsq - 2.0 * sum * sum / K + (sum * sum) / K;
    for (int i = K + 1; i <= N; i++) {
        sum -= (double) 1.0 * ducks[i - K];
        sumsq -= (double) 1.0 * ducks[i - K] * ducks[i - K];
        sum += (double) 1.0 * ducks[i];
        sumsq += (double) 1.0 * ducks[i] * ducks[i];
        best = min(best, sumsq - 2.0 * sum * sum / K + (sum * sum) / K);
    }

    cout << fixed << setprecision(6) << best << endl;
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