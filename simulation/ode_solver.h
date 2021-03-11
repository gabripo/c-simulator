#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct 
{
    int nEqs;
    char *odeEqs;
    int *odeICs;
    int nSubs;
    char **parametersSub;
    char independentVariable;
    char derivativeIdentifier;
} odeSys;

typedef struct
{
    char *derivativeSub;
    char timeStepName;
    double timeStep;
    char abscissaIdentifier;
    char independentVariable;
    char derivativeIdentifier;
} finiteDifferenceMethod;

typedef struct
{
    int nEqs;
    double *algEqs;
} algSys;

void odeNumericalConverter( odeSys symbolicSys, finiteDifferenceMethod method, algSys *numericSys );
void getParameterSubValues( char *str, char *name, double *value );
void setParameterSubValues( char **str, char *sub );