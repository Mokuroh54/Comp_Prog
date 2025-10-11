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
int N;
int arr[MAXN];
vector<int> occ[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        arr[i] = 0;
        occ[i].clear();
    }
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    map<int, int> coords;
    for (int i = 1; i <= N; i++) coords[arr[i]]++;
    int cnt = 0;
    for (pii n : coords) coords[n.FF] = ++cnt;
    for (int i = 1; i <= N; i++) arr[i] = coords[arr[i]];

    for (int i = 1; i <= N; i++) occ[arr[i]].pb(i);

    set<int> left, mid, right;
    int mid_min = INF;
    for (int i = N; i >= 1; i--) if (size(occ[i]) > 0) {
        if (mid.empty()) {
            if (size(occ[i]) >= 3) {
                cout << "YES" << endl;
                cout << occ[i][1] - 1 << " " << 1 << " " << N - occ[i][1] << endl;
                reset_tc();
                return;
            }

            for (int n : occ[i]) mid.insert(n);
            for (int j = *mid.begin(); j <= *mid.rbegin(); j++) {
                mid.insert(j);
                if (arr[j] < mid_min) mid_min = arr[j];
            }
        }
        else {
            // cout << i << " " << *mid.begin() << " " << *mid.rbegin() << endl;
            int leftside = 0, rightside = 0;
            for (int n : occ[i]) {
                if (n < *mid.begin()) leftside++;
                else if (n > *mid.rbegin()) rightside++;
            }
            // cout << leftside << " " << rightside << " " << mid_min << endl;

            if (mid_min > i) {
                if (leftside > 1 && rightside >= 1 && arr[*mid.begin() - 1] == i) {
                    cout << "YES" << endl;
                    cout << *mid.begin() - 2 << " " << *mid.rbegin() - *mid.begin() + 2 << " " << N - *mid.rbegin() << endl;
                    reset_tc();
                    return;
                }

                if (rightside > 1 && leftside >= 1 && arr[*mid.rbegin() + 1] == i) {
                    cout << "YES" << endl;
                    cout << *mid.begin() - 1 << " " << *mid.rbegin() - *mid.begin() + 2 << " " << N - *mid.rbegin() - 1 << endl;
                    reset_tc();
                    return;
                }
            }

            // cout << "you know i love you so" << endl;
            
            if (mid_min == i && leftside && rightside) {
                cout << "YES" << endl;
                cout << *mid.begin() - 1 << " " << *mid.rbegin() - *mid.begin() + 1 << " " << N - *mid.rbegin() << endl;
                reset_tc();
                return;
            }

            for (int n : occ[i]) {
                if (n < *mid.begin()) {
                    int bv = *mid.begin();
                    for (int j = n; j < bv; j++) {
                        mid.insert(j);
                        if (arr[j] < mid_min) mid_min = arr[j];
                    }
                }
                if (n > *mid.rbegin()) {
                    int ev = *mid.rbegin();
                    for (int j = ev + 1; j <= n; j++) {
                        mid.insert(j);
                        if (arr[j] < mid_min) mid_min = arr[j];
                    }
                }
            }
        }
    }

    cout << "NO" << endl;
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