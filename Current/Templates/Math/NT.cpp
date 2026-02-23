struct NT {
    vector<int> primes;
    vector<int> sieve;
    vector<int> num_divs;
    vector<int> cnt;
    vector<int> npf;
    vector<vector<int>> divisors;
    vector<vector<pii>> factorization;

    NT(int x) {
        sieve.resize(x + 1);
        num_divs.resize(x + 1);
        cnt.resize(x + 1);
        npf.resize(x + 1);

        sieve[1] = 1;
        for (int i = 2; i <= x; i++) {
            if (!sieve[i]) {
                primes.pb(i);
                sieve[i] = i;
                num_divs[i] = 2;
                cnt[i] = 2;
                npf[i] = 1;
            }
            for (int p : primes) {
                if (i * p > x || p > sieve[i]) break;
                sieve[i * p] = p;

                if (i % p == 0) {
                    cnt[i * p] = cnt[i];
                    num_divs[i * p] = num_divs[i] / cnt[i] * cnt[i * p];
                    npf[i * p] = npf[i];
                    break;
                }

                cnt[i * p] = 2;
                num_divs[i * p] = num_divs[i] * 2;
                npf[i * p] = npf[i] + 1;
            }
        }

        // for (int i = 2; i <= x; i++) {
        //     if (!sieve[i]) {
        //         divisors[i].pb(1);
        //         divisors[i].pb(i);
        //     }
        //     else {
        //         divisors[i] = divisors[i / sieve[i]];
        //         for (int n : divisors[i / sieve[i]]) if ((i / sieve[i] / n) % sieve[i]) {
        //             divisors[i].pb(n * sieve[i]);
        //         }
        //     }
        // }

        // for (int i = 2; i <= x; i++) {
        //     if (!sieve[i]) factorization[i].pb(pii(i, 1));
        //     else {
        //         factorization[i] = factorization[i / sieve[i]];
        //         for (int j = 0; j < size(factorization[i / sieve[i]]); j++) {
        //             if (factorization[i / sieve[i]][j].FF == sieve[i]) 
        //                 factorization[i / sieve[i]][j].SS++;
        //         }
        //     }
        // }
    }

    // should only call once
    void factor(vector<pii>& ans, ll n) {
        if (n < size(sieve)) {
            while (n > 1) {
                if (ans.empty() || ans.back().FF != sieve[n]) 
                    ans.pb(pii(sieve[n], 1));
                else ans.back().SS++;
                n /= sieve[n];
            }
        }
        else {
            for (int p : primes) {
                if (p * p > n) break;
                if (n % p == 0) ans.pb(pii(p, 0));
                while (n % p == 0) {
                    n /= p;
                    ans.back().SS++;
                }
            }
            if (n > 1) ans.pb(pii(n, 1));
        }
    }

    int num_div(ll n) {
        vector<pii> factors;
        factor(factors, n);

        int ans = 1;
        for (pii p : factors) ans *= p.SS;
        return ans;
    }

    void gen_div(vector<int>& ans, ll n) {
        vector<pii> factors;
        factor(factors, n);
        
        ans.pb(1);
        for (pii p : factors) {
            int asz = size(ans);
            int multy = 1;
            for (int j = 0; j < p.SS; j++) {
                multy *= p.FF;
                for (int i = 0; i < asz; i++) ans.pb(ans[i] * multy);
            }
        }
    }

    int modsqrt(int n) {
        n %= MOD;
        if (power(n, (MOD - 1) / 2) == MOD - 1) return -1;
        ll a = 2;
        for (; a < MOD; a++) {
            if (power((a * a - n) % MOD, (MOD - 1) / 2) == MOD - 1) break;
        }

        pll m = pll(a, 1);
        pll ans = pll(1, 0);

        int b = (MOD + 1) / 2;

        for (int i = 0; i < 32; i++) {
            if (b & 1) {
                ans = pll(add(mult(ans.FF, m.FF), mult(mult(ans.SS, m.SS), sub(mult(a, a), n))),
                        add(mult(ans.FF, m.SS), mult(ans.SS, m.FF)));
            }
            m = pll(add(mult(m.FF, m.FF), mult(mult(m.SS, m.SS), sub(mult(a, a), n))),
                    add(mult(m.FF, m.SS), mult(m.SS, m.FF)));
            b >>= 1;
        }

        return (ans.FF + MOD) % MOD;
    }
};