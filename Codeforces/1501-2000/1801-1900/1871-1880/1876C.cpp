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
vector<int> rnbs[MAXN];
int in[MAXN];
int c[MAXN];

void reset_tc() {

}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
        in[arr[i]]++;
        rnbs[arr[i]].pb(i);
    }

    int ok = 1;
    priority_queue<int> topsort;
    for (int i = 1; i <= N; i++) if (!in[i]) {
        c[i] = 1;
        topsort.push(i);
    }
    while (!topsort.empty()) {
        int n = topsort.top();
        topsort.pop();

        if (c[n] == 1) {
            if (c[arr[n]] == 1) ok = 0;
            c[arr[n]] = -1;
        }
        else {
            int brnb = 0;
            int hope = 0;
            for (int nb : rnbs[n]) {
                if (c[nb] == 1) brnb = 1;
                if (c[nb] == -1) hope = 1;
            }

            if (c[n] == -1) {
                if (!brnb && !hope) ok = 0;
            }
            else {
                if (!brnb) c[n] = 1;
                else c[n] = -1;
            }
        }

        in[arr[n]]--;
        if (!in[arr[n]]) topsort.push(arr[n]);
    }

    for (int i = 1; i <= N; i++) if (!c[i]) {
        vector<int> cyc;
        cyc.pb(i);

        int t = arr[i];
        while (t != i) {
            cyc.pb(t);
            t = arr[t];
        }

        int start = -1;
        for (int j = 0; j < size(cyc); j++) {
            int brnb = 0;
            for (int nb : rnbs[cyc[j]]) if (c[nb] == 1) brnb = 1;

            if (brnb) {
                c[cyc[j]] = -1;
                start = j + 1;
            }
        }

        if (start == -1) {
            if (size(cyc) & 1) ok = 0;
            start = 0;
        }

        for (int j = start; j < start + size(cyc); j++) if (!c[cyc[j % size(cyc)]]) {
            int brnb = 0;
            for (int nb : rnbs[cyc[j % size(cyc)]]) if (c[nb] == 1) brnb = 1;

            if (brnb) c[cyc[j % size(cyc)]] = -1;
            else c[cyc[j % size(cyc)]] = 1;
        }
    }

    vector<int> ops;
    for (int i = 1; i <= N; i++) if (c[i] == 1) ops.pb(arr[i]);

    if (!ok) cout << -1 << endl;
    else {
        cout << size(ops) << endl;
        for (int n : ops) cout << n << " ";
        cout << endl;
    }
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