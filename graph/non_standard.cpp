#include <iostream> // std::ostream

enum value_class_type {
    finite_class,
    pos_inf_class,
    neg_inf_class
};

template <class T>
struct non_standard {
    value_class_type value_class;
    T value;

    non_standard(T value) : value_class(value_class_type::finite_class), value(value) { }

    non_standard(value_class_type value_class, T value) : value_class(value_class), value(value) { }

    inline bool is_finite() const {
        return value_class == value_class_type::finite_class;
    }

    inline bool is_pos_inf() const {
        return value_class == value_class_type::pos_inf_class;
    }

    inline bool is_neg_inf() const {
        return value_class == value_class_type::neg_inf_class;
    }

    static inline non_standard pos_inf() {
        return non_standard(value_class_type::pos_inf_class, 0);
    }

    static inline non_standard neg_inf() {
        return non_standard(value_class_type::neg_inf_class, 0);
    }

    friend std::ostream& operator<<(std::ostream &os, const non_standard &x) {
        if (x.is_finite()) {
            os << x.value;
        } else if (x.is_pos_inf()) {
            os << "INF";
        } else if (x.is_neg_inf()) {
            os << "-INF";
        }
        return os;
    }
};
