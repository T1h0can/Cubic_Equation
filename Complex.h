//
// Created by T1h0can on 2021/10/15.
//

#ifndef COMPLEX_COMPLEX_H
#define COMPLEX_COMPLEX_H

#include <iostream>
#include <cmath>

const double PI = 3.14159265358979323846;
const double EPS = 1e-10;

class Complex {
private:
    double r;
    double phi;

    static double to_r(const double& x, const double& y) {
        return sqrt(x * x + y * y);
    }

    static double to_phi(const double& x, const double& y) {
        return atan2(y, x);
    }

public:
    Complex(double a = 0., double b = 0.) : r(a), phi(b) {}

    double radius() const { return r; }
    double& radius() { return r; }
    double arg() const { return phi; }
    double& arg() { return phi; }

    double abs2() const {
        return r * r;
    }

    double abs() const {
        return radius();
    }

    double real() const {
        return r * cos(phi);
    }

    double imag() const {
        return r * sin(phi);
    }

    Complex conjugate() const {         //共轭
        return Complex(r, -phi);
    }

    Complex complex_pow(int n) const {                //整数幂
        return Complex(pow(r, double(n)), phi * double(n));
    }

    Complex& operator+=(const Complex& z) {
        double a = real() + z.real();
        double b = imag() + z.imag();
        r = to_r(a, b);
        phi = to_phi(a, b);
        return *this;
    }

    Complex& operator-=(const Complex& z) {
        double a = real() - z.real();
        double b = imag() - z.imag();
        r = to_r(a, b);
        phi = to_phi(a, b);
        return *this;
    }

    Complex& operator*=(const Complex& z) {
        r *= z.r;
        phi += z.phi;
        return *this;
    }

    Complex& operator/=(const Complex& z) {
        r /= z.r;
        phi -= z.phi;
        return *this;
    }

    void roots(int n, Complex* roots) const;
};


inline Complex operator+(const Complex& u, const Complex& v) {
    Complex res = u;
    res += v;
    return res;
}

inline Complex operator-(const Complex& u, const Complex& v) {
    Complex res = u;
    res -= v;
    return res;
}

inline Complex operator*(const Complex& u, const Complex& v) {
    Complex res = u;
    res *= v;
    return res;
}

inline Complex operator/(const Complex& u, const Complex& v) {
    Complex res = u;
    res /= v;
    return res;
}

inline std::ostream& operator<<(std::ostream& s, const Complex& z) {
    s << z.radius() << " * e^(" << z.arg() << "*i)";
    return s;
}

inline std::istream& operator>>(std::istream& s, Complex& z) {
    s >> z.radius() >> z.arg();
    return s;
}



#endif //COMPLEX_COMPLEX_H
