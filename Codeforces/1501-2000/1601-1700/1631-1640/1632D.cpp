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
int arr[MAXN][30];

void reset_tc() {
    for (int i = 1; i <= N; i++) for (int j = 0; j <= 29; j++) arr[i][j] = 0;
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i][0];

    for (int i = N; i >= 1; i--) {
        for (int j = 1; j <= 29; j++) {
            if (i + (1 << (j - 1)) <= N) {
                arr[i][j] = gcd(arr[i][j - 1], arr[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    vector<pii> oops;
    for (int i = 1; i <= N; i++) {
        int alr = 0;
        int idx = i;
        for (int j = 29; j >= 0; j--) {
            if (idx + (1 << j) <= N + 1) {
                // cout << idx << " " << j << endl;
                int alr2 = gcd(alr, arr[idx][j]);
                // cout << alr << " " << arr[idx][j] << endl;
                if (alr2 > idx + (1 << j) - i) {
                    // cout << idx << " " << j << " tall " << endl;
                    alr = alr2;
                    idx += (1 << j);
                }
                else if (alr2 == idx + (1 << j) - i) {
                    // cout << idx << " " << j << " good " << endl;
                    oops.pb(pii(i, idx + (1 << j) - 1));
                    break;
                }
                else {
                    // cout << idx << " " << j << " short " << endl;
                }
            }
        }
    }

    for (pii p : oops) swap(p.FF, p.SS);
    sort(oops.begin(), oops.end());
    for (pii p : oops) swap(p.FF, p.SS);

    deque<int> guys;
    guys.pb(0);
    for (pii p : oops) {
        if (p.FF > guys.back()) guys.pb(p.SS);
    }

    int j = 1;
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        if (j < size(guys) && i == guys[j]) {
            ans++;
            j++;
        }
        cout << ans << " ";
    }
    cout << endl;

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