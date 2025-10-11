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
ll MOD = 1000000007;

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

const int MAXN = 1000010;
int N, M, K;
pii cells[MAXN];
pii c1[MAXN];
pii c2[MAXN];
int dx[8] = {2, 1, 0, -1, -2, -1, 0, 1};
int dy[8] = {0, 1, 2, 1, 0, -1, -2, -1};

void reset_tc() {
    for (int i = 1; i <= K + 1; i++) cells[i] = pii(0, 0);
    for (int i = 1; i <= K; i++) c1[i] = c2[i] = pii(0, 0);
}

void solve() {
    cin >> N >> M >> K;
    for (int i = 1; i <= K + 1; i++) cin >> cells[i].FF >> cells[i].SS;

    for (int i = 1; i <= K; i++) {
        if (abs(cells[i].FF - cells[i + 1].FF) + abs(cells[i].SS - cells[i + 1].SS) != 2) {
            cout << 0 << endl;
            reset_tc();
            return;
        }

        if (cells[i].FF != cells[i + 1].FF && cells[i].SS != cells[i + 1].SS) {
            c1[i] = pii(cells[i].FF, cells[i + 1].SS);
            c2[i] = pii(cells[i + 1].FF, cells[i].SS);
            // cout << c1[i].FF << " " << c1[i].SS << endl;
            // cout << c2[i].FF << " " << c2[i].SS << endl;
        }
        else {
            if (cells[i].FF == cells[i + 1].FF) 
                c1[i] = pii(cells[i].FF, (cells[i].SS + cells[i + 1].SS) / 2);
            else 
                c1[i] = pii((cells[i].FF + cells[i + 1].FF) / 2, cells[i].SS);
            // cout << c1[i].FF << " " << c1[i].SS << endl;
        }
    }

    pll vals = pll(1, 1);
    pll nvals = pll(0, 0);
    for (int i = 2; i <= K; i++) {
        // cout << c1[i].FF << " " << c1[i].SS << endl;
        for (int j = 0; j < 8; j++) {
            pii v = pii(c1[i].FF + dx[j], c1[i].SS + dy[j]);
            // cout << "scan for " << v.FF << " " << v.SS << endl;
            if (c1[i - 1] == v) addeq(nvals.FF, vals.FF);
            if (c2[i - 1] == v) addeq(nvals.FF, vals.SS);

            if (c2[i] != pii(0, 0)) {
                v = pii(c2[i].FF + dx[j], c2[i].SS + dy[j]);
                if (c1[i - 1] == v) addeq(nvals.SS, vals.FF);
                if (c2[i - 1] == v) addeq(nvals.SS, vals.SS);
            }
        }
        vals = nvals;
        cout << i << " " << vals.FF << " " << vals.SS << endl;
        nvals = pll(0, 0);
    }

    cout << add(vals.FF, vals.SS) << endl;
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