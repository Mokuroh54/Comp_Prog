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
int arr[MAXN];
int res[40][2];
int fix[40][2];

void reset_tc() {
    for (int i = 1; i <= N; i++) arr[i] = 0;
    for (int i = 0; i < 40; i++) res[i][0] = res[i][1] = fix[i][0] = fix[i][1] = 0;
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    ll sum = 0;
    for (int i = 1; i <= N; i++) sum += arr[i];
    ll avg = sum / N;

    int ans = 1;
    if (avg * N != sum) ans = 0;

    for (int i = 1; i <= N; i++) {
        int diff = arr[i] - avg;
        if (!diff) continue;
        int dir = (diff < 0);
        diff = abs(diff);

        int take = __builtin_ctz(diff);

        if (diff - (1 << take)) {
            int send = __builtin_ctz(diff + (1 << take));

            if (diff + (1 << take) - (1 << send)) ans = 0;

            fix[take][dir]++;
            fix[send][1 - dir]++;
            // cout << "eepy" << endl;
        }
        else {
            res[take][1 - dir]++;
            fix[take][1 - dir]++;
        }
    }

    // for (int i = 0; i < 3; i++) cout << fix[i][0] << " ";
    // cout << endl;
    // for (int i = 0; i < 3; i++) cout << fix[i][1] << " ";
    // cout << endl;

    for (int i = 30; i >= 0; i--) {
        int v = min(fix[i][0], fix[i][1]);
        fix[i][0] -= v;
        fix[i][1] -= v;

        int e = -1;
        if (fix[i][0]) e = 0;
        if (fix[i][1]) e = 1;

        if (e >= 0) {
            if (i && res[i - 1][1 - e] >= fix[i][e]) {
                res[i - 1][1 - e] -= fix[i][e];
                fix[i - 1][1 - e] -= fix[i][e];
                fix[i - 1][e] += fix[i][e];
            }
            else ans = 0;
        }
    }

    if (ans) cout << "Yes" << endl;
    else cout << "No" << endl;

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