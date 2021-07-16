#include "ode_solver.c"

#define MAX_NUM_EQS 100
#define MAX_NUM_SUBS 100

int main(int argc, char const *argv[])
{

    /* odeEqs and parametersSub cannot be dynamically allocated at this point, since they would be in contiguous blocks of memory */
    odeSys sys = {
        .nEqs = 0,
        .odeEqs = calloc(MAX_NUM_EQS, sizeof *sys.odeEqs),
        .odeICs = (int*) 0,
        .nSubs = 0,
        .parametersSub = calloc(MAX_NUM_SUBS, sizeof *sys.parametersSub),
        .independentVariable = 't',
        .derivativeIdentifier = 'D',
    };

    setOde(&sys, "DxDt - a * x");
    setOde(&sys, "DxDt - b * x");
    setOde(&sys, "DxDt - ( a + b + c) * x");

    //sys.parametersSub[0] = calloc(strlen("a = 1") + 1, sizeof **sys.parametersSub);
    //strncpy(sys.parametersSub[0], "a = 1", strlen("a = 1"));
    setParameterSubValues(&sys, "a = 1");
    setParameterSubValues(&sys, "b = 2");
    setParameterSubValues(&sys, "c = 3");
    printOdeSys(sys);

    finiteDifferenceMethod fwdEuler = {
        .derivativeSub = "DxDt = ( x(k) - x(k-1) ) / h",
        .timeStepName = 'h',
        .timeStep = 0.1,
        .abscissaIdentifier = 'k',
        .independentVariable = sys.independentVariable,
        .derivativeIdentifier = sys.derivativeIdentifier,
    };

    algSys toSolveEqs = {
        .nEqs = 1,
        .algEqs = (double*) 1,
    };
    
    odeNumericalConverter(sys, fwdEuler, &toSolveEqs);
    printOdeSys(sys);
    return 0;
}
