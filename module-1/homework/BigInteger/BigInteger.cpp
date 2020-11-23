#include "biginteger.h"

BigInteger::BigInteger() {
    digits.resize(1, '0');
}

BigInteger::BigInteger(int value) {
    convert(std::to_string(value));
}

BigInteger::BigInteger(const BigInteger& other) = default;
BigInteger::~BigInteger() = default;

BigInteger& BigInteger::operator=(int value) {
    convert(std::to_string(value));
    return *this;
}

BigInteger& BigInteger::operator+=(const BigInteger& other) {
    if (sign == other.sign) {
        addition(digits, other.digits);
        return *this;
    }
    if (!sign) {
        if (module_compare(digits, other.digits)) {
            std::vector<char> copy(digits);
            digits = other.digits;
            subtraction(digits, copy);
            sign = true;
        } else {
            subtraction(digits, other.digits);
        }
    } else {
        if (module_compare(other.digits, digits)) {
            subtraction(digits, other.digits);
        } else {
            std::vector<char> copy(digits);
            digits = other.digits;
            subtraction(digits, copy);
            sign = false;
        }
    }
    sign = sign && bool(*this);
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& other) {
    sign = !sign;
    operator+=(other);
    sign = !sign && bool(*this);
    return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& other) {
    digits = multiplication(digits, other.digits);
    sign = (sign != other.sign) && bool(*this);
    return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& other) {
    digits = division(digits, other.digits);
    sign = (sign != other.sign) && bool(*this);
    return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& other) {
    subtraction(digits, multiplication(division(digits, other.digits), other.digits));
    sign = (sign != other.sign) && bool(*this);
    return *this;
}

BigInteger BigInteger::operator+(const BigInteger& other) {
    return operator+=(BigInteger(*this));
}

BigInteger BigInteger::operator-(const BigInteger& other) {
    return operator-=(BigInteger(*this));
}

BigInteger BigInteger::operator*(const BigInteger& other) {
    return operator*=(BigInteger(*this));
}

BigInteger BigInteger::operator/(const BigInteger& other) {
    return operator/=(BigInteger(*this));
}

BigInteger BigInteger::operator%(const BigInteger& other) {
    return operator%=(BigInteger(*this));
}

BigInteger BigInteger::operator-() const {
    BigInteger copy(*this);
    copy.sign = !copy.sign;
    return copy;
}

BigInteger& BigInteger::operator++() {
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
    return *this;
}

BigInteger& BigInteger::operator--() {
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
    return *this;
}

BigInteger BigInteger::operator++(int) {
    BigInteger copy(*this);
    ++(*this);
    return copy;
}

BigInteger BigInteger::operator--(int) {
    BigInteger copy(*this);
    --(*this);
    return copy;
}

bool operator<(const BigInteger& A, const BigInteger& B) {
    if (A.sign == B.sign) {
        if (!A.sign) {
            if (A.digits.size() != B.digits.size())
                return A.digits.size() < B.digits.size();
            return A.digits < B.digits;
        } else {
            if (A.digits.size() != B.digits.size())
                return A.digits.size() > B.digits.size();
            return A.digits > B.digits;
        }
    }
    return A.sign;
}

bool operator>(const BigInteger& A, const BigInteger& B) {
    return !operator<(A, B) && !operator==(A, B);
}

bool operator<=(const BigInteger& A, const BigInteger& B) {
    return operator<(A, B) || operator==(A, B);
}

bool operator>=(const BigInteger& A, const BigInteger& B) {
    return operator>(A, B) || operator==(A, B);
}

bool operator==(const BigInteger& A, const BigInteger& B) {
    return (A.sign == B.sign) && (A.digits == B.digits);
}

bool operator!=(const BigInteger& A, const BigInteger& B) {
    return !operator==(A, B);
}

std::string BigInteger::toString() const {
    std::string result = (sign) ? "-" : "";
    for (const auto& digit : digits)
        result.push_back(digit);
    return result;
}

BigInteger::operator bool() const {
    return !(digits.size() == 1 && digits[0] == '0');
}

std::istream& operator>>(std::istream& stream, BigInteger& object) {
    std::string number;
    stream >> number;
    object.convert(number);
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const BigInteger& object) {
    return stream << object.toString();
}

bool BigInteger::module_compare(const std::vector<char>& A, const std::vector<char>& B) {
    if (A.size() < B.size())
        return true;
    if (A.size() > B.size())
        return false;
    return A < B;
}

void BigInteger::remove_zeroes(std::vector<char>& temp) {
    if (temp[0] != '0')
        return;
    reverse_vector(temp);
    while (temp.size() > 1 && temp.back() == '0')
        temp.pop_back();
    reverse_vector(temp);
}

void BigInteger::mult_power(std::vector<char>& temp, int step) {
    while (step--)
        temp.push_back('0');
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
    remove_zeroes(digits);
}

void BigInteger::addition(std::vector<char>& A, const std::vector<char>& B) {
    if (A.size() <= B.size()) {
        reverse_vector(A);
        int pw = static_cast<int>(B.size() - A.size());
        mult_power(A, pw + 1);
        reverse_vector(A);
    }
    int p = 0;
    int index = static_cast<int>(A.size()) - 1;
    for (size_t i = B.size(); i > 0; i--, index--) {
        int tmp = p + A[index] - '0' + B[i - 1] - '0';
        A[index] = (tmp % 10) + '0';
        p = tmp / 10;
    }
    for (; p > 0; index--) {
        int tmp = p + A[index] - '0';
        A[index] = (tmp % 10) + '0';
        p = tmp / 10;
    }
    remove_zeroes(A);
}

void BigInteger::subtraction(std::vector<char>& A, const std::vector<char>& B) {
    int index = static_cast<int>(A.size()) - 1;
    for (size_t i = B.size(); i > 0; i--, index--) {
        if (A[index] >= B[i - 1]) {
            A[index] = A[index] - B[i - 1] + '0';
            continue;
        }
        int it = static_cast<int>(index) - 1;
        while (it >= 0 && A[it] == '0')
            --it;
        A[it++]--;
        while (it != index)
            A[it++] = '9';
        A[index] = 10 + (A[index] - B[i - 1]) + '0';
    }
    remove_zeroes(A);
}

std::vector<char> BigInteger::multiplication(const std::vector<char>& _A, const std::vector<char>& _B) {
    std::vector<char> A(_A);
    std::vector<char> B(_B);
    if (A.size() != B.size()) {
        if (A.size() < B.size())
            std::swap(A, B);
        reverse_vector(B);
        mult_power(B, A.size() - B.size());
        reverse_vector(B);
    }
    if (A.size() == 1) {
        std::vector<char> C(1, '0');
        for (int i = 0; i < (A[0] - '0'); i++)
            addition(C, B);
        remove_zeroes(C);
        return C;
    }
    if (A.size() & 1) {
        reverse_vector(A);
        reverse_vector(B);
        mult_power(A, 1);
        mult_power(B, 1);
        reverse_vector(A);
        reverse_vector(B);
    }
    int m = static_cast<int>(A.size() >> 1);
    std::vector<char> A1(A.begin() + 0, A.begin() + m); remove_zeroes(A1);
    std::vector<char> A0(A.begin() + m, A.begin() + 2 * m); remove_zeroes(A0);
    std::vector<char> B1(B.begin() + 0, B.begin() + m); remove_zeroes(B1);
    std::vector<char> B0(B.begin() + m, B.begin() + 2 * m); remove_zeroes(B0);
    std::vector<char> C1 = multiplication(A0, B0);
    std::vector<char> C2 = multiplication(A1, B1);
    addition(A0, A1);
    addition(B0, B1);
    std::vector<char> C3 = multiplication(A0, B0);
    subtraction(C3, C1);
    subtraction(C3, C2);
    mult_power(C2, m << 1);
    mult_power(C3, m);
    std::vector<char> C(1, '0');
    addition(C, C1);
    addition(C, C2);
    addition(C, C3);
    remove_zeroes(C);
    return C;
}

std::vector<char> BigInteger::division(const std::vector<char>& _A, const std::vector<char>& _B) {
    std::vector<char> A(_A);
    std::vector<char> B(_B);
    if (A.size() < B.size())
        return {0};
    size_t iter = B.size() - 1;
    std::vector<char> res(1, '0');
    std::vector<char> temp(A.begin() + 0, A.begin() + iter);
    while (iter < A.size()) {
        temp.push_back(A[iter++]);
        remove_zeroes(temp);
        char new_digit = '0';
        while (!module_compare(temp, B)) {
            new_digit += 1;
            subtraction(temp, B);
        }
        res.push_back(new_digit);
    }
    remove_zeroes(res);
    return res;
}
