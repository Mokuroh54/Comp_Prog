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

struct NT {
    vector<int> primes;
    vector<int> sieve;
    vector<vector<int>> divisors;
    vector<vector<pii>> factorization;

    NT(int x) {
        sieve.resize(x + 1);
        divisors.resize(x + 1);

        sieve[1] = 1;
        for (int i = 2; i <= x; i++) if (!sieve[i]) {
            primes.pb(i);
            for (int j = 2; i * j <= x; j++) sieve[i * j] = i;
        }

        // for (int i = 2; i <= x; i++) {
        //     if (!sieve[i]) {
        //         divisors[i].pb(1);
        //         divisors[i].pb(i);
        //     }
        //     else {
        //         divisors[i] = divisors[i / sieve[i]];
        //         for (int n : divisors[i / sieve[i]]) if ((i / sieve[i] / n) % sieve[i]) {
        //             divisors[i].pb(n * sieve[i]);
        //         }
        //     }
        // }

        // for (int i = 2; i <= x; i++) {
        //     if (!sieve[i]) factorization[i].pb(pii(i, 1));
        //     else {
        //         factorization[i] = factorization[i / sieve[i]];
        //         for (int j = 0; j < size(factorization[i / sieve[i]]); j++) {
        //             if (factorization[i / sieve[i]][j].FF == sieve[i]) 
        //                 factorization[i / sieve[i]][j].SS++;
        //         }
        //     }
        // }
    }

    // should only call once
    void factor(vector<pll>& ans, ll n) {
        for (int p : primes) {
            if (n < p) break;
            if (n % p == 0) ans.pb(pll(p, 0));
            while (n % p == 0) {
                n /= p;
                ans.back().SS++;
            }
        }
        if (n > 1) ans.pb(pll(n, 1));
    }

    // should only call once
    void gen_div(vector<ll>& ans, ll n) {
        vector<pll> factors;
        factor(factors, n);
        ans.pb(1);
        for (pll p : factors) {
            int asz = size(ans);
            ll multy = 1;
            for (int j = 0; j < p.SS; j++) {
                multy *= p.FF;
                for (int i = 0; i < asz; i++) ans.pb(ans[i] * multy);
            }
        }
    }

    int modsqrt(int n) {
        n %= MOD;
        if (power(n, (MOD - 1) / 2) == MOD - 1) return -1;
        ll a = 2;
        for (; a < MOD; a++) {
            if (power((a * a - n) % MOD, (MOD - 1) / 2) == MOD - 1) break;
        }

        pll m = pll(a, 1);
        pll ans = pll(1, 0);

        int b = (MOD + 1) / 2;

        for (int i = 0; i < 32; i++) {
            if (b & 1) {
                ans = pll(add(mult(ans.FF, m.FF), mult(mult(ans.SS, m.SS), sub(mult(a, a), n))),
                        add(mult(ans.FF, m.SS), mult(ans.SS, m.FF)));
            }
            m = pll(add(mult(m.FF, m.FF), mult(mult(m.SS, m.SS), sub(mult(a, a), n))),
                    add(mult(m.FF, m.SS), mult(m.SS, m.FF)));
            b >>= 1;
        }

        return (ans.FF + MOD) % MOD;
    }
};

int N;
ll arr[MAXN];
ll tmp[MAXN];
NT nt(1000000);

void reset_tc() {

}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    ll sum = 0;
    for (int i = 1; i <= N; i++) sum += arr[i];

    vector<pll> factors;
    nt.factor(factors, sum);

    ll ans = LINF;
    for (pll n : factors) if (n.FF != 1) {
        for (int i = 1; i <= N; i++) tmp[i] = arr[i] % n.FF;
        // for (int i = 1; i <= N; i++) if (n == 3) cout << tmp[i] << " ";
        // cout << endl;

        ll tans = 0;
        for (int i = 1; i <= N; i++) if (tmp[i]) {
            int j = i;
            ll tsum = tmp[i];
            while (j < N && tsum < n.FF) {
                j++;
                tsum += tmp[j];
            }
            ll extra = tsum - n.FF;

            ll best_arr = 0;
            for (int k = i; k < j; k++) best_arr += tmp[k] * (k - i);
            best_arr += (tmp[j] - extra) * (j - i);
            
            ll cur_arr = best_arr;
            ll v = 0;
            for (int k = i + 1; k <= j; k++) {
                v += tmp[k - 1];
                cur_arr += v;
                cur_arr -= n.FF - v;

                best_arr = min(best_arr, cur_arr);
            }

            i = j - 1;
            tmp[j] = extra;
            tans += best_arr;
        }
        ans = min(ans, tans);
    }

    if (ans == LINF) cout << -1 << endl;
    else cout << ans << endl;

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