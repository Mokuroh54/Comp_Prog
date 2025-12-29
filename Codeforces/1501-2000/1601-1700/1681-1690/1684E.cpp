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
int N, K;
int arr[MAXN];
map<int, int> freq;
set<pii> largers;
set<pii> support;

void reset_tc() {
    for (int i = 1; i <= N; i++) arr[i] = 0;
    freq.clear();
    largers.clear();
    support.clear();
}

void solve() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= N; i++) freq[arr[i]]++;

    int max_mex = 0;
    int have = N;
    int ops_needed = 0;
    for (int i = 0; i < N; i++) {
        if (!freq.count(i)) ops_needed++;
        else have--;
        if (ops_needed <= min(have, K)) max_mex = i + 1;
    }

    for (pii p : freq) {
        if (p.FF >= max_mex) largers.insert(pii(p.SS, p.FF));
        else support.insert(pii(p.SS, p.FF));
    }

    int ans = size(freq);
    for (int i = 0; i < max_mex; i++) {
        if (!freq[i]) {
            set<pii>* guy;
            if (size(largers)) guy = &largers;
            else guy = &support;

            int ns = guy->begin()->SS;
            guy->erase(guy->begin());
            freq[ns]--;
            if (freq[ns]) guy->insert(pii(freq[ns], ns));
        }

        // cout << "mex is: " << i << endl;
        // for (pii p : largers) cout << p.FF << " " << p.SS << endl;
        // cout << endl;

        mineq(ans, size(largers));
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