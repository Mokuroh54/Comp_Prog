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

struct BIT {
    vector<ll> arr;

    BIT() {arr.resize(0);}
    BIT(int n) {arr.resize(n + 1);}

    void update(int a, ll v) {
        if (!a) return;
        while (a < size(arr)) {
            arr[a] += v;
            a += (a & -a);
        }
    }

    ll query(int a) {
        ll ans = 0;
        while (a) {
            ans += arr[a];
            a -= (a & -a);
        }
        return ans;
    }

    ll query(int a, int b) {return query(b) - query(a - 1);}

    void clear() {
        arr.resize(0);
    }
};

int N, Q;
int a[MAXN], b[MAXN];
pii aactive[MAXN];
pii bactive[MAXN];
struct Rng {
    int s, e, i;
} rngs[MAXN];
int ans[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) 
        a[i] = b[i] = aactive[i].FF = aactive[i].SS = bactive[i].FF = bactive[i].SS = 0;
    for (int i = 1; i <= Q; i++) rngs[i].s = rngs[i].e = rngs[i].i = ans[i] = 0;
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        char c;
        cin >> c;
        a[i] = c - '0';
    }
    for (int i = 1; i <= N; i++) {
        char c;
        cin >> c;
        b[i] = c - '0';
    }

    cin >> Q;
    for (int i = 1; i <= Q; i++) {
        cin >> rngs[i].s >> rngs[i].e;
        rngs[i].i = i;
    }

    for (int i = 1; i <= N; i++) {
        if (a[i]) aactive[i] = pii(i, i);
        if (b[i]) bactive[i] = pii(i, i);
    }

    for (int i = 2; i <= N; i++) if (!a[i - 1] && !a[i + 1] && !b[i]) {
        b[i] = 1;
        bactive[i] = pii(i - 1, i + 1);
    }

    for (int i = 2; i <= N; i++) if (b[i - 1] && b[i + 1] && !a[i]) {
        a[i] = 1;
        aactive[i] = pii(bactive[i - 1].FF, bactive[i + 1].SS);
    }

    sort(aactive + 1, aactive + 1 + N);
    sort(rngs + 1, rngs + 1 + Q, [](const Rng& r1, const Rng& r2) {
        return pii(r1.s, r1.e) < pii(r2.s, r2.e);
    });

    BIT bit(N);
    for (int i = 1; i <= N; i++) bit.update(aactive[i].SS, 1);

    int j = 1;
    for (int i = 1; i <= Q; i++) {
        while (j <= N && aactive[j].FF < rngs[i].s) {
            bit.update(aactive[j].SS, -1);
            j++;
        }
        ans[rngs[i].i] = bit.query(rngs[i].s, rngs[i].e);
    }

    for (int i = 1; i <= Q; i++) cout << ans[i] << endl;

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