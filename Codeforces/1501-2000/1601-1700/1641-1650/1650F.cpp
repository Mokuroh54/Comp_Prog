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
int N, M;
int arr[MAXN];
struct Task {
    int id, t, p;    
};
int fuckyou[MAXN];
vector<Task> ducks[MAXN];
vector<ll> dp[210];
vector<int> pv[210];

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        arr[i] = 0;
        fuckyou[i] = 0;
        ducks[i].clear();
    }
}

bool Comp(const Task& t1, const Task& t2) {
    return 1ll * t1.t * t2.p < 1ll * t2.t * t1.p;
}

void solve() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        fuckyou[i] = c;
        ducks[a].pb(Task({i, b, c}));
    }

    int ok = 1;
    ll hours = 0;
    vector<int> seq;
    for (int i = 1; i <= N; i++) {
        sort(ducks[i].begin(), ducks[i].end(), Comp);

        for (int j = 0; j <= 200; j++) {
            dp[j].resize(size(ducks[i]) + 1);
            pv[j].resize(size(ducks[i]) + 1);
            for (int k = 0; k <= size(ducks[i]); k++) dp[j][k] = LINF;
        }
        dp[0][0] = 0;
        
        for (int k = 0; k < size(ducks[i]); k++) {
            for (int j = 199; j >= 0; j--) {
                if (j >= ducks[i][k].p && 
                    dp[j][k + 1] > dp[j - ducks[i][k].p][k] + ducks[i][k].t) {
                    dp[j][k + 1] = dp[j - ducks[i][k].p][k] + ducks[i][k].t;
                    pv[j][k + 1] = ducks[i][k].id;
                }
                if (dp[j][k] < dp[j][k + 1]) {
                    dp[j][k + 1] = dp[j][k];
                    pv[j][k + 1] = 0;
                }
            }
        }
        ll yay = 200;
        for (int j = 100; j < 200; j++) {
            // cout << dp[j][size(ducks[i])] << endl;
            if (dp[j][size(ducks[i])] < dp[yay][size(ducks[i])]) yay = j;
        }
        // cout << yay << endl;

        if (yay == 200 || dp[yay][size(ducks[i])] + hours > arr[i]) ok = 0;
        hours += dp[yay][size(ducks[i])];

        for (int k = size(ducks[i]); k >= 1; k--) if (pv[yay][k]) {
            seq.pb(pv[yay][k]);
            yay -= fuckyou[pv[yay][k]];
        }

        for (int j = 0; j <= 200; j++) {
            dp[j].clear();
            pv[j].clear();
        }
    }

    if (ok) {
        cout << size(seq) << endl;
        for (int n : seq) cout << n << " ";
        cout << endl;
    }
    else cout << -1 << endl;

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