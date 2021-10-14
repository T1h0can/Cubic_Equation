#ifndef COMPLEX_H
#define COMPLEX_H 1

#include <cmath>
#include <iostream>

// Bad style!
// using namespace std;

class Complex {
private:
    double a;
    double b;
    // z = r*e^(i*phi)
public:
    Complex(double x = 0., double y = 0.):
        a(x),
        b(y)
    {}
    
    // Bad style:
    // Complex(double x = 0., double y = 0.) {
    //     a = x; b = y;
    // }
    
    // Destructor
    // ~Complex() {}
    
    /*
    // Copy constructor
    Complex(const Complex& z):
        a(z.a),
        b(z.b)
    {}
    */
    
    double real() const { return a; }   // double r = z.real();返回实部
    double& real() { return a; }        // z.real() = 0.5;
    double imag() const { return b; }   //返回虚部
    double& imag() { return b; }

    double abs2() const {
        return a*a + b*b;
    }

    double abs() const {
        return sqrt(abs2());
    }

    double arg() const {                //辅角
        return atan2(b, a);
    }
    
    /*...
    // z = u + v;  z = u.operator+(v);
    Complex operator+(const Complex& z) const {
        return Complex(a + z.a, b + z.b);
    }
    ...*/

    Complex& operator+=(const Complex& z) {
        a += z.a;
        b += z.b;
        return *this;
    }
    
    Complex& operator-=(const Complex& z) {
        a -= z.a;
        b -= z.b;
        return *this;
    }
    
    Complex& operator*=(const Complex& z) {
        double r = a*z.a - b*z.b;
        double i = a*z.b + b*z.a;
        a = r;
        b = i;
        return *this;
    }
    
    Complex conjugate() const {         //共轭
        return Complex(a, -b);
    }
    
    Complex inverse() const {
        double mod2 = abs2();
        double r = a/mod2;
        double i = (-b)/mod2;
        return Complex(r, i);
    }
    
    Complex& operator/=(const Complex& z) {
        *this *= z.inverse();
        return *this;
    }
    
    void roots(int n, Complex* root) const;
};

inline Complex operator+(
    const Complex& u, const Complex& v
) {
    Complex res = u;
    res += v;
    return res;
}

inline Complex operator+(const Complex& u, const double& x) {
    Complex v(x, 0);
    Complex res = u;
    res += v;
    return res;
}

inline Complex operator-(
    const Complex& u, const Complex& v
) {
    Complex res = u;
    res -= v;
    return res;
}

inline Complex operator*(
    const Complex& u, const Complex& v
) {
    Complex res = u;
    res *= v;
    return res;
}

inline Complex operator*(const Complex& u, const double& x) {
    Complex v(x, 0);
    Complex res = u;
    res *= v;
    return res;
}

inline Complex operator/(
    const Complex& u, const Complex& v
) {
    Complex res = u;
    res /= v;
    return res;
}

//inline std::ostream& operator<<(std::ostream& s, const Complex& z) {
//    s << z.real() << " + " << z.imag() << "*i";
//    return s;
//}

//rewrite output of complex numbers in exponential form
inline std::ostream& operator<<(std::ostream& s, const Complex& z) {
    s << z.abs() << " * e^(" << z.arg() << "*i)";
    return s;
}

inline std::istream& operator>>(std::istream& s, Complex& z) {
    s >> z.real() >> z.imag();
    return s;
}

#endif
