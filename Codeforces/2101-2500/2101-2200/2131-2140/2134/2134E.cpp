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

// #define endl "\n"
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

const int MAXN = 1010;
int N;
int arr[MAXN];
int hops[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) arr[i] = hops[i] = 0;
}

pii query(int a, int b, int c) {
    pii ans;
    cout << "throw " << a << endl;
    cin >> ans.FF;
    cout << "swap " << b << endl;
    cout << "throw " << c << endl;
    cout.flush();
    cin >> ans.SS;
    return ans;
}

void solve() {
    cin >> N;
    for (int i = N; i >= 2; i -= 2) {
        if (hops[i + 1] == hops[i + 2]) {
            pii ans = query(i - 1, i - 1, i - 1);

            if (ans.FF == hops[i + 1] + 1) arr[i - 1] = 2;
            else arr[i - 1] = 1;
            if (ans.SS == hops[i + 1] + 1) arr[i] = 2;
            else arr[i] = 1;

            hops[i] = hops[i + arr[i - 1]] + 1;
            hops[i - 1] = hops[i - 1 + arr[i]] + 1;
            // cout << arr[i - 1] << " " << arr[i] << endl;
        }
        else {
            pii ans = query(i, i - 1, i);

            if (ans.FF == hops[i + 1] + 1) arr[i] = 1;
            else arr[i] = 2;
            if (ans.SS == hops[i + 1] + 1) arr[i - 1] = 1;
            else arr[i - 1] = 2;

            hops[i] = hops[i + arr[i - 1]] + 1;
            hops[i - 1] = hops[i - 1 + arr[i]] + 1;
            // cout << arr[i - 1] << " " << arr[i] << endl;
        }
    }
    if (N & 1) {
        if (hops[3] == hops[4]) {
            cout << "throw " << 1 << endl;
            int ans;
            cin >> ans;
            if (ans == hops[3] + 1) arr[1] = 2;
            else arr[1] = 1;
        }
        else {
            cout << "swap " << 1 << endl;
            cout << "throw " << 2 << endl;
            cout.flush();
            int ans;
            cin >> ans;
            if (ans == hops[3] + 1) arr[1] = 1;
            else arr[1] = 2;
        }
    }

    // for (int i = 1; i <= N; i++) cout << hops[i] << " ";
    // cout << endl;

    cout << "! ";
    for (int i = 1; i <= N; i++) cout << arr[i] << " ";
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