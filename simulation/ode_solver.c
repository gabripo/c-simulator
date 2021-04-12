#include "ode_solver.h"

void odeNumericalConverter( odeSys symbolicSys, finiteDifferenceMethod method, algSys *numericSys ) 
{
    printf("Conversion of symbolic ODEs to numerical ones, using a Finite Difference scheme...\n");

    /* Substitution of parameters into ODEs */
    double value;
    char *name = NULL;
    name = calloc(1, sizeof name);

    int idxParametersSub = 0;
    for ( idxParametersSub = 0; idxParametersSub < symbolicSys.nSubs; idxParametersSub++)
    {
        getParameterSubValues(symbolicSys.parametersSub[idxParametersSub], name, &value);
        printf("%s = %d\n", name, value);
        idxParametersSub++;
    }

    applySubValues(&symbolicSys);

    // TODO: Composing finite difference equation
    // TODO: Substituting finite difference equation
    // TODO: Creating algebraic equations to solve
};

void getParameterSubValues( char *str, char *name, double *value )
{
    sscanf( str, "%s = %d", name, value);
};

void setParameterSubValues( odeSys *sys, char *sub )
{
    int len = strlen(sub);

    sys->parametersSub[sys->nSubs] = calloc( len + 1, sizeof **sys->parametersSub);
    strncpy(sys->parametersSub[sys->nSubs], sub, len);
    sys->parametersSub[sys->nSubs++][len] = 0;
}

void applySubValues( odeSys *symbolicSys )
{
    int idxParametersSub = 0;
    for ( idxParametersSub = 0; idxParametersSub < symbolicSys->nSubs; idxParametersSub++)
    {
        double value;
        char *name = NULL;
        name = calloc(1, sizeof name);

        getParameterSubValues(symbolicSys->parametersSub[idxParametersSub], name, &value);
        char *castedValue = NULL;
        castedValue = calloc(1, sizeof castedValue);
        sprintf(castedValue, "%d", value);

        int idxOdeEq = 0;
        for ( idxOdeEq = 0; idxOdeEq < symbolicSys->nEqs; idxOdeEq++ )
            replaceSubstring(&symbolicSys->odeEqs[idxOdeEq], name, castedValue);
    };
};

void replaceSubstring( char *fullStr, char *origStr, char *replacementString )
{
    printf("String before sub: %s\n", fullStr);
    
    const int origStrLength = strlen(origStr);
    const int replacementStringLength = strlen(replacementString);

    int idxCharStrOld, nOccurences = 0;
    for ( idxCharStrOld = 0; fullStr[idxCharStrOld] != '\0'; idxCharStrOld++ )
    {
        if ( strstr( &fullStr[idxCharStrOld], origStr ) == &fullStr[idxCharStrOld] )
        {
            nOccurences++;

            /* Jumping to index after the old string */
            idxCharStrOld += origStrLength - 1;
        }
    }

    if (nOccurences != 0)
        {
        char *fullStrNew = NULL;
        fullStrNew = (char*) malloc( idxCharStrOld + nOccurences * (replacementStringLength - origStrLength) + 1 );

        int idxCharStrNew = 0;
        while ( *fullStr )
        {
            if ( strstr( fullStr, origStr ) == fullStr )
            {
                strcpy( &fullStrNew[idxCharStrNew], replacementString );
                
                /* Advancing in the new string */
                idxCharStrNew += replacementStringLength;

                /* Advancing in original string */
                fullStr += origStrLength;
            }
            else
                fullStrNew[idxCharStrNew++] = *fullStr++;
        }
        fullStrNew[idxCharStrNew] = '\0';

        fullStr = malloc(strlen(fullStrNew)+1);
        memcpy(fullStr, fullStrNew, strlen(fullStrNew)+1);
        free(fullStrNew);
    }

    printf("String before sub: %s\n", fullStr);
};