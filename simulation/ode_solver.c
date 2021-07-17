#include "ode_solver.h"

void printOdeSys( odeSys sysToPrint )
{
    if (sysToPrint.nEqs != 0)
    {
        printf("--------------------\n");
        printf("Printing ODE system:\n");
        for ( int idxOdeEq = 0; idxOdeEq < sysToPrint.nEqs; idxOdeEq++ )
            printf("%s\n", sysToPrint.odeEqs[idxOdeEq]);
        printf("--------------------\n");
    }
    else
        printf("No equations to print!\n");

    if (sysToPrint.nSubs != 0)
    {
        printf("--------------------\n");
        printf("Printing set of substitutions:\n");
        for ( int idxSubEq = 0; idxSubEq < sysToPrint.nSubs; idxSubEq++ )
            printf("%s\n", sysToPrint.parametersSub[idxSubEq]);
        printf("--------------------\n");
    }
   else
        printf("No substitutions to print!\n");
}

void odeNumericalConverter( odeSys symbolicSys, finiteDifferenceMethod method, algSys *numericSys ) 
{
    printf("----------------------------------------------------------------------------------\n");
    printf("Conversion of symbolic ODEs to numerical ones, using a Finite Difference scheme...\n");
    applySubValues(&symbolicSys);

    // TODO: Composing finite difference equation
    // TODO: Substituting finite difference equation
    // TODO: Creating algebraic equations to solve
    printf("----------------------------------------------------------------------------------\n");
};

void getParameterSubValues( char *str, char *name, double *value )
{
    sscanf( str, "%s = %lf", name, value);
};

void setParameterSubValues( odeSys *sys, char *sub )
{
    size_t len = strlen(sub);

    sys->parametersSub[sys->nSubs] = calloc( len + 1, sizeof **sys->parametersSub); // +1 because of 0 value at the end of string
    strncpy(sys->parametersSub[sys->nSubs], sub, len);
    sys->parametersSub[sys->nSubs++][len] = 0;  // Last element of the string
    printf("Added substitution: %s\n\n", sys->odeEqs[sys->nSubs-1]);
}

void numToString( char *castedValue, double *source )
{
    sprintf(castedValue, "%lf", *source);
}

void applySubValues( odeSys *symbolicSys )
{
    for ( int idxParametersSub = 0; idxParametersSub < symbolicSys->nSubs; idxParametersSub++)
    {
        double value;
        char *name = NULL;
        name = calloc(1, sizeof name);

        getParameterSubValues(symbolicSys->parametersSub[idxParametersSub], name, &value);
        char *castedValue = NULL;
        castedValue = calloc(1, sizeof castedValue);
        numToString(castedValue, &value);

        if (symbolicSys->nEqs != 0)
        {
            printf("Substitution of %s ...\n", symbolicSys->parametersSub[idxParametersSub]);
            for ( int idxOdeEq = 0; idxOdeEq < symbolicSys->nEqs; idxOdeEq++ )
            {
                char *eqWithSub = NULL;
                eqWithSub = malloc(sizeof(symbolicSys->odeEqs[idxOdeEq]));
                size_t charDiff = 0;

                replaceSubstring(symbolicSys->odeEqs[idxOdeEq], name, castedValue, eqWithSub, charDiff);
                if(strlen(eqWithSub) != 0)
                {
                    // printf("Substituted eq: %s\n", eqWithSub);

                    char **odeEqsNew = NULL;
                    odeEqsNew = malloc(sizeof(symbolicSys->odeEqs) + 1000);     // TODO: Smart addition of charDiff
                    for (int idxOdeEqLocal = 0; idxOdeEqLocal < symbolicSys->nEqs; idxOdeEqLocal++)
                    {
                        if(idxOdeEqLocal != idxOdeEq)
                        {
                            odeEqsNew[idxOdeEqLocal] = calloc(strlen(symbolicSys->odeEqs[idxOdeEqLocal])+1, sizeof odeEqsNew[idxOdeEqLocal]);
                            strcpy(odeEqsNew[idxOdeEqLocal], symbolicSys->odeEqs[idxOdeEqLocal]);
                            // printf("Eq %d copied\n", idxOdeEqLocal);
                        }
                        else
                        {
                            // printf("Copying eqWithSub...\n");
                            odeEqsNew[idxOdeEqLocal] = calloc(strlen(eqWithSub)+1, sizeof odeEqsNew[idxOdeEqLocal]);
                            strcpy(odeEqsNew[idxOdeEqLocal], eqWithSub);
                            // printf("Eq %d (eqWithSub) copied\n", idxOdeEqLocal);
                        }
                    }
                    for (int i = 0; i < symbolicSys->nEqs; i++)
                    {
                        symbolicSys->odeEqs[i] = malloc(strlen(odeEqsNew[i])+1);
                        memcpy(symbolicSys->odeEqs[i], odeEqsNew[i], strlen(odeEqsNew[i])+1);
                    }
                    free(odeEqsNew);
                }
                // printOdeSys(*symbolicSys);
            }
            printf("Substituted: %s\n\n", symbolicSys->parametersSub[idxParametersSub]);
        }
    };
    printf("End of substitutions...\n\n");
    // printOdeSys(*symbolicSys);
};

void replaceSubstring( char *fullStr, char *origStr, char *replacementString, char *fullStrNew, size_t charDiff )
{   
    const size_t origStrLength = strlen(origStr);
    const size_t replacementStringLength = strlen(replacementString);

    size_t idxCharStrOld, nOccurences = 0;
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
        printf("Equation before substitution: %s\n", fullStr);
        // printf("Substitution: %s = %s\n", origStr, replacementString);

        // char *fullStrNew = NULL;
        // fullStrNew = (char*) malloc( idxCharStrOld + nOccurences * (replacementStringLength - origStrLength) + 1 );
        fullStrNew = realloc(fullStrNew, idxCharStrOld + nOccurences * (replacementStringLength - origStrLength) + 1 );

        size_t idxCharStrNew = 0;
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

        // fullStr = malloc(strlen(fullStrNew)+1);
        // memcpy(fullStr, fullStrNew, strlen(fullStrNew)+1);
        // free(fullStrNew);

        charDiff = sizeof(fullStr) - sizeof(fullStrNew);

        printf("Equation after substitution: %s\n\n", fullStrNew);
    }
};

void setOde( odeSys *sys, char *sub )
{
    size_t len = strlen(sub);

    sys->odeEqs[sys->nEqs] = calloc( len + 1, sizeof **sys->odeEqs); // +1 because of 0 value at the end of string
    strncpy(sys->odeEqs[sys->nEqs], sub, len);
    sys->odeEqs[sys->nEqs++][len] = 0;  // Last element of the string
    printf("Added ODE: %s\n\n", sys->odeEqs[sys->nEqs-1]);
};