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

// #define endl "\n"
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

const int MAXN = 0;
int N;

void reset_tc() {

}

int ask(int a, int v) {
    cout << "? " << a << " " << v << endl;
    int n;
    cin >> n;
    return n;
}

void solve() {
    cin >> N;

    int v = N;

    vector<int> cands;
    for (int i = 1; i < N; i++) cands.pb(i);

    int resembles = 0;
    vector<int> has[2];
    int taker = 0;
    for (int j = 0; (1 << j) <= N; j++) {
        // if (!size(cands)) break;
        for (int i : cands) has[ask(i, (1 << j))].pb(i);

        // cout << taker << " " << (N / (1 << j)) << endl;

        int expect = (v / (1 << j)) + taker;

        int expect_no = (expect + taker) / 2;
        int expect_yes = expect - taker;

        // cout << "looking at bit " << j << endl;
        // cout << expect_no << " " << expect_yes << endl;
        // cout << size(has[0]) << " " << size(has[1]) << endl;

        if (size(has[0]) < expect_no) cands = has[0];
        else if (size(has[1]) < expect_yes) {
            resembles |= (1 << j);
            v -= (1 << j);
            cands = has[1];
            taker = 1;
        }
        else assert(0);

        has[0].clear();
        has[1].clear();
    }
    cout << "! " << resembles << endl;
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