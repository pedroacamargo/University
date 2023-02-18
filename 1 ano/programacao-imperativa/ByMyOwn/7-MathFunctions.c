#include <stdio.h>
#include <math.h> // will import the math gallery

int main() {
    double A = sqrt(9); // square root
    double B = pow(2,4); // will power the number with 2 parameters, the number and the power
    int C = round(3.14); // will round the number up or down
    int D = ceil(3.14); // rounded up
    int E = floor(3.99); // rounded down
    double F = fabs(-100); // will make negative numbers positive
    double G = log(3); // will give the logarithm of a number
    double H = sin(45);
    double I = cos(45);
    double J = tan(45);

    printf("\n%d",C);
    printf("\n%d",D);
    printf("\n%d",E);
    printf("\n%lf",F);

    return 0;
}