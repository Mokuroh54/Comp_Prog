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

template <typename T1, typename T2>
inline pair<T1, T2> operator+(const pair<T1, T2>& p1, const pair<T1, T2>& p2) {
    return pii(p1.FF + p2.FF, p1.SS + p2.SS);
}
template <typename T1, typename T2>
inline pair<T1, T2> operator-(const pair<T1, T2>& p1, const pair<T1, T2>& p2) {
    return pii(p1.FF - p2.FF, p1.SS - p2.SS);
}
template <typename T1, typename T2>
inline pair<T1, T2> operator+=(pair<T1, T2>& l, const pair<T1, T2>& r) {
    l.FF += r.FF;
    l.SS += r.SS;
    return l;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 1000010;

struct NT {
    vector<int> primes;
    vector<int> sieve;
    vector<int> num_divs;
    vector<int> cnt;
    vector<int> npf;
    vector<vector<int>> divisors;
    vector<vector<pii>> factorization;

    NT(int x) {
        sieve.resize(x + 1);
        num_divs.resize(x + 1);
        cnt.resize(x + 1);
        npf.resize(x + 1);

        sieve[1] = 1;
        for (int i = 2; i <= x; i++) {
            if (!sieve[i]) {
                primes.pb(i);
                sieve[i] = i;
                num_divs[i] = 2;
                cnt[i] = 2;
                npf[i] = 1;
            }
            for (int p : primes) {
                if (i * p > x || p > sieve[i]) break;
                sieve[i * p] = p;

                if (i % p == 0) {
                    cnt[i * p] = cnt[i];
                    num_divs[i * p] = num_divs[i] / cnt[i] * cnt[i * p];
                    npf[i * p] = npf[i];
                    break;
                }

                cnt[i * p] = 2;
                num_divs[i * p] = num_divs[i] * 2;
                npf[i * p] = npf[i] + 1;
            }
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
    void factor(vector<pii>& ans, ll n) {
        if (n < size(sieve)) {
            while (n > 1) {
                if (ans.empty() || ans.back().FF != sieve[n]) 
                    ans.pb(pii(sieve[n], 1));
                else ans.back().SS++;
                n /= sieve[n];
            }
        }
        else {
            for (int p : primes) {
                if (p * p > n) break;
                if (n % p == 0) ans.pb(pii(p, 0));
                while (n % p == 0) {
                    n /= p;
                    ans.back().SS++;
                }
            }
            if (n > 1) ans.pb(pii(n, 1));
        }
    }

    int num_div(ll n) {
        vector<pii> factors;
        factor(factors, n);

        int ans = 1;
        for (pii p : factors) ans *= p.SS;
        return ans;
    }

    void gen_div(vector<int>& ans, ll n) {
        vector<pii> factors;
        factor(factors, n);
        
        ans.pb(1);
        for (pii p : factors) {
            int asz = size(ans);
            int multy = 1;
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

int N, X, Y;
int arr[MAXN];
ll cnt[MAXN];
ll psum[MAXN];

void reset_tc() {

}

void solve() {
    cin >> N >> X >> Y;
    int V = 1000000;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    for (int i = 1; i <= N; i++) {
        cnt[arr[i]]++;
        psum[arr[i]] += arr[i];
    }
    for (int i = 1; i <= V; i++) {
        cnt[i] += cnt[i - 1];
        psum[i] += psum[i - 1];
    }

    ll gans = LINF;
    NT nt(V);
    for (int p : nt.primes) {
        ll tans = 0;
        for (int i = p; i <= V + p; i += p) {
            if (i > V) {
                int thres = i - min(p, (X + Y - 1) / Y);
                tans += (cnt[min(thres, V)] - cnt[i - p]) * X;
                tans += ((cnt[min(i, V)] - cnt[min(thres, V)]) * i - (psum[V] - psum[min(thres, V)])) * Y;
            }
            else {
                int thres = i - min(p, (X + Y - 1) / Y);
                tans += (cnt[thres] - cnt[i - p]) * X;
                tans += ((cnt[i] - cnt[thres]) * i - (psum[i] - psum[thres])) * Y;
            }
        }
        mineq(gans, tans);
    }
    cout << gans << endl;
    
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