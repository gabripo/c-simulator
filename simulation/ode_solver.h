#include <stdio.h>
#include <math.h>

typedef struct 
{
    int nEqs;
    char *odeEqs;
    int *odeICs;
} odeSys;

typedef struct
{
    char *derivativeSub;
    double timeStep;
} finiteDifferenceMethod;

typedef struct
{
    int nEqs;
    double *algEqs;
} algSys;

void odeNumericalConverter( odeSys symbolicSys, finiteDifferenceMethod method, algSys *numericSys );