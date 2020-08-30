#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

const double EPS = 1e-10;

typedef enum nRootFlags {
    INF_ROOTS = - 1,
    NO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS
} nRootFlags_t;

struct SquareEquation {
    double a = 0,
           b = 0,
           c = 0;

    double  firstRoot = 0,
           secondRoot = 0;

    bool solved = 0;
    nRootFlags_t nRoots = INF_ROOTS;
};

void SolveSquare   (struct SquareEquation* squareEquation);
void SquareSolver  (struct SquareEquation* squareEquation);
void LinearSolver  (struct SquareEquation* squareEquation);
void TrivialSolver (struct SquareEquation* squareEquation);

void PrintResult (struct SquareEquation* squareEquation);
void PrintTitle  ();

bool isZero (double value);

int main() {
    PrintTitle();

    struct SquareEquation se;

    printf ("Enter a, b, c coefficients:\n");
    scanf ("%lg %lg %lg", &se.a, &se.b, &se.c);

    SolveSquare (&se);

    PrintResult (&se);
}

void SolveSquare (struct SquareEquation* se) {

    assert (isfinite(se -> a));
    assert (isfinite(se -> b));
    assert (isfinite(se -> c));

    if (!isZero(se -> a)) {
        SquareSolver (se);
    }

    else if (!isZero(se -> b)) {
        LinearSolver (se);
    }

    else {
        TrivialSolver (se);
    }

    se -> solved = true;
}

void SquareSolver (struct SquareEquation* se) {
    double discriminant = (se -> b) * (se -> b) - 4 * (se -> a) * (se -> c);

    if (discriminant < 0) {
        se -> nRoots = NO_ROOTS;
    }

    else if (isZero(discriminant)) {
        (se -> firstRoot) = (se -> secondRoot) = -(se -> b) / (2 * (se -> a));
        se -> nRoots = ONE_ROOT;
    }

    else {
        double sqrtDiscr = sqrt(discriminant);
         se -> firstRoot = (-(se -> b) + sqrtDiscr) / (2 * (se -> a));
        se -> secondRoot = (-(se -> b) - sqrtDiscr) / (2 * (se -> a));
        se -> nRoots = TWO_ROOTS;
    }
}

void LinearSolver (struct SquareEquation* se) {
    se -> firstRoot = (isZero(se -> c)) ? 0 : -(se -> c) / (se -> b);
    se -> nRoots = ONE_ROOT;
}

void TrivialSolver (struct SquareEquation* se) {
    se -> nRoots = (isZero(se -> c)) ? INF_ROOTS : NO_ROOTS;
}

bool isZero(double value) {
    return fabs(value) < EPS;
}

void PrintResult (struct SquareEquation* se) {
    if (!(se -> solved)) {
        printf ("Sorry, the equation is not solved.\n");
        return;
    }
    switch (se -> nRoots) {
        case NO_ROOTS:
            printf ("No roots\n");
            break;
        case ONE_ROOT:
            printf ("One root: %.4lg\n", se -> firstRoot);
            break;
        case TWO_ROOTS:
            printf ("Roots: %.4lg, %.4lg\n", se -> firstRoot, se -> secondRoot);
            break;
        case INF_ROOTS:
            printf ("Any number is root\n");
            break;
    }
}

void PrintTitle() {
    printf ("Square equation solver");
}
