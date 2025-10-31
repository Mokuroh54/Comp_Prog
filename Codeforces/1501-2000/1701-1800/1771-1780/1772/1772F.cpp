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

const int MAXN = 110;
int N, M, K;
int grid[MAXN][40][40];
pii relaxo[MAXN];
vector<int> mutations[MAXN];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void reset_tc() {

}

void solve() {
    cin >> N >> M >> K;
    for (int k = 1; k <= K + 1; k++) {
        for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) {
            char c;
            cin >> c;
            grid[k][i][j] = c - '0';
        }

        for (int i = 2; i <= N - 1; i++) for (int j = 2; j <= M - 1; j++) {
            int hey = 1;
            for (int h = 0; h < 4; h++) if (grid[k][i + dx[h]][j + dy[h]] != grid[k][i][j]) hey = 0;
            relaxo[k].FF += hey;
        }
        relaxo[k].SS = k;
    }
    
    sort(relaxo + 1, relaxo + 1 + K + 1);
    cout << relaxo[1].SS << endl;
    int opc = 0;
    for (int k = 2; k <= K + 1; k++) {
        for (int i = 2; i <= N - 1; i++) for (int j = 2; j <= M - 1; j++) {
            if (grid[relaxo[k - 1].SS][i][j] != grid[relaxo[k].SS][i][j]) opc++;
        }
        opc++;
    }

    cout << opc << endl;

    for (int k = 2; k <= K + 1; k++) {
        for (int i = 2; i <= N - 1; i++) for (int j = 2; j <= M - 1; j++) {
            if (grid[relaxo[k - 1].SS][i][j] != grid[relaxo[k].SS][i][j]) cout << "1 " << i << " " << j << endl;
        }
        cout << "2 " << relaxo[k].SS << endl;
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