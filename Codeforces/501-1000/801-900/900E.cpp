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

const int MAXN = 100010;
int N, M;
string s, t;
int happy[MAXN];
pii dp[MAXN];

pii test(int i1, int i2) {
    return pii(s[i1] != '?' && s[i1] != t[i2], s[i1] == '?');
}

void reset_tc() {
    cin >> N;
    cin >> s;
    cin >> M;
    t = "";
    for (int i = 0; i < M; i++) t += 'a' + (i & 1);

    for (int i = 0; i < N; i++) happy[i] = INF;

    int diff = 0;
    int ops = 0;
    for (int i = 0; i < M; i++) {
        pii v = test(i, i);
        diff += v.FF;
        ops += v.SS;
    }
    if (!diff) happy[M - 1] = ops;

    for (int i = M + 1; i < N; i += 2) {
        pii v = test(i - M - 1, 0); 
        diff -= v.FF;
        ops -= v.SS;

        if (M > 1) {
            v = test(i - M, 1); 
            diff -= v.FF;
            ops -= v.SS;

            v = test(i - 1, M - 2); 
            diff += v.FF;
            ops += v.SS;
        }

        v = test(i, M - 1); 
        diff += v.FF;
        ops += v.SS;

        if (!diff) happy[i] = ops;
    }

    if (N > M) {
        int diff = 0;
        int ops = 0;
        for (int i = 1; i <= M; i++) {
            pii v = test(i, i - 1);
            diff += v.FF;
            ops += v.SS;
        }
        if (!diff) happy[M] = ops;

        for (int i = M + 2; i < N; i += 2) {
            pii v = test(i - M - 1, 0); 
            diff -= v.FF;
            ops -= v.SS;

            if (M > 1) {
                v = test(i - M, 1); 
                diff -= v.FF;
                ops -= v.SS;

                v = test(i - 1, M - 2); 
                diff += v.FF;
                ops += v.SS;
            }

            v = test(i, M - 1); 
            diff += v.FF;
            ops += v.SS;
                    
            if (!diff) happy[i] = ops;
        }
    }

    // for (int i = 1; i <= N; i++) dp[i].SS = INF;
    // cout << endl;

    for (int i = M; i <= N; i++) {
        if (i >= M && happy[i - 1] < INF) {
            // if (M >= 2 && happy[i - 3] < INF) {
            //     maxeq(dp[i], pii(dp[i - 2].FF + 1, 
            //                      dp[i - 2].SS - s[i - 2] == '?' - s[i - 1] == '?'));
            // }
            // else {
                maxeq(dp[i], pii(dp[i - M].FF + 1, dp[i - M].SS - happy[i - 1]));
            // }
        }
        maxeq(dp[i], dp[i - 1]);

        // cout << i << " " << dp[i].FF << " " << dp[i].SS << endl;
    }

    cout << -dp[N].SS << endl;
}

void solve() {
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