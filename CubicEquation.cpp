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
double choice_root(Complex* root, int num = 3);

int main() {
    Coeff coeffi;
    Complex* roots = new Complex[3];
    while (true) {
        cout << "Input coefficient a,b,c,d of cubic equation:" << endl;
        cin >> coeffi.a >> coeffi.b >> coeffi.c >> coeffi.d;
        if(!cin.good())
            break;
        printEquation(coeffi);
//    coeffi.func();
//    printEquation(coeffi);
        cout << "Roots of cubic equation:" << endl;
        calcRootsOfCubicEquation(coeffi, roots);
        for(int i = 0; i < 3; ++i) {
            cout << "x[" << i + 1 << "] = " << roots[i] << "\t" << roots[i].real() << " + " << roots[i].imag() << "i" << endl;;
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
    double p = (3 * C.a * C.c - pow(C.b, 2.)) / (3 * pow(C.a, 2.));     //p = (3ac - b^2) / 3a^2
    double q = (2 * pow(C.b, 3.) - 9 * C.a * C.b * C.c + 27 * pow(C.a, 2.) * C.d) /
               (27 * pow(C.a, 3.));                                     //q = (2b^3 - 9abc + 27*a^2*d) / 27a^3
    double m = -q / 2;
    double n2 = pow(q, 2.) / 4 + pow(p, 3.) / 27;
    double n = sqrt(abs(n2));

    Complex u3(m + n);                        //u3 = (-q/2 + sqrt(|(q^2) / 4 + (p^3)/27|), 0.i)
    Complex *root_u3 = new Complex[num_roots];
    u3.roots(num_roots, root_u3);

    double u, v, t;
    u = choice_root(root_u3, num_roots);
    v = -p / (3 * u);
    t = -C.b / (3 * C.a);

    Complex omega(1, 2 * PI / 3);   //omega = -1/2 + sqrt(3)/2 * i = e^((2PI/3)i)
    Complex omega2 = omega * omega;

    roots[0] = u + v + t;                         //x1 = u + v + t
    roots[1] = omega * u + omega2 * v + t;        //x2 = omega * u + omega2 * v + t
    roots[2] = omega2 * u + omega * v + t;        //x3 = omega2 * u + omega * v + t
}

double choice_root(Complex* root, int num) {    //3 roots, choice the real of root, which imag of root < EPS
    double real;
    for(int i = 0; i < num; ++i) {
        if(root[i].arg() < EPS){
            real = root[i].real();
            break;
        }
    }
    return real;
}