#include "biginteger.h"

BigInteger::BigInteger() {
    convert(std::to_string(0));
}

BigInteger::BigInteger(int value) {
    convert(std::to_string(value));
}

BigInteger::BigInteger(const BigInteger& other) = default;
BigInteger::~BigInteger() = default;

BigInteger& BigInteger::operator =(int value) {
    convert(std::to_string(value));
    return (*this);
}

BigInteger& BigInteger::operator +=(const BigInteger& other) {
    if (!(sign || other.sign))
        return ((*this) = addition((*this), other));
    if (sign && other.sign)
        return ((*this) = -addition(-(*this), -other));
    if (!sign) {
        if (-(*this) <= other)
            return ((*this) = subtraction((*this), -other));
        else
            return ((*this) = -subtraction(-other, (*this)));
    } else {
        if (-(*this) >= other)
            return ((*this) = -subtraction(-(*this), other));
        else
            return ((*this) = subtraction(other, -(*this)));
    }
}

BigInteger& BigInteger::operator -=(const BigInteger& other) {
    (*this) += (-other);
    return (*this);
}

BigInteger& BigInteger::operator *=(const BigInteger& other) {
    BigInteger _other = other;
    bool _sign = sign ^ _other.sign;
    sign = false;
    _other.sign = false;
    (*this) = multiplication((*this), _other);
    sign = _sign && (toString() != "0");
    return (*this);
}

BigInteger& BigInteger::operator /=(const BigInteger& other) {
    BigInteger _other = other;
    bool _sign = sign ^ _other.sign;
    sign = false;
    _other.sign = false;
    (*this) = division((*this), _other);
    sign = _sign && (toString() != "0");
    return (*this);
}

BigInteger& BigInteger::operator %=(const BigInteger& other) {
    BigInteger _other = other;
    bool _sign = sign ^ _other.sign;
    sign = false;
    _other.sign = false;
    (*this) -= multiplication(division((*this), _other), _other);
    sign = _sign && (toString() != "0");
    return (*this);
}

BigInteger BigInteger::operator +(const BigInteger& other) {
    BigInteger copy = (*this);
    copy += other;
    return copy;
}

BigInteger BigInteger::operator -(const BigInteger& other) {
    BigInteger copy = (*this);
    copy -= other;
    return copy;
}

BigInteger BigInteger::operator *(const BigInteger& other) {
    BigInteger copy = (*this);
    copy *= other;
    return copy;
}

BigInteger BigInteger::operator /(const BigInteger& other) {
    BigInteger copy = (*this);
    copy /= other;
    return copy;
}

BigInteger BigInteger::operator %(const BigInteger& other) {
    BigInteger copy = (*this);
    copy %= other;
    return copy;
}

BigInteger BigInteger::operator -() const {
    BigInteger copy(*this);
    copy.sign ^= true;
    return copy;
}

BigInteger& BigInteger::operator ++() {
    if (sign) {
        sign ^= true;
        --(*this);
        sign ^= true;
    } else {
        int digit = digits.size() - 1;
        while (digit > 0 && digits[digit] == '9')
            digits[digit--] = '0';
        if (digit == -1) {
            reverse_vector(digits);
            digits.push_back('0');
            reverse_vector(digits);
            digit++;
        }
        digits[digit]++;
    }
    return (*this);
}

BigInteger& BigInteger::operator --() {
    if (sign || (digits.size() == 1 && digits[0] == '0')) {
        sign ^= true;
        ++(*this);
        sign ^= true;
    } else {
        if (digits.size() == 1 && digits[0] == '0')
            return (*this = -1);
        int digit = digits.size() - 1;
        while (digit > 0 && digits[digit] == '0')
            digits[digit--] = '9';
        digits[digit]--;
    }
    return (*this);
}

BigInteger BigInteger::operator ++(int) {
    BigInteger copy = (*this);
    ++(*this);
    return copy;
}

BigInteger BigInteger::operator --(int) {
    BigInteger copy = (*this);
    --(*this);
    return copy;
}

bool BigInteger::operator <(const BigInteger& other) const {
    if (sign == other.sign) {
        if (!sign) {
            if (digits.size() != other.digits.size())
                return digits.size() < other.digits.size();
            return digits < other.digits;
        } else {
            if (digits.size() != other.digits.size())
                return digits.size() > other.digits.size();
            return digits > other.digits;
        }
    }
    return sign;
}

bool BigInteger::operator >(const BigInteger& other) const {
    return (!((*this) < other) && !((*this) == other));
}

bool BigInteger::operator <=(const BigInteger& other) const {
    return (((*this) < other) || ((*this) == other));
}

bool BigInteger::operator >=(const BigInteger& other) const {
    return (((*this) > other) || ((*this) == other));
}

bool BigInteger::operator ==(const BigInteger& other) const {
    return (!((*this) < other) && !(other < (*this)));
}

bool BigInteger::operator !=(const BigInteger& other) const {
    return (!((*this) == other));
}

std::string BigInteger::toString() {
    std::string result = (sign) ? "-" : "";
    for (const auto& digit : digits)
        result.push_back(digit);
    return result;
}

BigInteger::operator bool() const {
    BigInteger copy = *this;
    return (copy.toString() != "0");
}

std::istream& operator >>(std::istream& stream, BigInteger& object) {
    std::string number;
    stream >> number;
    object.convert(number);
    return stream;
}

std::ostream& operator <<(std::ostream& stream, const BigInteger& object) {
    BigInteger copy = object;
    return (stream << copy.toString());
}

void BigInteger::remove_zeroes(BigInteger& temp) {
    if (temp.digits[0] != '0')
        return;
    reverse_vector(temp.digits);
    while (temp.digits.size() > 1 && temp.digits.back() == '0')
        temp.digits.pop_back();
    reverse_vector(temp.digits);
}

void BigInteger::mult_power(BigInteger& temp, int step) {
    while (step--)
        temp.digits.push_back('0');
}

template <typename T> void BigInteger::reverse_vector(std::vector <T>& vect) {
    for (size_t i = 0; i < vect.size() / 2; ++i)
        std::swap(vect[i], vect[vect.size() - i - 1]);
}

void BigInteger::convert(std::string number) {
    digits.clear();
    sign = (number[0] == '-');
    for (size_t digit = static_cast<size_t>(sign); digit < number.size(); ++digit)
        digits.push_back(number[digit]);
}

BigInteger BigInteger::addition(BigInteger A, BigInteger B) {
    remove_zeroes(A);
    remove_zeroes(B);
    if (A.digits.size() < B.digits.size())
        std::swap(A, B);
    reverse_vector(A.digits);
    reverse_vector(B.digits);
    mult_power(A, 1);
    mult_power(B, A.digits.size() - B.digits.size());
    BigInteger C = 0;
    C.digits.resize(A.digits.size(), '0');
    int p = 0;
    for (size_t i = 0; i < C.digits.size(); ++i) {
        int tmp = p + A.digits[i] - '0' + B.digits[i] - '0';
        C.digits[i] = (tmp % 10) + '0';
        p = tmp / 10;
    }
    reverse_vector(C.digits);
    remove_zeroes(C);
    return C;
}

BigInteger BigInteger::subtraction(BigInteger A, BigInteger B) {
    remove_zeroes(A);
    remove_zeroes(B);
    reverse_vector(A.digits);
    reverse_vector(B.digits);
    mult_power(B, A.digits.size() - B.digits.size());
    BigInteger C = 0;
    C.digits.resize(A.digits.size(), '0');
    for (size_t i = 0; i < C.digits.size(); ++i) {
        if (A.digits[i] >= B.digits[i]) {
            C.digits[i] = A.digits[i] - B.digits[i] + '0';
            continue;
        }
        size_t it = i + 1;
        while (it < C.digits.size() && A.digits[it] == '0')
            ++it;
        A.digits[i] += 10;
        A.digits[it--] -= 1;
        while (it != i)
            A.digits[it--] = '9';
        C.digits[i] = A.digits[i] - B.digits[i] + '0';
    }
    reverse_vector(C.digits);
    remove_zeroes(C);
    return C;
}

BigInteger BigInteger::multiplication(BigInteger A, BigInteger B) {
    if (A.digits.size() != B.digits.size()) {
        if (A.digits.size() < B.digits.size())
            std::swap(A, B);
        reverse_vector(B.digits);
        mult_power(B, A.digits.size() - B.digits.size());
        reverse_vector(B.digits);
    }
    if (A.digits.size() == 1) {
        BigInteger C = 0;
        for (BigInteger i = 0; i < A; i = i + BigInteger(1))
            C = addition(C, B);
        remove_zeroes(C);
        return C;
    }
    if (A.digits.size() & 1) {
        reverse_vector(A.digits);
        reverse_vector(B.digits);
        mult_power(A, 1);
        mult_power(B, 1);
        reverse_vector(A.digits);
        reverse_vector(B.digits);
    }
    int m = static_cast<int>(A.digits.size() >> 1);
    BigInteger A1, A0, B1, B0;
    A1.convert(A.toString().substr(0, m)); remove_zeroes(A1);
    A0.convert(A.toString().substr(m, m)); remove_zeroes(A0);
    B1.convert(B.toString().substr(0, m)); remove_zeroes(B1);
    B0.convert(B.toString().substr(m, m)); remove_zeroes(B0);
    BigInteger C1 = multiplication(A0, B0); 
    BigInteger C2 = multiplication(A1, B1);
    BigInteger C3 = multiplication(addition(A0, A1), addition(B0, B1));
    C3 = subtraction(C3, addition(C1, C2));
    mult_power(C2, m << 1);
    mult_power(C3, m);
    BigInteger C = addition(addition(C1, C2), C3);
    remove_zeroes(C);
    return C;
}

BigInteger BigInteger::division(BigInteger A, BigInteger B) {
    if (A.digits.size() < B.digits.size())
        return 0;
    size_t iter = B.digits.size() - 1;
    BigInteger res;
    BigInteger temp;
    temp.convert(A.toString().substr(0, iter));
    while (iter < A.digits.size()) {
        temp.digits.push_back(A.digits[iter++]);
        remove_zeroes(temp);
        char new_digit = '0';
        while (temp >= B) {
            new_digit += 1;
            temp = temp - B;
        }
        res.digits.push_back(new_digit);
    }
    remove_zeroes(res);
    return res;
}