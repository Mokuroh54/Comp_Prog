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
ll MOD = 998244353;

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

const int MAXN = 0;

ll w[(1 << 20)][20][2];
struct Poly {
    static void init_w() {
        ll g = 3;
        ll ginv = power(g, MOD - 2);

        for (int i = 0; i < 20; i++) {
            w[0][i][0] = 1;
            w[0][i][1] = 1;

            ll t = power(g, (MOD - 1) / (1 << (i + 1)));
            for (int j = 1; j < (1 << i); j++) w[j][i][0] = mult(w[j - 1][i][0], t);

            ll t2 = power(ginv, (MOD - 1) / (1 << (i + 1)));
            for (int j = 1; j < (1 << i); j++) w[j][i][1] = mult(w[j - 1][i][1], t2);
        }
    }

    static void dft(vector<ll> &a, int tot, bool inv) {
        int sz = (1 << tot);
        for (int i = 1, j = 0; i < sz; i++) {
            int bit = sz >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }

        if (!w[0][0][0]) init_w();

        for (int i = 0; i < tot; i++) {
            for (int j = 0; j < sz; j += (1 << (i + 1))) {
                for (int k = 0; k < (1 << i); k++) {
                    ll v = mult(w[k][i][inv], a[j + k + (1 << i)]);
                    a[j + k + (1 << i)] = sub(a[j + k], v);
                    a[j + k] = add(a[j + k], v);
                }
            }
        }

        if (inv) {
            ll szinv = power(sz, MOD - 2);
            for (int i = 0; i < sz; i++) multeq(a[i], szinv);
        }
    }

    static vector<ll> slowmult(vector<ll> &a, vector<ll> &b) {
        vector<ll> c(size(a) + size(b) - 1);

        for (int i = 0; i < size(a); i++) for (int j = 0; j < size(b); j++)
            addeq(c[i + j], mult(a[i], b[j]));

        return c;
    }

    static vector<ll> pmult(vector<ll>& a, vector<ll>& b) {
        if (1ll * size(a) * size(b) <= 1000000) return slowmult(a, b);
        int tot = 32 - __builtin_clz(size(a) + size(b) - 1);
        if (size(a) == 1 && size(b) == 1) tot = 0;

        a.resize(1 << tot);
        b.resize(1 << tot);

        dft(a, tot, 0);
        dft(b, tot, 0);

        vector<ll> c(1 << tot);

        for (int i = 0; i < 1 << tot; i++) c[i] = mult(a[i], b[i]);

        dft(c, tot, 1);
        c.resize(size(a) + size(b) - 1);
        return c;
    }
};

struct Comb {
    vector<ll> fact, factinv;
    vector<vector<int>> stirling;
    /* 
    stirling numbers of the first kind
    s[i][j] = jth coefficient of x risepow i
    s[i][j] = number of permutations length i with j cycles
    */
    vector<vector<int>> stirling2;
    /*
    stirling numbers of the second kind
    s2[i][j] = jth coefficient of x fallpow i
    s2[i][j] = number of ways to partition i elements into j subsets
    */
 
    Comb(int x) {
        fact.resize(x + 1);
        factinv.resize(x + 1);
        fact[0] = 1;
        for (int i = 1; i <= x; i++) fact[i] = mult(i, fact[i - 1]);
        factinv[x] = divide(1, fact[x]);
        for (int i = x - 1; i >= 0; i--) 
            factinv[i] = mult(factinv[i + 1], i + 1);
    }
 
    void gen_stirling(int i, int j) {
        stirling.resize(i + 1);
        for (auto& n : stirling) n.resize(j + 1);
        stirling[0][0] = 1;
        for (int n = 0; n <= i; n++) for (int k = 0; k <= n; k++) {
            if (n && k)
                stirling[n][k] = add(mult(sub(0, n - 1), stirling[n - 1][k]), stirling[n - 1][k - 1]);
        }
    }
 
 
    void gen_stirling2(int i, int j) {
        stirling2.resize(i + 1);
        for (auto& n : stirling2) n.resize(j + 1);
        for (int n = 0; n <= i; n++) for (int k = 0; k <= n; k++) {
            if (n == k) stirling2[n][k] = 1;
            if (n && k) 
                stirling2[n][k] = add(stirling2[n - 1][k - 1], mult(k, stirling2[n - 1][k]));
        }
    }
 
    ll choose(int a, int b) {
        return mult(fact[a], mult(factinv[b], factinv[a - b]));
    }
 
    ll fallpow(int a, int b) {
        return mult(fact[a], factinv[a - b]);
    }
 
    ll stars_bars(int n, int k) {
        return choose(n + k - 1, k - 1);
    }
};

int N, A, B, C;
Poly p;
Comb comb(300000);

void reset_tc() {

}

void solve() {
    cin >> N >> A >> B >> C;
    vector<ll> a(N + 1);
    for (int i = 0; i * A <= N; i++) a[i * A] = 1;
    vector<ll> b(N + 1);
    for (int i = 0; i * B <= N; i++) b[i * B] = 1;
    vector<ll> c(N + 1);
    for (int i = 0; i * C <= N; i++) c[i * C] = 1;

    vector<ll> res;
    res = p.pmult(a, b);
    res.resize(N + 1);
    vector<ll> res2;
    res2 = p.pmult(res, c);

    cout << res2[N] << endl;

    a.clear();
    b.clear();
    c.clear();
    a.resize(N + 1);
    b.resize(N + 1);
    c.resize(N + 1);
    for (int i = 0; i * A <= N; i++) a[i * A] = comb.factinv[i * A];
    for (int i = 0; i * B <= N; i++) b[i * B] = comb.factinv[i * B];
    for (int i = 0; i * C <= N; i++) c[i * C] = comb.factinv[i * C];
    res = p.pmult(a, b);
    res.resize(N + 1);
    res2 = p.pmult(res, c);

    cout << mult(comb.fact[N], res2[N]) << endl;

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