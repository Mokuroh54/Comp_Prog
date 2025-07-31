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

const int MAXN = 100010;
int N, Q;
ll sz[MAXN];
int a[MAXN];
int ans[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) sz[i] = a[i] = 0;
    for (int i = 1; i <= Q; i++) ans[i] = 0;
}

void solve() {
    cin >> N >> Q;
    int idx = N;
    for (int i = 1; i <= N; i++) {
        int t, n;
        cin >> t >> n;
        if (t == 1) {
            a[i] = n;
            if (sz[i - 1] == LINF) sz[i] = LINF;
            else sz[i] = sz[i - 1] + 1;
        }
        else {
            if (LINF / (n + 1) >= sz[i - 1] && sz[i - 1] * (n + 1) <= LINF) 
                sz[i] = sz[i - 1] * (n + 1);
            else sz[i] = LINF;
        }
        if (sz[i] == LINF) mineq(idx, i);
        // cout << sz[i] << " ";
    }
    cout << endl;

    priority_queue<pll> queries;
    for (int i = 1; i <= Q; i++) {
        ll x;
        cin >> x;
        queries.push(pll(x, i));
    }

    while (!queries.empty()) {
        ll x = queries.top().FF;
        ll qid = queries.top().SS;
        queries.pop();

        while (x <= sz[idx - 1]) idx--;

        if (a[idx]) {
            assert(x == sz[idx]);
            ans[qid] = a[idx];
        }
        else queries.push(pll((x - 1) % sz[idx - 1] + 1, qid));
    }

    for (int i = 1; i <= Q; i++) cout << ans[i] << " ";
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
    // T = 1;
    cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 