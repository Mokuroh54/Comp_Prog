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

const int MAXN = 300010;
int N;
int h[MAXN], d[MAXN];
int ans[MAXN];
int l[MAXN], r[MAXN];
int alive[MAXN];

struct Duck {
    int h, d, i;
};

bool operator<(const Duck& d1, const Duck& d2) {
    return 1ll * d1.h * d2.d < 1ll * d1.d * d2.h;
}

void reset_tc() {
    for (int i = 1; i <= N; i++) h[i] = d[i] = ans[i] = l[i] = r[i] = alive[i] = 0;
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> d[i];
    for (int i = 1; i <= N; i++) cin >> h[i];

    multiset<Duck> ducks;
    for (int i = 1; i <= N; i++) l[i] = i - 1, r[i] = i + 1, alive[i] = 1;
    for (int i = 1; i <= N; i++) ducks.insert({h[i], d[l[i]] + d[r[i]], i});

    for (int t = 1; t <= N; t++) {
        set<int> dead_ducks;
        set<int> update_ducks;
        // cout << t << endl;
        while (size(ducks) && ducks.begin()->h < ducks.begin()->d) {
            int i = ducks.begin()->i;
            alive[i] = 0;
            dead_ducks.insert(i);
            update_ducks.insert(l[i]);
            update_ducks.insert(r[i]);
            ducks.erase(ducks.begin());
            ans[t]++;
            // cout << i << " is dead " << endl;
        }

        for (int n : update_ducks) if (alive[n]) {
            ducks.erase({h[n], d[l[n]] + d[r[n]], n});
            // h[n] -= (t + 1) * (d[l[n]] + d[r[n]]);
        }

        for (int n : dead_ducks) {
            l[r[n]] = l[n];
            r[l[n]] = r[n];
        }

        for (int n : update_ducks) if (alive[n]) {
            // h[n] += (t + 1) * (d[l[n]] + d[r[n]]);
            ducks.insert({h[n], d[l[n]] + d[r[n]], n});
        }
    }

    for (int i = 1; i <= N; i++) cout << ans[i] << " ";
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