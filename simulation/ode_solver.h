#include <stdio.h>
#include <math.h>

typedef struct 
{
    int nEqs;
    char *odeEqs;
    int *odeICs;
    char *parametersSub;
    char independentVariable;
} odeSys;

typedef struct
{
    char *derivativeSub;
    char timeStepName;
    double timeStep;
    char abscissaIdentifier;
    char independentVariable;
} finiteDifferenceMethod;

typedef struct
{
    int nEqs;
    double *algEqs;
} algSys;

void odeNumericalConverter( odeSys symbolicSys, finiteDifferenceMethod method, algSys *numericSys );