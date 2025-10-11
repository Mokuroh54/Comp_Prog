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
string str;
int z[2 * MAXN];

void reset_tc() {

}

void solve() {
    cin >> N >> K;
    cin >> str;
    str = str + str;
    str = '#' + str;
    // cout << str << endl;
    int l = 1, r = 1;
    for (int i = 2; i <= 2 * N; i++) {
        if (i < r) z[i] = min(r - i, z[i - l + 1]);
        // cout << i << " preset to " << z[i] << endl;
        // cout << l << " " << r << endl;

        while (i + z[i] <= 2 * N && str[i + z[i]] == str[1 + z[i]]) {
            // cout << 1 + z[i] << " match with " << i + z[i] << endl;
            z[i]++;
        }

        if (i + z[i] > r) l = i, r = i + z[i];
        // cout << i << " " << z[i] << endl;
    }
    // cout << endl;

    for (int i = 2; i <= N; i++) if (str[i + z[i]] > str[1 + z[i]]) {
        // cout << str[i + z[i]] << " " << str[1 + z[i]] << endl;
        // cout << i - 1 << endl;
        for (int j = 1; j <= K; j++) {
            cout << str[(j - 1) % (i - 1) + 1];
        }
        cout << endl;
        reset_tc();
        return;
    }

    for (int j = 1; j <= K; j++) {
        cout << str[(j - 1) % N + 1];
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