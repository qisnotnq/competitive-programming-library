#include <iostream> // std::ostream
#include <vector> // std::vector

template <class T, T M>
class modulo {
public:
    T data;

    modulo(T data = 0) {
        T r = data % M;
        if (r < 0) {
            r += M;
        }
        this->data = r;
    }

    modulo _modulo(const T data) const {
        return modulo { data };
    }

    modulo operator+(const modulo &x) const {
        T y = data + x.data;
        if (y >= M) {
            y -= M;
        }
        return _modulo(y);
    }

    modulo operator-(const modulo &x) const {
        T y;
        if (data >= x.data) {
            y = data - x.data;
        } else {
            y = data + M - x.data;
        }
        return _modulo(y);
    }

    modulo operator*(const modulo &x) const {
        return _modulo(data * x.data % M);
    }

    modulo operator/(const modulo &x) const {
        return _modulo(data * x.inv().data % M);
    }

    modulo operator+=(const modulo &x) {
        data += x.data;
        if (data >= M) {
            data -= M;
        }
        return *this;
    }

    modulo operator-=(const modulo &x) {
        if (data >= x.data) {
            data -= x.data;
        } else {
            data += M - x.data;
        }
        return *this;
    }

    modulo operator*=(const modulo &x) {
        data = (data * x.data) % M;
        return *this;
    }

    modulo operator/=(const modulo &x) {
        data = (data * x.inv().data) % M;
        return *this;
    }

    modulo operator-() {
        return _modulo(data ? M - data : 0);
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
            return factorial[n] * inv_factorial[n - k];
        } else {
            return 0;
        }
    }

    Mod C(T n, T k) {
        if (0 <= k && k <= n) {
            return factorial[n] * inv_factorial[k] * inv_factorial[n - k];
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
