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

const int MAXN = 510;
const int MAXK = 200010;
int N, M, K;
pii tower[MAXK];
pii c[MAXN][MAXN], sc[MAXN][MAXN];
int vis[MAXN][MAXN];

struct Info {
    int cx, cy, i;
};

void reset_tc() {

}

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

void solve() {
    cin >> N >> M >> K;
    for (int i = 1; i <= K; i++) cin >> tower[i].FF >> tower[i].SS;
    queue<Info> q;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) {
        c[i][j] = pii(INF, 0);
        sc[i][j] = pii(INF, 0);
    }
    for (int i = 1; i <= K; i++) {
        c[tower[i].FF][tower[i].SS] = pii(0, i);
        q.push({tower[i].FF, tower[i].SS, i});
    }

    while (!q.empty()) {
        int x = q.front().cx, y = q.front().cy, i = q.front().i;
        q.pop();

        int dist = abs(tower[i].FF - x) + abs(tower[i].SS - y);

        if (vis[x][y] < 2) {
            vis[x][y]++;
            for (int j = 0; j < 4; j++) {
                int nx = x + dx[j];
                int ny = y + dy[j];

                if (nx < 1 || N < nx || ny < 1 || M < ny) continue;

                if (c[nx][ny] > pii(dist + 1, i)) {
                    // if (nx == 3 && ny == 3) {
                    //     cout << x << " " << y << endl;
                    //     cout << c[nx][ny].FF << " " << c[nx][ny].SS << endl;
                    //     cout << dist << " " << i << endl;
                    //     cout << tower[i].FF << " " << x << " " << tower[i].SS << " " << y << endl;
                    //     cout << "eee" << endl;
                    // }
                    c[nx][ny] = pii(dist + 1, i);
                    q.push(Info(nx, ny, i));
                }
                else if (sc[nx][ny] > pii(dist + 1, i) && i != c[nx][ny].SS) {
                    sc[nx][ny] = pii(dist + 1, i);
                    q.push(Info(nx, ny, i));
                }
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) cout << c[i][j].SS << " ";
        cout << endl;
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) cout << sc[i][j].SS << " ";
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