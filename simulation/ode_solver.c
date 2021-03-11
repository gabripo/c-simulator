#include "ode_solver.h"

void odeNumericalConverter( odeSys symbolicSys, finiteDifferenceMethod method, algSys *numericSys ) 
{
    printf("Conversion of symbolic ODEs to numerical ones, using a Finite Difference scheme...\n");

    /* Substitution of parameters into ODEs */
    double value;
    char *name = NULL;
    name = calloc(1, sizeof name);

    int idxParametersSub = 0;
    while (symbolicSys.parametersSub[idxParametersSub])
    {
        getParameterSubValues(symbolicSys.parametersSub[idxParametersSub], name, &value);
        printf("%s = %d\n", name, value);
        idxParametersSub++;
    }

    // TODO: Composing finite difference equation
    // TODO: Substituting finite difference equation
    // TODO: Creating algebraic equations to solve
};

void getParameterSubValues( char *str, char *name, double *value )
{
    sscanf( str, "%s = %d", name, value);
};

void setParameterSubValues( odeSys sys, char *sub )
{
    int len = strlen(sub);
    int idx = 0;
    
    while (sys.parametersSub[idx]) { idx++; };
    sys.nSubs = idx;

    sys.parametersSub[idx] = calloc( len + 1, sizeof **sys.parametersSub);
    strncpy(sys.parametersSub[idx], sub, len);
    sys.parametersSub[idx][len] = 0;
}