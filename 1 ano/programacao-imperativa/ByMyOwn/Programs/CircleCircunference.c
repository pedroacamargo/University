#include <stdio.h>
#include <math.h>

int main() {

    const double PI = 3.14159;
    double radius;
    double circunference, area;

    printf("\nEnter radius of a circle: ");
    scanf("%lf", &radius);

    circunference = round(2 * PI * radius);
    area = round(PI * pow(radius, 2));

    printf("Cirfunference: %.0lf", circunference);
    printf("\nArea: %.0lf", area);

    return 0;
}