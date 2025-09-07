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

int N;
int arr[MAXN];
int w[MAXN];
vector<int> occ[MAXN];
ll ans[MAXN];

void reset_tc() {

}

void solve() {
    cin >> N;
    int maxv = 0;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
        maxeq(maxv, arr[i]);
    }
    for (int i = 1; i <= N; i++) w[i] = 1;
    for (int i = 1; i <= N; i++) occ[arr[i]].pb(i);
    set<int> idxs;
    for (int i = 1; i <= maxv; i++) {
        for (int g : occ[i]) {
            if (size(idxs)) {
                auto it = idxs.upper_bound(g);
                int l = -1, r = -1;
                if (it != idxs.end()) r = *it;
                if (it != idxs.begin()) l = *(--it);

                if (l == -1 && r == -1) int a = 4;
                else if (r == -1) w[l]--;
                else if (l == -1) w[r]--;
                else {
                    if (arr[r] > arr[l]) w[r]--;
                    else w[l]--;
                }
            }
            idxs.insert(g);
        } 
    }

    // for (int i = 1; i <= N; i++) cout << w[i] << " ";
    // cout << endl;
    
    for (int i = 1; i <= N; i++) {
        ans[arr[i]] += w[i];
        ans[maxv + 1] -= w[i];
        // cout << arr[i] << " " << maxv << " " << 1 << endl;
        int lv = arr[i];
        for (int j = 2; j * j <= arr[i]; j++) {
            lv = (arr[i] + j - 1) / j;
            ans[(arr[i] + j - 1) / j] += j * w[i];
            ans[(arr[i] - 1) / (j - 1) + 1] -= j * w[i];
            // cout << (arr[i] + j - 1) / j << " " << (arr[i] - 1) / (j - 1) << " " << j << endl;
        }
        for (int j = 1; j < lv; j++) {
            ans[j] += (arr[i] + j - 1) / j * w[i];
            ans[j + 1] -= (arr[i] + j - 1) / j * w[i];
            // cout << j << " " << (arr[i] + j - 1) / j << endl;
        }
        // cout << endl;
        // cout << endl;
    }

    ll accum = 0;
    for (int i = 1; i <= maxv; i++) {
        accum += ans[i];
        cout << accum << " ";
    }
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
    T = 1;
    // cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 