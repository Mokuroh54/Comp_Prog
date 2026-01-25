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
int N;
int s[MAXN], t[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) s[i] = t[i] = 0;
}

int please() {
    set<pii> so, to;
    int lz = 0;
    for (int i = 1; i <= N; i++) {
        if (s[i] == 0) {
            if (lz < i - 1) so.insert(pii(lz, i - 1));
            lz = i;
        }
    }
    if (lz < N) so.insert(pii(lz, N));
    
    lz = 0;
    for (int i = 1; i <= N; i++) {
        if (t[i] == 0) {
            if (lz < i - 1) to.insert(pii(lz, i - 1));
            lz = i;
        }
    }
    if (lz < N) to.insert(pii(lz, N));

    int works = 1;
    for (pii p : so) {
        auto it = to.lower_bound(pii(p.FF, 0));

        pii p2 = *it;
        if ()
    }

    return 0;
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        char c;
        cin >> c;
        s[i] = c - '0';
    }
    for (int i = 1; i <= N; i++) {
        char c;
        cin >> c;
        t[i] = c - '0';
    }

    int a1 = please();
    for (int i = 1; i <= N; i++) {
        s[i] = 1 - s[i];
        t[i] = 1 - t[i];
    }
    int a2 = please();
    int a = min(a1, a2);

    if (a == INF) cout << -1 << endl;
    else cout << a << endl;

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