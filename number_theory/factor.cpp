struct factor {
    unordered_map p_es;

    Factor(Integer n) {
    }

    friend std::ostream& operator<<(std::ostream &os, const factor &x) {
        os << x.data;
        return os;
    }
};

template <class Integer>
Factor least_common_multiple(const vector<Integer> &v) {
    Factor factor;
    for (ull n: v) {
        for (ull p: primes) {
            if (p * p > n) break;
            size_t e = 0;
            while (n % p == 0) {
                n /= p;
                e++;
            }
            if (e && factor[p] < e) {
                factor[p] = e;
            }
        }
        if (n > 1) {
            if (!factor.count(n)) {
                factor[n] = 1;
            }
        }
    }
    return factor;
}

Factor div(Factor &factor1, Factor &factor2) {
    Factor factor;
    for (auto p_e: factor1) {
        ull p;
        size_t e1;
        tie(p, e1) = p_e;
        if (factor2.count(p)) {
            size_t e2 = factor2[p];
            assert(e1 >= e2);
            size_t e = e1 - e2;
            if (e > 0)
                factor[p] = e;
        } else {
            factor[p] = e1;
        }
    }
    return factor;
}

/*
Factor factorize(int N) {
    Factor factor;
    for (int p: primes) {
        if (p * p > N) break;
        int e = 0;
        while (N % p == 0) {
            N /= p;
            ++e;
        }
        if (e) factor[p] = e;
    }
    if (N > 1) factor[N] = 1;
    return factor;
}

void print_factor(const Factor &factor) {
    for (auto &p_e: factor) {
        int p, e;
        tie(p, e) = p_e;
        cout << p << '^' << e << ' ';
    }
    cout << endl;
}
*/

template <class Mod>
Mod factor_to_mod(const Factor &factor) {
    Mod result = 1;
    for (auto &p_e: factor) {
        ull p;
        size_t e;
        tie(p, e) = p_e;
        result *= Mod(p) ^ e;
    }
    return result;
}
