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

struct DSU {
    vector<int> p, sz;
    vector<int> szo, sze;
    vector<int> omax, emax;

    DSU() {DSU(0);}
    DSU(int n) {
        p.resize(n + 1);
        sz.resize(n + 1);
        szo.resize(n + 1);
        sze.resize(n + 1);
        omax.resize(n + 1);
        emax.resize(n + 1);
        for (int i = 1; i <= n; i++) p[i] = i, sz[i] = 1;
    }

    int root(int a) {return p[a] = (a == p[a] ? a : root(p[a]));}
    int combine(int a, int b) {
        a = root(a), b = root(b);
        if (a == b) return 0;

        if (sz[a] < sz[b]) swap(a, b);
        
        szo[a] += szo[b];
        sze[a] += sze[b];
        omax[a] |= omax[b];
        emax[a] |= emax[b];

        p[b] = a;
        sz[a] += sz[b];
        return 1;
    }
};

int N;
pii arr[MAXN];
int active[MAXN];
int MV = 0;

int score(DSU& dsu, int a, int& has_max, int mood) {
    a = dsu.root(a);

    if (!dsu.omax[a] && !dsu.emax[a]) return max(dsu.szo[a], dsu.sze[a]);
    if (dsu.omax[a] && dsu.emax[a]) {
        has_max += mood;
        return max(dsu.szo[a], dsu.sze[a]);
    }
        
    if (dsu.omax[a] && dsu.szo[a] >= dsu.sze[a]) has_max += mood; 
    if (dsu.emax[a] && dsu.sze[a] >= dsu.szo[a]) has_max += mood;
    
    return max(dsu.szo[a], dsu.sze[a]);
}

void reset_tc() {
    for (int i = 1; i <= N; i++) arr[i].FF = arr[i].SS = active[i] = 0;
}

void solve() {
    cin >> N;
    DSU dsu(N);
    for (int i = 1; i <= N; i++) {
        cin >> arr[i].FF;
        arr[i].SS = i;
        if (i & 1) dsu.szo[i] = 1;
        else dsu.sze[i] = 1;
    }

    sort(arr + 1, arr + 1 + N);
    MV = arr[N].FF;
    for (int i = 1; i <= N ; i++) {
        if (arr[i].FF == arr[N].FF) {
            if (arr[i].SS & 1) dsu.omax[arr[i].SS] = 1;
            else dsu.emax[arr[i].SS] = 1;
        }
    }

    int ans = 0;
    int tans = MV;
    int has_max = 0;
    for (int i = N; i >= 1; i--) {
        active[arr[i].SS] = 1;

        tans -= arr[i + 1].FF;
        tans += arr[i].FF;

        tans += score(dsu, arr[i].SS, has_max, 1);

        if (arr[i].SS + 1 <= N && active[arr[i].SS + 1]) {
            tans -= score(dsu, arr[i].SS + 1, has_max, -1);
            tans -= score(dsu, arr[i].SS, has_max, -1);
            dsu.combine(arr[i].SS, arr[i].SS + 1);
            tans += score(dsu, arr[i].SS, has_max, 1);
        }
        if (1 <= arr[i].SS - 1 && active[arr[i].SS - 1]) {
            tans -= score(dsu, arr[i].SS - 1, has_max, -1);
            tans -= score(dsu, arr[i].SS, has_max, -1);
            dsu.combine(arr[i].SS, arr[i].SS - 1);
            tans += score(dsu, arr[i].SS, has_max, 1);
        }
        // cout << arr[i].SS << " " << pause << " " << sob << endl;
        maxeq(ans, tans + (has_max ? 0 : -1));
        // cout << tans << endl;
    }

    cout << ans << endl;

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