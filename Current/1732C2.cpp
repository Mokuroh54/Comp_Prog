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
int N, Q;
ll arr[MAXN];
ll psum[MAXN];
int lv[MAXN];
int rv[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) arr[i] = psum[i] = lv[i] = rv[i] = 0;
}

void solve() {
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    int nz = 0;
    for (int i = 1; i <= N; i++) {
        lv[i] = nz;
        if (arr[i]) nz = i;
    }
    nz = N + 1;
    for (int i = N; i >= 1; i--) {
        rv[i] = nz;
        if (arr[i]) nz = i;
    }

    // for (int i = 1; i <= N; i++) cout << lv[i] << " ";
    // cout << endl;
    // for (int i = 1; i <= N; i++) cout << rv[i] << " ";
    // cout << endl;

    for (int i = 1; i <= N; i++) psum[i] = arr[i] ^ psum[i - 1];

    while (Q--) {
        int L0, R0;
        cin >> L0 >> R0;
        int L = L0, R = R0;
        if (!arr[L0]) L = rv[L];
        if (!arr[R0]) R = lv[R];
        if (L > R) {
            cout << L0 << " " << L0 << endl;
            continue;
        }
        pii min_len = pii(L, R);

        ll duck = psum[R] ^ psum[L - 1];
        for (int l = L; l <= R; l = rv[l]) {
            // cout << duck << endl;
            ll coconut = duck;
            for (int r = R; r >= L; r = lv[r]) {
                // cout << "try " << l << " " << r << endl;
                if (l > r) break;
                if (min_len.SS - min_len.FF > r - l) min_len = pii(l, r);

                if ((arr[r] | coconut) == coconut) {
                    // cout << coconut << " " << arr[r] << " " << (coconut ^ arr[r]) << endl;
                    coconut ^= arr[r]; 
                }
                else break;
            }

            if ((arr[l] | duck) == duck) {
                // cout << duck << " " << arr[l] << " " << (duck ^ arr[l]) << endl;
                duck ^= arr[l];
            }
            else break;
        }

        cout << min_len.FF << " " << min_len.SS << endl;
    }

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