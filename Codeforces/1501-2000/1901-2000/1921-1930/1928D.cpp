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

const int MAXN = 200010;
int N;
ll B, X;
int arr[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) arr[i] = 0;
}

ll solve(int a) {
    ll cost = X * (1 - a) * 2;
    for (int i = 1; i <= N; i++) {
        int m = arr[i] % a;
        ll tcost = 0;
        tcost += B * (m * ((arr[i] + a - 1) / a)) * (arr[i] - (arr[i] + a - 1) / a);
        tcost += B * ((a - m) * (arr[i] / a)) * (arr[i] - arr[i] / a);
        cost += tcost;
    }
    return cost / 2;
}

void solve() {
    cin >> N >> B >> X;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    int lb = 1, ub = 200000;
    ll ans = 0;
    while (lb <= ub) {
        int m1 = lb + (ub - lb) / 3;
        int m2 = ub - (ub - lb) / 3;

        ll m1a = solve(m1);
        ll m2a = solve(m2);

        ans = max({ans, m1a, m2a});

        if (m1a < m2a) lb = m1 + 1;
        else ub = m2 - 1;
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