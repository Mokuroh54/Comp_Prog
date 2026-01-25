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
ll MOD = 998244353;

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

const int MAXN = 1 << 20;
int N;
int arr[MAXN];
int lc[MAXN], rc[MAXN];

void reset_tc() {

}

int Comp(int a, int b) {
    if (arr[a] < arr[b]) return -1;
    else if (arr[a] > arr[b]) return 1;
    else if (lc[a] && rc[a] && lc[b] && rc[b]) {
        int la = Comp(lc[a], lc[b]);
        int ra = Comp(rc[a], rc[b]);
        if (la == ra) return la;
        else if (la < ra) return -1;
        else return 1;
    }
    else return 0;
}

ll DFS(int a) {
    if (a << 1 >= (1 << N)) return 1;
    
    ll ans1 = DFS(lc[a]);
    ll ans2 = DFS(rc[a]);
    
    int c = Comp(lc[a], rc[a]);
    // cout << "see " << c << endl;
    // cout << arr[lc[a]] << " " << arr[rc[a]] << endl;
    // cout << a << " " << ans1 << " " << ans2 << " " << c << endl;
    if (!c) return mult(ans1, ans2);
    else {
        if (c == 1) swap(lc[a], rc[a]);
        return mult(2, mult(ans1, ans2));
    }
}

void solve() {
    cin >> N;
    for (int i = 1; i <= (1 << N) - 1; i++) {
        char c;
        cin >> c;
        arr[i] = c - 'A';
    }

    for (int i = 1; i <= (1 << N) - 1; i++) {
        if ((i << 1) <= (1 << N)) {
            lc[i] = i << 1;
            rc[i] = (i << 1) + 1;
        }
    }

    cout << DFS(1) << endl;
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