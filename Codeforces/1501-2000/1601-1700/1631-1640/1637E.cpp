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

const int MAXN = 300010;
int N, M;
int arr[MAXN];
int decompress[MAXN];
int cnt[MAXN];
set<int> bad[MAXN];
map<int, int> coords;
vector<int> has_cnt[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        arr[i] = decompress[i] = cnt[i] = 0;
        bad[i].clear();
        has_cnt[i].clear();
    }
    coords.clear();
}

void solve() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    for (int i = 1; i <= N; i++) coords[arr[i]] = 1;
    int N2 = 0;
    for (pii n : coords) {
        coords[n.FF] = ++N2;
        decompress[N2] = n.FF;
    }

    for (int i = 1; i <= N; i++) arr[i] = coords[arr[i]];
    for (int i = 1; i <= N; i++) cnt[arr[i]]++;

    for (int i = 1; i <= M; i++) {
        int x, y;
        cin >> x >> y;
        x = coords[x], y = coords[y];
        bad[x].insert(y);
        bad[y].insert(x);
    }

    ll ans = 0;
    for (int i = 1; i <= N2; i++) has_cnt[cnt[i]].pb(i);

    vector<int> cnts;
    for (int i = 1; i <= N; i++) {
        sort(has_cnt[i].rbegin(), has_cnt[i].rend());
        if (size(has_cnt[i])) cnts.pb(i);
    }
    
    for (int i = size(cnts) - 1; i >= 0; i--) {
        for (int k = 0; k < size(has_cnt[cnts[i]]); k++) {
            for (int j = i; j >= 0; j--) {
                for (int h = 0; h < size(has_cnt[cnts[j]]); h++) {
                    if (i == j && k == h) continue;
                    // cout << "try " << decompress[has_cnt[cnts[i]][k]] << " " << decompress[has_cnt[cnts[j]][h]] << endl;
                    if (!bad[has_cnt[cnts[i]][k]].count(has_cnt[cnts[j]][h])) {
                        // cout << i << " " << j << " " << decompress[has_cnt[i][k]] << " " << decompress[has_cnt[j][h]] << endl;
                        // cout << cnts[i] << " " << cnts[j] << endl;
                        // cout << decompress[has_cnt[cnts[i]][k]] << " " << decompress[has_cnt[cnts[j]][h]] << endl;
                        ans = max(ans, 1ll * (cnts[i] + cnts[j]) 
                                           * (decompress[has_cnt[cnts[i]][k]] + 
                                              decompress[has_cnt[cnts[j]][h]]));
                        break;
                    }
                }
            }
        }
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