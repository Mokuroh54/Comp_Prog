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
int l[MAXN], r[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) arr[i] = l[i] = r[i] = 0;
}

void solve() {
    cin >> N;
    int yay = 0;
    for (int i = 1; i <= N; i++) {
        char c;
        cin >> c;
        arr[i] = c - '0';
        yay += arr[i];
    }

    if (yay & 1 || !yay) {
        cout << "NO" << endl;
        reset_tc();
        return;
    }
    cout << "YES" << endl;

    for (int i = 1; i <= N; i++) {
        l[i] = i - 1;
        r[i] = i + 1;
    }
    l[1] = N;
    r[N] = 1;

    int eated = N;
    vector<pii> edges;
    for (int j = 1; j <= 2 * N; j++) {
        int i = (j - 1) % N + 1;
        while (!arr[l[i]] && arr[i]) {
            edges.pb(pii(l[i], i));
            arr[l[i]] = 1;
            arr[i] = 0;
            l[r[i]] = l[i];
            r[l[i]] = r[i];
            eated--;
            // cerr << "eating " << l[i] << " " << i << endl;
            i = l[i];
        }
        while (!arr[r[i]] && arr[i]) {
            edges.pb(pii(r[i], i));
            arr[r[i]] = 1;
            arr[i] = 0;
            l[r[i]] = l[i];
            r[l[i]] = r[i];
            // cerr << "eating " << r[i] << " " << i << endl;
            eated--;
            i = r[i];
        }
    }

    assert(!(eated & 1));

    int s = 0;
    for (int i = 1; i <= N; i++) if (arr[i]) s = i;
    int s0 = s;
    for (int i = 0; i < eated - 1; i++) {
        edges.pb(pii(s0, l[s]));
        // cerr << "ducking " << s0 << " " << l[s] << endl;
        s = l[s];
    }

    for (pii p : edges) cout << p.FF << " " << p.SS << endl;

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