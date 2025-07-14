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

struct BIT {
    vector<ll> arr;

    BIT() {arr.resize(0);}
    BIT(int n) {arr.resize(n + 1);}

    void update(int a, ll v) {
        while (a < size(arr)) {
            arr[a] += v;
            a += (a & -a);
        }
    }

    ll query(int a) {
        ll ans = 0;
        while (a) {
            ans += arr[a];
            a -= (a & -a);
        }
        return ans;
    }

    ll query(int a, int b) {return query(b) - query(a - 1);}

    void clear() {
        arr.resize(0);
    }
};

int N;
int arr[MAXN];
deque<pii> boys[2];
BIT b[2];

void reset_tc() {
    for (int i = 1; i <= N; i++) arr[i] = 0;
    b[0].clear();
    b[1].clear();
}

void solve() {
    cin >> N;
    b[0] = BIT(N >> 1);
    b[1] = BIT((N + 1) >> 1);
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
        boys[i & 1].pb(pii(arr[i], i));
        b[i & 1].update((i + 1) >> 1, 1);
    }

    sort(boys[0].begin(), boys[0].end());
    sort(boys[1].begin(), boys[1].end());

    int swaps[2] = {0, 0};
    for (int i = 1; i <= N - 4; i++) {
        cout << boys[i & 1][0].FF << " ";
        int bidx = (boys[i & 1][0].SS + 1) >> 1;
        int delta = b[i & 1].query(1, bidx);
        // cout << bidx << " " << delta << endl;
        b[i & 1].update(bidx, -1);
        swaps[1 - (i & 1)] += 1 - (delta & 1);
        boys[i & 1].ppf();
    }
    // cout << swaps[0] << " " << swaps[1] << endl;

    if (boys[0][0].SS > boys[0][1].SS) swap(boys[0][0], boys[0][1]);
    if (boys[1][0].SS > boys[1][1].SS) swap(boys[1][0], boys[1][1]);

    if (swaps[0] & 1) swap(boys[0][0], boys[0][1]);
    if (swaps[1] & 1) swap(boys[1][0], boys[1][1]);

    if (boys[1 - (N & 1)][0].FF > boys[1 - (N & 1)][1].FF) {
        swap(boys[0][0], boys[0][1]);
        swap(boys[1][0], boys[1][1]);
    }

    for (int i = N - 3; i <= N; i++) {
        cout << boys[i & 1][0].FF << " ";
        boys[i & 1].ppf();
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
    // T = 1;
    cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 