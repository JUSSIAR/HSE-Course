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
    (*this) -= ((*this) / _other) * _other;
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

BigInteger BigInteger::operator -() {
    BigInteger copy = *this;
    copy.sign ^= true;
    return copy;
}

BigInteger& BigInteger::operator ++() {
    (*this) += 1;
    return (*this);
}

BigInteger& BigInteger::operator --() {
    (*this) -= 1;
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

bool BigInteger::operator <(const BigInteger& other) {
    if (digits.size() != other.digits.size())
        return digits.size() < other.digits.size();
    return digits < other.digits;
}

bool BigInteger::operator >(const BigInteger& other) {
    return (!((*this) < other) && !((*this) == other));
}

bool BigInteger::operator <=(const BigInteger& other) {
    return (((*this) < other) || ((*this) == other));
}

bool BigInteger::operator >=(const BigInteger& other) {
    return (((*this) > other) || ((*this) == other));
}

bool BigInteger::operator ==(const BigInteger& other) {
     return (!((*this) < other) && !(other < (*this)));
}

bool BigInteger::operator !=(const BigInteger& other) {
    return (!((*this) == other));
}

std::string BigInteger::toString() {
    std::string result = (sign) ? "-" : "";
    for (const auto& digit : digits)
        result += digit;
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
    if (temp.toString() != "0")
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
        C.digits[i] = tmp % 10 + '0';
        p = tmp / 10;
    }
    reverse_vector(C.digits);
    remove_zeroes(C);
    return C;
}

BigInteger BigInteger::subtraction(BigInteger A, BigInteger B) {
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
    if ((A.digits.size() == 1) && (B.digits.size() == 1)) {
        BigInteger C = 0;
        for (BigInteger i = 0; i < A; i = i + BigInteger(1))
            C += B;
        return C;
    }
    int m1 = static_cast<int>(A.digits.size() / 2);
    int m2 = static_cast<int>((A.digits.size() + 1) / 2);
    BigInteger A1;
    A1.convert(A.toString().substr(0, m1));
    BigInteger A0;
    A0.convert(A.toString().substr(m1, m2));
    BigInteger B1;
    B1.convert(B.toString().substr(0, m1));
    BigInteger B0;
    B0.convert(B.toString().substr(m1, m2));
    BigInteger C1 = A0 * B0;
    BigInteger C2 = A1 * B1;
    BigInteger C3 = (A0 + A1) * (B0 + B1);
    C3 = C3 - (C1 + C2);
    mult_power(C2, 2 * m2);
    mult_power(C3, m2);
    BigInteger C = C1 + C2 + C3;
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