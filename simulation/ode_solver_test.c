#include "ode_solver.c"

int main(int argc, char const *argv[])
{
    odeSys sys;
    finiteDifferenceMethod fwdEuler;
    algSys toSolveEqs;

    // TODO: Reasonable ODE problem
    sys.nEqs = 1;
    sys.odeEqs = (char*) "a";
    sys.odeICs = (int*) 0;

    fwdEuler.derivativeSub = (char*) "fd";
    fwdEuler.timeStep = 0.1;

    toSolveEqs.nEqs = 1;
    toSolveEqs.algEqs = (double*) 1;
    
    odeNumericalConverter(sys, fwdEuler, &toSolveEqs);
    return 0;
}
