#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

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

		bool operator ==(const BigInteger& other) const;
		bool operator !=(const BigInteger& other) const;
		bool operator <(const BigInteger& other) const;
		bool operator >(const BigInteger& other) const;
		bool operator <=(const BigInteger& other) const;
		bool operator >=(const BigInteger& other) const;

		std::string toString();

		operator bool() const;

		friend std::istream& operator >>(std::istream& stream, BigInteger& object);
		friend std::ostream& operator <<(std::ostream& stream, const BigInteger& object);

	private:

		std::vector <char> digits;
		bool sign = false;

		void remove_zeroes(BigInteger& temp);
		void mult_power(BigInteger& temp, int step = 0);
        template <typename T> void reverse_vector(std::vector <T>& vect);
        void convert(std::string number);

        BigInteger addition(BigInteger A, BigInteger B);
		BigInteger subtraction(BigInteger A, BigInteger B);
		BigInteger multiplication(BigInteger A, BigInteger B);
		BigInteger division(BigInteger A, BigInteger B);
};