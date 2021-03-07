#include "ode_solver.h"

void odeNumericalConverter( odeSys symbolicSys, finiteDifferenceMethod method, algSys *numericSys ) 
{
    printf("Conversion of symbolic ODEs to numerical ones, using a Finite Difference scheme...\n");

    /* Substitution of parameters into ODEs */
    double value;
    char name[10]; // Impossible to pre-allocate
    // printf("%s\n", symbolicSys.parametersSub);
    sscanf( symbolicSys.parametersSub, "%s = %d", name, &value);
    printf("%s = %d\n", name, value);

    // TODO: Composing finite difference equation
    // TODO: Substituting finite difference equation
    // TODO: Creating algebraic equations to solve
};