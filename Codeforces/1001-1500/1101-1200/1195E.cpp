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
int N, M, A, B;
ll griddy[MAXN][MAXN];
ll minv[MAXN][MAXN];

void reset_tc() {

}

void solve() {
    cin >> N >> M >> A >> B;
    ll g, x, y, z;
    cin >> g >> x >> y >> z;
    MOD = z;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            griddy[i][j] = g;
            g = add(mult(g, x), y);
            // cout << griddy[i][j] << " ";
        }
        // cout << endl;
    }
    
    for (int j = 1; j <= M; j++) {
        deque<pll> guys;
        for (int i = 1; i < A; i++) {
            while (!guys.empty() && guys.back().FF > griddy[i][j]) guys.ppb();
            guys.pb(pll(griddy[i][j], i + A));
        }
        for (int i = A; i <= N; i++) {
            if (!guys.empty() && guys.front().SS == i) guys.ppf();
            while (!guys.empty() && guys.back().FF > griddy[i][j]) guys.ppb();
            guys.pb(pll(griddy[i][j], i + A));
            minv[i - A + 1][j] = guys.front().FF;
        }
    }
    // for (int i = 1; i <= N; i++) {
    //     for (int j = 1; j <= M; j++) {
    //         cout << minv[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    ll ans = 0;
    for (int i = 1; i <= N - A + 1; i++) {
        deque<pll> guys;
        for (int j = 1; j < B; j++) {
            while (!guys.empty() && guys.back().FF > minv[i][j]) guys.ppb();
            guys.pb(pll(minv[i][j], j + B));
        }
        for (int j = B; j <= M; j++) {
            if (!guys.empty() && guys.front().SS == j) guys.ppf();
            while (!guys.empty() && guys.back().FF > minv[i][j]) guys.ppb();
            guys.pb(pll(minv[i][j], j + B));
            ans += guys.front().FF;
        }
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
    T = 1;
    // cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 