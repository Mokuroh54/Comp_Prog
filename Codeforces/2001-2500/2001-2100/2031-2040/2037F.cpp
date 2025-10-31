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

const int MAXN = 100010;
int N, M, K;
int h[MAXN], pos[MAXN];
pii itvs[2 * MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) h[i] = pos[i] = 0;
}

void solve() {
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) cin >> h[i];
    for (int i = 1; i <= N; i++) cin >> pos[i];

    int ans = -1;
    int lb = 1, ub = INF;
    while (lb <= ub) {
        int mid = (lb + ub) / 2;
        // cout << mid << endl;

        for (int i = 1; i <= N; i++) {
            int max_away = INF;
            max_away = M - (h[i] + mid - 1) / mid;

            if (max_away >= 0) {
                itvs[2 * i - 1] = pii(pos[i] - max_away, -1);
                itvs[2 * i] = pii(pos[i] + max_away + 1, 1);
            }
            // cout << pos[i] - max_away << " " << pos[i] + max_away << endl;
        }

        sort(itvs + 1, itvs + 1 + 2 * N);

        int yippee = 0;
        int guys = 0;
        for (int i = 1; i <= 2 * N; i++) {
            guys -= itvs[i].SS;
            if (itvs[i].FF == itvs[i + 1].FF) continue;
            if (guys >= K) yippee = 1;
        }
        // cout << yippee << endl;

        for (int i = 1; i <= 2 * N; i++) itvs[i].FF = itvs[i].SS = 0;

        if (yippee) {
            // cout << "success" << endl;
            ans = mid;
            ub = mid - 1;
        }
        else lb = mid + 1;
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