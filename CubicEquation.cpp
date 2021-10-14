#include <iostream>
#include <cmath>
#include "Complex.h"

using namespace std;

const double EPS = 1e-10;

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
            cout << "x[" << i + 1 << "] = " << roots[i] << endl;
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
    //p = (3ac - b^2) / 3a^2
    double p = (3 * C.a * C.c - pow(C.b, 2.)) / (3 * pow(C.a, 2.));
    //q = (2b^3 - 9abc + 27*a^2*d) / 27a^3
    double q = (2 * pow(C.b, 3.) - 9 * C.a * C.b * C.c + 27 * pow(C.a, 2.) * C.d) /
               (27 * pow(C.a, 3.));
    double m = -q / 2;
    double n2 = pow(q, 2.) / 4 + pow(p, 3.) / 27;
    double n = sqrt(abs(n2));
//    cout << "m = " << m << ", n2 = " << n2 << ", n = " << n << endl;

    Complex u3(m + n);
//    Complex v3(m - n);
    Complex *root_u3 = new Complex[num_roots];
//    Complex *root_v3 = new Complex[num_roots];
    u3.roots(num_roots, root_u3);
//    v3.roots(num_roots, root_v3);
//    for(int i = 0; i < num_roots; ++i) {
//        cout << "u[" << i << "] = " << root_u3[i]
//             << ", v[" << i << "] = " << root_v3[i] << endl;
//    }
    double u, v, t;
    u = choice_root(root_u3, num_roots);
//    v = choice_root(root_v3, num_roots);
    v = -p / (3 * u);
    t = -C.b / (3 * C.a);
//    cout << "u = " << u << ", v = " << v << ", t = " << t << endl;
    Complex omega(-1. / 2, sqrt(3.) / 2);   //omega = -1/2 + sqrt(3)/2 * i = e^((2PI/3)i)
    Complex omega2 = omega * omega;

    roots[0] = u + v + t;                         //x1 = u + v + t
    roots[1] = omega * u + omega2 * v + t;        //x2 = omega * u + omega2 * v + t
    roots[2] = omega2 * u + omega * v + t;        //x3 = omega2 * u + omega * v + t
}

double choice_root(Complex* root, int num) {    //3 roots, choice the real of root, which imag of root < EPS
    double real;
    for(int i = 0; i < num; ++i) {
        if(root[i].imag() < EPS){
            real = root[i].real();
            break;
        }
    }
    return real;
}