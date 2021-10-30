//
// Created by T1h0can on 2021/10/16.
//

#include <iostream>
#include <cmath>
#include "Complex.h"

using namespace std;

//const double EPS = 1e-10;
//const double PI = 3.14159265358979323846;

typedef struct _coefficients_of_equation{
    double a;
    double b;
    double c;
    double d;
    void func() {
        b /= a;
        c /= a;
        d /= a;
        a /= a;
    }
} Coeff;

void printCoefficient(double& k);
void printEquation(Coeff& C);
void calcRootsOfCubicEquation(Coeff& C, Complex *roots);
void printRoots(Complex* root, int num = 3);

int main() {
    Coeff coeffi;
    Complex* roots = new Complex[3];
    while (true) {
        cout << "Input coefficient a,b,c,d of cubic equation:" << endl;
        cin >> coeffi.a >> coeffi.b >> coeffi.c >> coeffi.d;
        if(!cin.good())
            break;
        printEquation(coeffi);
        calcRootsOfCubicEquation(coeffi, roots);
        cout << "Roots of cubic equation:" << endl;
        for(int i = 0; i < 3; ++i) {
            cout << "x[" << i + 1 << "] = " << roots[i] << " = " << roots[i].real() << " + " << roots[i].imag() << "i" << endl;;
        }
    }
    free(roots);
    return 0;
}

void printEquation(Coeff& C) {
    printCoefficient(C.a);
    cout << " * x^3 + ";
    printCoefficient(C.b);
    cout << " * x^2 + ";
    printCoefficient(C.c);
    cout << " * x + ";
    printCoefficient(C.d);
    cout << " = 0" << endl;
}

void printCoefficient(double& k) {                          //when koeff is negative add "()"
    if(k < 0)
        cout << "(" << k << ")";
    else
        cout << k;
}

void calcRootsOfCubicEquation(Coeff& C, Complex *roots) {
    const int num_roots = 3;
    //x^3 +px + q = 0, x = x_ + t, t = -b/(3a)
    double p = (3 * C.a * C.c - pow(C.b, 2.)) / (3 * pow(C.a, 2.));     //p = (3ac - b^2) / 3a^2
    double q = (2 * pow(C.b, 3.) - 9 * C.a * C.b * C.c + 27 * pow(C.a, 2.) * C.d) /
               (27 * pow(C.a, 3.));                                     //q = (2b^3 - 9abc + 27*a^2*d) / 27a^3
    double t = -C.b / (3 * C.a);
    double m = -q / 2;
    double n2 = pow(q, 2.) / 4 + pow(p, 3.) / 27;
    double n = sqrt(abs(n2));

    Complex u3;                                 //u3 = (-q/2 + sqrt(|(q^2) / 4 + (p^3)/27|), 0.i)
    if(n2 < 0) {
        u3.toExp(m, n);
    } else {
        u3.toExp(m + n, 0);
    }
//    cout << "u3 = " << u3 << endl;
    Complex *root_u3 = new Complex[num_roots];
    u3.roots(num_roots, root_u3);
//    cout << "root_u:" << endl;
//    printRoots(root_u3, num_roots);

    Complex u, v;
    u = root_u3[0];
    v.toExp(-p, 0);
    v /= (3 * u);

    Complex omega(1, 2 * PI / 3);   //omega = -1/2 + sqrt(3)/2 * i = e^((2PI/3)i)
    Complex omega2 = omega * omega;

    roots[0] = u + v + t;                         //x1 = u + v + t
    roots[1] = omega * u + omega2 * v + t;        //x2 = omega * u + omega2 * v + t
    roots[2] = omega2 * u + omega * v + t;        //x3 = omega2 * u + omega * v + t
}

void printRoots(Complex* root, int num) {
    for(int i =0; i < num; ++i) {
        cout << root[i] << endl;
    }
}
