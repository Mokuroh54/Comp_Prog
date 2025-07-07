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

#define add(a, b) ((a + b) >= MOD ? a + b - MOD : a + b)
#define sub(a, b) ((a - b) >= 0 ? a - b : a + MOD - b)
#define mult(a, b) ((a * b) % MOD)
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
#define divide(a, b) ((a * power(b, MOD - 2)) % MOD)

#define maxeq(x, y) x = x > y ? x : y
#define mineq(x, y) x = x < y ? x : y
#define addeq(x, y) x = add(x, y)
#define subeq(x, y) x = sub(x, y)
#define multeq(x, y) x = mult(x, y)
#define diveq(x, y) x = divide(x, y)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 1010;
int N, M;
int griddy[MAXN][MAXN];
int vis[MAXN][MAXN];

int cx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int cy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int gx[3] = {0, 1, 1};
int gy[3] = {1, 0, 1};

void reset_tc() {

}

void solve() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) cin >> griddy[i][j];

    queue<pii> search;
    for (int i = 1; i < N; i++) for (int j = 1; j < M; j++) {
        int good = 1;
        for (int k = 0; k < 3; k++) if (griddy[i][j] != griddy[i + gx[k]][j + gy[k]]) good = 0;
        if (good) search.push(pii(i, j));
    }
    
    vector<pii> ops;
    vector<int> col;
    while (!search.empty()) {
        int x = search.front().FF;
        int y = search.front().SS;
        search.pop();

        if (vis[x][y] == 2) continue;
        // cout << x << " " << y << endl;
        int color = 0;
        if (!vis[x][y]) color = griddy[x][y];
        for (int k = 0; k < 3; k++) {
            int nx = x + gx[k];
            int ny = y + gy[k];

            if (!vis[nx][ny]) color = griddy[nx][ny];
            maxeq(vis[nx][ny], 1);
        }
        vis[x][y] = 2;
        if (!color) continue;

        ops.pb(pii(x, y));
        col.pb(color);

        for (int k = 0; k < 8; k++) {
            int nx = x + cx[k];
            int ny = y + cy[k];

            if (nx < 1 || ny < 1 || nx >= N || ny >= M) continue;

            int good = 1;
            int color = 0;
            if (!vis[nx][ny]) color = griddy[nx][ny];
            for (int h = 0; h < 3; h++) if (!vis[nx + gx[h]][ny + gy[h]]) {
                if (color && color != griddy[nx + gx[h]][ny + gy[h]]) good = 0;
                color = griddy[nx + gx[h]][ny + gy[h]];
            }
            if (good && color) {
                // cout << "go to " << nx << " " << ny << endl;
                search.push(pii(nx, ny));
            }
        }
    }

    int yay = 1;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) if (!vis[i][j]) yay = 0;

    if (!yay) {
        cout << -1 << endl;
        return;
    }

    reverse(ops.begin(), ops.end());
    reverse(col.begin(), col.end());

    cout << size(ops) << endl;
    for (int i = 0; i < size(ops); i++) {
        cout << ops[i].FF << " " << ops[i].SS << " " << col[i] << endl;
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