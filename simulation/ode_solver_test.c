#include "ode_solver.c"

int main(int argc, char const *argv[])
{
    odeSys sys;
    finiteDifferenceMethod fwdEuler;
    algSys toSolveEqs;

    sys.nEqs = 1;
    sys.odeEqs = "DxDt - a * x";
    sys.odeICs = (int*) 0;

    sys.parametersSub = NULL;
    sys.parametersSub = calloc(100, sizeof *sys.parametersSub);
    sys.parametersSub[0] = calloc(strlen("a = 1") + 1, sizeof *sys.parametersSub);
    strncpy(sys.parametersSub[0], "a = 1", strlen("a = 1"));
    
    sys.independentVariable = 't';
    sys.derivativeIdentifier = 'D';

    fwdEuler.derivativeSub = "DxDt = ( x(k) - x(k-1) ) / h";
    fwdEuler.timeStepName = 'h';
    fwdEuler.timeStep = 0.1;
    fwdEuler.abscissaIdentifier = 'k';
    fwdEuler.independentVariable = sys.independentVariable;
    fwdEuler.derivativeIdentifier = sys.derivativeIdentifier;

    toSolveEqs.nEqs = 1;
    toSolveEqs.algEqs = (double*) 1;
    
    odeNumericalConverter(sys, fwdEuler, &toSolveEqs);
    return 0;
}
