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

const int MAXN = 1000010;
int N, M;
int arr[MAXN];
pll thash[MAXN];
pll inv27[MAXN];

void reset_tc() {

}

void solve() {
    string str;
    cin >> str;
    N = str.length();
    for (int i = 1; i <= N; i++) arr[i] = str[i - 1] - '0';
    if (arr[1] == 1) for (int i = 1; i <= N; i++) arr[i] = 1 - arr[i];

    int c0 = 0, c1 = 0;
    for (int i = 1; i <= N; i++) {
        if (!arr[i]) c0++;
        else c1++;
    }

    string tar;
    cin >> tar;
    M = tar.length();
    ll p1 = 1;
    ll p2 = 1;
    MOD = 998244353;
    ll i271 = divide(1, 27);
    MOD = 1000000007;
    ll i272 = divide(1, 27);
    inv27[0] = pll(1, 1);
    for (int i = 1; i <= M; i++) {
        thash[i].FF = (thash[i - 1].FF + p1 * (tar[i - 1] - 'a' + 1)) % 998244353;
        thash[i].SS = (thash[i - 1].SS + p2 * (tar[i - 1] - 'a' + 1)) % 1000000007;
        p1 = (p1 * 27) % 998244353;
        p2 = (p2 * 27) % 1000000007;

        inv27[i].FF = (inv27[i - 1].FF * i271) % 998244353;
        inv27[i].SS = (inv27[i - 1].SS * i272) % 1000000007;
        // cout << thash[i].FF << " " << thash[i].SS << endl;
    }

    int ans = 0;
    for (int l0 = 1; l0 <= M; l0++) {
        int ok = 0;
        if (c1) ok = (M > 1ll * l0 * c0 && (M - l0 * c0) % c1 == 0);
        else ok = M % l0 == 0;

        if (ok) {
            int l1 = (M - l0 * c0) / c1;
            // cout << l0 << " " << l1 << endl;
            int c = 1;
            int t = 0;

            pll t0 = pll(-INF, -INF);
            pll t1 = pll(-INF, -INF);
            int works = 1;
            for (; c <= N; c++) {
                if (arr[c]) {
                    t += l1;
                    pll rn;
                    rn.FF = ((thash[t].FF - thash[t - l1].FF + 998244353) * inv27[t - l1].FF) % 998244353;
                    rn.SS = ((thash[t].SS - thash[t - l1].SS + 1000000007) * inv27[t - l1].SS) % 1000000007;
                    if (t1 == pll(-INF, -INF)) t1 = rn;
                    if (t1 != rn) works = 0;
                }
                else {
                    t += l0;
                    pll rn;
                    rn.FF = ((thash[t].FF - thash[t - l0].FF + 998244353) * inv27[t - l0].FF) % 998244353;
                    rn.SS = ((thash[t].SS - thash[t - l0].SS + 1000000007) * inv27[t - l0].SS) % 1000000007;
                    if (t0 == pll(-INF, -INF)) t0 = rn;
                    if (t0 != rn) works = 0;
                }
            }
            if (works && t0 != t1) ans++;
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