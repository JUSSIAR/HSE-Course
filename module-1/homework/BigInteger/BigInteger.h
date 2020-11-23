#include <iostream>
#include <vector>
#include <string>

class BigInteger
{
    public:

        BigInteger();
        BigInteger(const BigInteger& other);
        BigInteger(int value);

        ~BigInteger();

        BigInteger& operator =(int value);

        BigInteger& operator +=(const BigInteger& other);
        BigInteger& operator -=(const BigInteger& other);
        BigInteger& operator *=(const BigInteger& other);
        BigInteger& operator /=(const BigInteger& other);
        BigInteger& operator %=(const BigInteger& other);

        BigInteger operator +(const BigInteger& other);
        BigInteger operator -(const BigInteger& other);
        BigInteger operator *(const BigInteger& other);
        BigInteger operator /(const BigInteger& other);
        BigInteger operator %(const BigInteger& other);

        BigInteger operator -() const;

        BigInteger& operator ++();
        BigInteger& operator --();

        BigInteger operator ++(int);
        BigInteger operator --(int);

        friend bool operator ==(const BigInteger& A, const BigInteger& B);
        friend bool operator !=(const BigInteger& A, const BigInteger& B);
        friend bool operator <(const BigInteger& A, const BigInteger& B);
        friend bool operator >(const BigInteger& A, const BigInteger& B);
        friend bool operator <=(const BigInteger& A, const BigInteger& B);
        friend bool operator >=(const BigInteger& A, const BigInteger& B);

        std::string toString() const;

        operator bool() const;

        friend std::istream& operator >>(std::istream& stream, BigInteger& object);
        friend std::ostream& operator <<(std::ostream& stream, const BigInteger& object);

    private:

        std::vector <char> digits;
        bool sign = false;

        bool module_compare(const std::vector<char>& A, const std::vector<char>& B);

        void remove_zeroes(std::vector<char>& temp);
        void mult_power(std::vector<char>& temp, int step = 0);
        template <typename T> void reverse_vector(std::vector <T>& vect);
        void convert(std::string number);

        void addition(std::vector<char>& A, const std::vector<char>& B);
        void subtraction(std::vector<char>& A, const std::vector<char>& B);
        std::vector<char> multiplication(const std::vector<char>& _A, const std::vector<char>& _B);
        std::vector<char>  division(const std::vector<char>& _A, const std::vector<char>& _B);
};