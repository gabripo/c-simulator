#include "ode_solver.h"

void odeNumericalConverter( odeSys symbolicSys, finiteDifferenceMethod method, algSys *numericSys ) 
{
    printf("Conversion of symbolic ODEs to numerical ones, using a Finite Difference scheme...\n");

    /* Substitution of parameters into ODEs */
    double value;
    char *name = NULL;
    name = calloc(1, sizeof name);

    getParameterSubValues(symbolicSys.parametersSub[0], name, &value);
    printf("%s = %d\n", name, value);

    // TODO: Composing finite difference equation
    // TODO: Substituting finite difference equation
    // TODO: Creating algebraic equations to solve
};

void getParameterSubValues( char *str, char *name, double *value )
{
    sscanf( str, "%s = %d", name, value);
};

void setParameterSubValues( char **str, char *sub )
{
    int len = strlen(sub);

    str[0] = calloc( len + 1, sizeof **str);
    strncpy(str[0], sub, len);
}