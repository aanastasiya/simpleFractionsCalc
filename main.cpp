#include <iostream>
#include <exception>
#include <string>
#include <stdexcept>
using namespace std;

int GreatestCommonDivisor(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return GreatestCommonDivisor(b, a % b);
    }
}

class Rational {
public:
    Rational() {
        num = 0;
        den = 1;
    }
    Rational(int numerator, int denominator) {
        if (denominator == 0) {
            throw invalid_argument("Invalid argument");
        }

        const int gcd = GreatestCommonDivisor(numerator, denominator);
        num = numerator / gcd;
        den = denominator / gcd;

        if (den < 0) {
            den = -den;
            num = -num;
        }
    }

    int Numerator() const {
        return num;
    }

    int Denominator() const {
        return den;
    }

private:
    int num;
    int den;
};

Rational operator+ (const Rational& lhs, const Rational& rhs) {
    if (lhs.Denominator() == rhs.Denominator()) {
        return Rational(lhs.Numerator() + rhs.Numerator(), lhs.Denominator());
    }
    else {
        return Rational(lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator());
    }
}

Rational operator- (const Rational& lhs, const Rational& rhs) {
    if (lhs.Denominator() == rhs.Denominator()) {
            return Rational(lhs.Numerator() - rhs.Numerator(), lhs.Denominator());
    }
    else {
        return Rational(lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator());
    }
}

Rational operator* (const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator/ (const Rational& lhs, const Rational& rhs) {
    if (rhs.Numerator() == 0) {
        throw domain_error("Division by zero");
    }
    else {
        return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
    }
}

bool operator== (const Rational& lhs, const Rational& rhs) {
    if (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator()) {
        return true;
    }
    else {
        return false;
    }
}

ostream& operator<< (ostream& stream, const Rational& number) {
    stream << number.Numerator() << '/' << number.Denominator();
    return stream;
}

istream& operator>> (istream& stream, Rational& number) {
    int num, den;
    char c;
    stream >> num >> c >> den;
    if (stream && c == '/') {
        number = Rational(num, den);
    }
    return stream;
}

bool operator< (const Rational& lhs, const Rational& rhs) {
    if (lhs.Denominator() == rhs.Denominator()) {
        return lhs.Numerator() < rhs.Numerator();
    }
    else {
        return lhs.Numerator() * rhs.Denominator() < rhs.Numerator() * lhs.Denominator();
    }
}


int main() {
    Rational lhs, rhs;
    string operation;
    try {
        cin >> lhs >> operation >> rhs;
    }
    catch (invalid_argument& err) {
        cout << err.what();
        return 0;
    }

    if (operation == "+") {
        cout << lhs + rhs;
    }
    else if (operation == "-") {
        cout << lhs - rhs;
    }
    else if (operation == "*") {
        cout << lhs * rhs;
    }
    else if (operation == "/") {
        try {
            cout << lhs / rhs;
        }
        catch (domain_error& err) {
            cout << err.what();
            return 0;
        }
    }

    return 0;
}
