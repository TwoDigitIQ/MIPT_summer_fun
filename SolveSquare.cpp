#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

const int INF_ROOTS = -1;
const double ZERO = 1e-10;

void CheckZeroThreshold (double* a, double* b, double* c) {
    if (abs(*a) <= ZERO) *a = 0;
    if (abs(*b) <= ZERO) *b = 0;
    if (abs(*c) <= ZERO) *c = 0;
}

int SolveSquare (double a, double b, double c, double* firstRoot, double* secondRoot) {

    assert (isfinite(a));
    assert (isfinite(b));
    assert (isfinite(c));

    assert (firstRoot != NULL);
    assert (secondRoot != NULL);
    assert (firstRoot != secondRoot);

    CheckZeroThreshold (&a, &b, &c);

    if (a) {
        double discriminant = b * b - 4 * a * c;

        if (discriminant < 0) {
            return 0;
        }

        double sqrtDiscr = sqrt(discriminant);
         *firstRoot = (-b + sqrtDiscr) / (2 * a);
        *secondRoot = (-b - sqrtDiscr) / (2 * a);

        return (discriminant) ? 2 : 1;
    }

    if (b) {
        *firstRoot = -c / b;
        return 1;
    }

    return (c) ? 0 : INF_ROOTS;
}

int main() {
    printf ("Square equation solver");
    printf ("Enter a, b, c coefficients:\n");

    double a = 0, b = 0, c = 0;
    scanf ("%lg %lg %lg", &a, &b, &c);

    double firstRoot = 0, secondRoot = 0;
    int nRoots = SolveSquare(a, b, c, &firstRoot, &secondRoot);

    switch (nRoots) {
        case 0:
            printf ("No roots\n");
            break;
        case 1:
            printf ("One root: %.4lg\n", firstRoot);
            break;
        case 2:
            printf ("Roots: %.4lg, %.4lg\n", firstRoot, secondRoot);
            break;
        case INF_ROOTS:
            printf ("Any number is root\n");
            break;
        default:
            printf ("ERROR: main(): nRoots = %d\n", nRoots);
            return 1;
    }
}
