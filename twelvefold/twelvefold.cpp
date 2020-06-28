#include <bits/stdc++.h>

#ifdef DEBUG
#define PRINT(x)\
    cout<<"func "<<__func__<<": line "<<__LINE__<<": "<<#x<<" = "<<(x)<<endl;
#define PRINTA(a,first,last)\
    cout<<"func "<<__func__<<": line "<<__LINE__<<": "<<#a<<"["<<(first)<<", "<<(last)<<")"<<endl;\
    for (int _i=(first);_i<(last);++_i){cout<<#a<<"["<<_i<<"] = "<<(a)[_i]<<endl;}
#define PRINTP(p)\
    cout<<"func "<<__func__<<": line "<<__LINE__<<": "<<#p<<" = ("<<(p.first)<<", "<<(p.second)<<")"<<endl;
#define PRINTI(a,i)\
    cout<<"func "<<__func__<<": line "<<__LINE__<<": "<<#a<<"["<<#i<<"] = "<<#a<<"["<<(i)<<"] = "<<(a)[i]<<endl;
#else
#define PRINT(x)
#define PRINTA(a,first,last)
#define PRINTP(p)
#define PRINTI(a,i)
#endif

#define FOR(i,a,b) for (int i=(a);i<(b);++i)
#define RFOR(i,a,b) for (int i=(b)-1;i>=(a);--i)
#define REP(i,n) for (int i=0;i<(n);++i)
#define RREP(i,n) for (int i=(n)-1;i>=0;--i)
#define all(a) (a).begin(),(a).end()
#define rall(a) (a).rbegin(),(a).rend()
#define MOD 1000000007

using namespace std;

using ull = unsigned long long;

template <class T, T M>
class modulo {
public:
    T data;

    modulo(T data = 0) : data(data % M) {
    }

    modulo operator+(const modulo &x) const {
        return modulo(data + x.data);
    }

    modulo operator-(const modulo &x) const {
        return modulo(data + (M - x.data));
    }

    modulo operator*(const modulo &x) const {
        return modulo(data * x.data);
    }

    modulo operator/(const modulo &x) const {
        return modulo(data * x.inv().data);
    }

    modulo operator+=(const modulo &x) {
        return data = (data + x.data) % M;
    }

    modulo operator-=(const modulo &x) {
        return data = (data + (M - x.data)) % M;
    }

    modulo operator*=(const modulo &x) {
        return data = (data * x.data) % M;
    }

    modulo operator/=(const modulo &x) {
        return data = (data * x.inv().data) % M;
    }

    modulo inv() const {
        return _pow(M - 2);
    }

    template <class Integer>
    modulo operator^(Integer n) const {
        if (n >= 0) {
            return _pow(n);
        } else {
            return _pow(M - 1 - (-n) % (M - 1));
        }
    }

    friend std::ostream& operator<<(std::ostream &os, const modulo &x) {
        os << x.data;
        return os;
    }

private:
    template <class NonNegativeInteger>
    modulo _pow(NonNegativeInteger n) const {
        modulo result(1);
        modulo x(*this);
        while (n) {
            if (n & 1) {
                result *= x;
            }
            x *= x;
            n >>= 1;
        }
        return result;
    }
};

template <class T, T M>
struct combinatorics {

    using Mod = modulo<T, M>;

    T N;
    std::vector<Mod> factorial;
    std::vector<Mod> inv_factorial;

    combinatorics(T N) : N(N), factorial(N + 1), inv_factorial(N + 1) {
        factorial[0] = 1;
        for (T i = 1; i <= N; ++i) {
            factorial[i] = factorial[i - 1] * i;
        }
        inv_factorial[N] = factorial[N].inv();
        for (T i = N; i >= 1; --i) {
            inv_factorial[i - 1] = inv_factorial[i] * i;
        }
    }

    Mod P(T n, T k) {
        if (0 <= k && k <= n) {
            return factorial[n] * inv_factorial[k];
        } else {
            return 0;
        }
    }

    Mod C(T n, T k) {
        if (0 <= k && k <= n) {
            return factorial[n] * inv_factorial[k] * inv_factorial[n - k];
        } else if (n == -1 && k == 0) { // conventinal
            return 1;
        } else {
            return 0;
        }
    }

    Mod H(T n, T k) {
        if (n == 0 && k == 0) {
            return 1;
        } else {
            return C(n + k - 1, k);
        }
    }
};

enum map_condition {
    NONE,
    INJECTIVE,
    SURJECTIVE,
};

using Mod = modulo<ull, MOD>;

Mod twelvefold(ull n, ull m, map_condition condition, bool up_to_permutation_of_n, bool up_to_permutation_of_m) {
    if (!up_to_permutation_of_n && !up_to_permutation_of_m) {
        if (condition == NONE) {
            // O(log(n))
            return Mod(m) ^ n;
        } else if (condition == INJECTIVE) {
            // pre O(m)
            // O(1)
            combinatorics<ull, MOD> c(m);
            return c.P(m, m - n);
        } else if (condition == SURJECTIVE) {
        }
    } else if (up_to_permutation_of_n && !up_to_permutation_of_m) {
        if (condition == NONE) {
            // pre O(n + m)
            // O(1)
            // Note that if n == 0 and m == 0 then C(-1, 0) == 1.
            combinatorics<ull, MOD> c(n + m - 1);
            return c.C(n + m - 1, n); // H(m, n)
        } else if (condition == INJECTIVE) {
            // pre O(m)
            // O(1)
            combinatorics<ull, MOD> c(m);
            return c.C(m, n);
        } else if (condition == SURJECTIVE) {
            // pre O(n)
            // O(1)
            // Note that if n == 0 and m == 0 then C(-1, 0) == 1.
            combinatorics<ull, MOD> c(n - 1);
            return c.C(n - 1, n - m);
        }
    } else if (!up_to_permutation_of_n && up_to_permutation_of_m) {
        if (condition == NONE) {

        } else if (condition == INJECTIVE) {
            return n <= m;
        } else if (condition == SURJECTIVE) {
        }
    } else if (up_to_permutation_of_n && up_to_permutation_of_m) {
        if (condition == NONE) {
            // pre O(n * min(n, m))
            // O(1)
            vector<vector<Mod>> p(n + 1);
            p[0] = {1};
            for (ull i = 1; i <= n; ++i) {
                p[i].resize(i + 1);
                for (ull j = 1; j <= min(i, m); ++j) {
                    p[i][j] = p[i - j][min(j, i - j)] + p[i][j - 1];
                }
            }
            return p[n][min(m, n)];
        } else if (condition == INJECTIVE) {
            return n <= m;
        } else if (condition == SURJECTIVE) {
            // pre O((n - m) * min(n - m, m))
            // O(1)
            if (n >= m) {
                return twelvefold(n - m, m, NONE, true, true);
            } else {
                return 0;
            }
        }
    }
    assert(0);
}

int main() {

    cin.tie(0);
    ios::sync_with_stdio(false);

    ull n, m;
    cin >> n >> m;
    cout << twelvefold(n, m, SURJECTIVE, true, true) << endl;

    return 0;
}
