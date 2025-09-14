ll w[(1 << 20)][20][2];
struct Poly {
    static void init_w() {
        ll g = 3;
        ll ginv = power(g, MOD - 2);

        for (int i = 0; i < 20; i++) {
            w[0][i][0] = 1;
            w[0][i][1] = 1;

            ll t = power(g, (MOD - 1) / (1 << (i + 1)));
            for (int j = 1; j < (1 << i); j++) w[j][i][0] = mult(w[j - 1][i][0], t);

            ll t2 = power(ginv, (MOD - 1) / (1 << (i + 1)));
            for (int j = 1; j < (1 << i); j++) w[j][i][1] = mult(w[j - 1][i][1], t2);
        }
    }

    static void dft(vector<ll> &a, int tot, bool inv) {
        int sz = (1 << tot);
        for (int i = 1, j = 0; i < sz; i++) {
            int bit = sz >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }

        if (!w[0][0][0]) init_w();

        for (int i = 0; i < tot; i++) {
            for (int j = 0; j < sz; j += (1 << (i + 1))) {
                for (int k = 0; k < (1 << i); k++) {
                    ll v = mult(w[k][i][inv], a[j + k + (1 << i)]);
                    a[j + k + (1 << i)] = sub(a[j + k], v);
                    a[j + k] = add(a[j + k], v);
                }
            }
        }

        if (inv) {
            ll szinv = power(sz, MOD - 2);
            for (int i = 0; i < sz; i++) multeq(a[i], szinv);
        }
    }

    static vector<ll> slowmult(vector<ll> &a, vector<ll> &b) {
        vector<ll> c(size(a) + size(b) - 1);

        for (int i = 0; i < size(a); i++) for (int j = 0; j < size(b); j++)
            addeq(c[i + j], mult(a[i], b[j]));

        return c;
    }

    static vector<ll> pmult(vector<ll>& a, vector<ll>& b) {
        if (1ll * size(a) * size(b) <= 1000000) return slowmult(a, b);
        int tot = 32 - __builtin_clz(size(a) + size(b) - 1);
        if (size(a) == 1 && size(b) == 1) tot = 0;

        a.resize(1 << tot);
        b.resize(1 << tot);

        dft(a, tot, 0);
        dft(b, tot, 0);

        vector<ll> c(1 << tot);

        for (int i = 0; i < 1 << tot; i++) c[i] = mult(a[i], b[i]);

        dft(c, tot, 1);
        c.resize(size(a) + size(b) - 1);
        return c;
    }

    static vector<ll> invert(vector<ll> &f) {
        vector<ll> g;
        g.pb(power(f[0], MOD - 2));

        for (int i = 2; i <= buffer(f); i <<= 1) {
            vector<ll> t3;
            for (int j = 0; j < min((int) f.size(), i); j++) t3.pb(f[j]);
            vector<ll> t2 = pmult(g, g);
            t2.resize(min((int) t2.size(), i));
            t2 = pmult(t2, t3);
            g.resize(i);

            for (int j = 0; j < i; j++) {
                g[j] += g[j];
                if (t2.size() > j) g[j] += MOD - t2[j];
                g[j] %= MOD ; 
            } 
        }

        return g;
    }

    static int modsqrt(int n) {
        n %= MOD;
        if (power(n, (MOD - 1) / 2) == MOD - 1) return -1;
        ll a = 2;
        for (; a < MOD; a++) {
            if (power(sub(mult(a, a), n), (MOD - 1) / 2) == MOD - 1) break;
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

    static vector<ll> sqrt(vector<ll> &f) {
        vector<ll> g;
        g.pb(modsqrt(f[0]));

        for (int i = 2; i <= buffer(f); i <<= 1) {
            vector<ll> t2;
            for (int j = 0; j < min((int) f.size(), i); j++) t2.pb(f[j]);
            g.resize(i);
            vector<ll> t1 = invert(g);
            t1 = pmult(t2, t1);

            for (int j = 0; j < i; j++) {
                g[j] = (g[j] + t1[j]) * (MOD + 1) / 2;
                g[j] %= MOD;
            }
        }

        return g;
    }

    static void integral(vector<ll> &f) {
        f.resize(f.size() + 1);

        for (int i = f.size() - 2; i >= 0; i--) {
            f[i + 1] = divide(f[i], i + 1);
            f[i] = 0;
        }
    }

    static void derivative(vector<ll> &f) {
        f[0] = 0;

        for (int i = 1; i < f.size(); i++) {
            f[i - 1] = f[i] * i;
            f[i - 1] %= MOD;
            f[i] = 0;
        }
    }

    static vector<ll> exp(vector<ll> &f) {
        vector<ll> g;
        g.pb(1);

        for (int i = 2; i <= buffer(f); i <<= 1) {
            vector<ll> tg = g;
            tg.resize(i);
            tg = ln(g);

            vector<ll> h(i / 2);
            h[0] = 1;

            for (int j = 0; j < i / 2; j++) {
                if (f.size() > j)
                    h[j] += f[j];

                if (tg.size() > j)
                    h[j] += MOD - tg[j];

                h [ j ]  %= MOD ; 
            }

            h.resize(i / 2);
            g.resize(i / 2);
            g = pmult(h, g);
            g.resize(i);
        }

        return g;
    }

    static vector<ll> ln(vector<ll> &f) {
        vector<ll> tmp = f;
        vector<ll> ans = invert(f);
        ans.resize(f.size());
        derivative(tmp);
        ans = pmult(tmp, ans);
        ans.resize(f.size());
        integral(ans);
        ans.resize(f.size());
        return ans;
    }

    static vector<ll> ppower(vector<ll> &f, int k) {
        vector<ll> ans = ln(f);

        for (int i = 0; i < f.size(); i++) {
            ans[i] *= k;
            ans[i] %= MOD;
        }

        ans = exp(ans);
        ans.resize(f.size());
        return ans;
    }

    static int buffer(vector<ll> &f) {
        return (1 << (32 - __builtin_clz(f.size() - 1)));
    }
};