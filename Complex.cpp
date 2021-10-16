//
// Created by T1h0can on 2021/10/15.
//

#include "Complex.h"
#include <cmath>

using namespace std;

//const double PI = 3.14159265358979323846;

void Complex::roots(int n, Complex* roots) const {      //r^(1/n) * e ^((phi/n + 2 * pi * k / n) * i)
    double new_r = pow(r, 1. / double(n));
    double new_phi = phi / double(n);
    double dphi = 2 * PI / double(n);

    for(int i = 0; i < n; ++i){
        roots[i] = Complex(new_r, new_phi);
        new_phi += dphi;
    }
}