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

const int MAXN = 200010;
int N, K;
ll arr[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) arr[i] = 0;
}

void solve() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    ll lb = 0, ub = 1000000, gans = LINF;
    while (lb <= ub) {
        ll mid = (lb + ub) / 2;

        vector<ll> smaller, midder, larger;
        ll sv = 0, lv = 0;
        for (int i = 1; i <= N; i++) {
            if (arr[i] <= mid - K) {
                smaller.pb(arr[i]);
                sv += (mid - K) - arr[i];
            }
            else if (arr[i] >= mid) {
                larger.pb(arr[i]);
                lv += arr[i] - mid;
            }
            else midder.pb(arr[i]);
        }

        if (sv > lv) {
            if (sv - lv <= size(larger)) {
                ll ans = sv * K;
                for (int i = 0; i < size(larger); i++) {
                    if (i < sv - lv) ans += (mid) * (mid - 1) / 2;
                    else ans += (mid) * (mid + 1) / 2;
                }
                for (int i = 0; i < size(smaller); i++) {
                    ans += (mid - K) * (mid - K + 1) / 2;
                }
                for (int i = 0; i < size(midder); i++) {
                    ans += (midder[i]) * (midder[i] + 1) / 2;
                }
                // if (ans < gans) cout << "better at " << mid << endl;
                gans = min(gans, ans);
            }

            ub = mid - 1;
        }
        else {
            if (lv - sv <= size(smaller)) {
                ll ans = lv * K;
                for (int i = 0; i < size(smaller); i++) {
                    if (i < lv - sv) ans += (mid - K + 2) * (mid - K + 1) / 2;
                    else ans += (mid - K) * (mid - K + 1) / 2;
                }
                for (int i = 0; i < size(larger); i++) {
                    ans += (mid) * (mid + 1) / 2;
                }
                for (int i = 0; i < size(midder); i++) {
                    ans += (midder[i]) * (midder[i] + 1) / 2;
                }
                // if (ans < gans) cout << "better at " << mid << endl;
                gans = min(gans, ans);
            }

            lb = mid + 1;
        }
    }
    cout << gans << endl;
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