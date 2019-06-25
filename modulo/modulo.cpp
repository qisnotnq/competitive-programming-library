#include <iostream> // std::ostream

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
        data = (data + x.data) % M;
    }

    modulo operator-=(const modulo &x) {
        data = (data + (M - x.data)) % M;
    }

    modulo operator*=(const modulo &x) {
        data = (data * x.data) % M;
    }

    modulo operator/=(const modulo &x) {
        data = (data * x.inv().data) % M;
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
    template<class NonNegativeInteger>
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
