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
int N, K;
int arr[MAXN];
deque<int> occ[MAXN];
set<pii> check;
int lptr[MAXN], rptr[MAXN];

void reset_tc() {
    check.clear();
    for (int i = 1; i <= N; i++) {
        arr[i] = 0;
        lptr[i] = rptr[i] = 0;
        occ[i].clear();
    }
}

int solve(int k) {
    for (int i = 1; i <= N; i++) {
        if (rptr[i] - lptr[i] + 1 >= k) {
            int fuck = INF;
            for (pii p : check) {
                if (p.SS > fuck) return 0;
                fuck = p.SS;
            }
            for (pii p : check) {
                while (k >= 2 && rptr[i] - lptr[i] + 1 >= 2 &&
                       occ[i][lptr[i]] < p.FF && p.SS < occ[i][rptr[i]]) {
                    k -= 2;
                    lptr[i]++;
                    rptr[i]--;
                }

                while (lptr[i] <= rptr[i] && occ[i][lptr[i]] < p.FF && 
                                             occ[i][rptr[i]] < p.SS)
                    lptr[i]++;
                while (lptr[i] <= rptr[i] && p.FF < occ[i][lptr[i]] && 
                                             p.SS < occ[i][rptr[i]])
                    rptr[i]--;
            }
            k -= min(k / 2, (rptr[i] - lptr[i] + 1) / 2) * 2;
            if ((k == 1) && (rptr[i] - lptr[i] + 1) & 1) k--;
            if (!k) return 1;
            else return 0;
        }
        else {
            if (((rptr[i] - lptr[i] + 1) & 1) && !(k & 1)) {
                // cout << "epping" << endl;
                // if (dev) {
                //     l = occ[i][lptr[i]] + 1;
                //     lptr[i]++;
                // }
                // else {
                //     r = occ[i][rptr[i]] - 1;
                //     rptr[i]--;
                // }
                return 0;
            }

            while (k >= 2 && rptr[i] - lptr[i] + 1 >= 2) {
                check.insert(pii(occ[i][lptr[i]], occ[i][rptr[i]]));
                k -= 2;
                lptr[i]++;
                rptr[i]--;
            }
            if ((k & 1) && lptr[i] == rptr[i]) {
                check.insert(pii(occ[i][lptr[i]], occ[i][rptr[i]]));
                k--;
            }
        }
    }
    return 0;
}

void solve() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
        occ[arr[i]].pb(i);
    }

    // int is_alr_palin = 1;
    // for (int i = 1; i <= N; i++) {
    //     if (arr[i] != arr[N - i + 1]) is_alr_palin = 0;
    // }
    // if (is_alr_palin) {
    //     cout << "YES" << endl;
    //     reset_tc();
    //     return;
    // }

    // K--;

    for (int i = 1; i <= N; i++) lptr[i] = 0, rptr[i] = size(occ[i]) - 1;
    int ok = solve(K);
    // cout << ok << endl;
    // cout << "try 2" << endl;
    check.clear();
    for (int i = 1; i <= N; i++) lptr[i] = 0, rptr[i] = size(occ[i]) - 1;
    if (ok || solve(K - 1)) cout << "YES" << endl;
    else cout << "NO" << endl;

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