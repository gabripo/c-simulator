#include "ode_solver.c"

int main(int argc, char const *argv[])
{

    // TODO : Same way to create 2D char arrays of parametersSub for odeEqs
    odeSys sys = {
        .nEqs = 1,
        .odeEqs = "DxDt - a * x",
        .odeICs = (int*) 0,
        .nSubs = 0,
        .parametersSub = calloc(sys.nSubs, sizeof *sys.parametersSub),
        .independentVariable = 't',
        .derivativeIdentifier = 'D',
    };

    //sys.parametersSub[0] = calloc(strlen("a = 1") + 1, sizeof **sys.parametersSub);
    //strncpy(sys.parametersSub[0], "a = 1", strlen("a = 1"));
    setParameterSubValues(&sys, "a = 1");
    setParameterSubValues(&sys, "b = 2");
    setParameterSubValues(&sys, "c = 3");

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
    return 0;
}
