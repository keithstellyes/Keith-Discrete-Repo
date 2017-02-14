#include <stdlib.h>
#include <string.h>
#include "dkmatrix.h"

char* dkmatrixbool_tostr(dkmatrix* dkm)
{
    dkmatrix _dkm = *dkm;
    int maxchars_perval = 2;
    /* +1 for each newline. */
    int maxchars_perrow = maxchars_perval * _dkm.colsc + 1;
    /* +1 for null char */
    int maxchars_forresult = maxchars_perrow * _dkm.rowsc + 1;
    char *result = (char*) calloc(maxchars_forresult, sizeof(char));
    
    int rowi, coli;

    for (rowi = 0; rowi < _dkm.rowsc; ++rowi){
        for (coli = 0; coli < _dkm.colsc; ++coli){
            int elsidx = coli*(_dkm.rowsc);
            if (*(_dkm.els+elsidx) != 0) {
                strcat(result, "1 ");
            } else {
                strcat(result, "0 ");
            }
        }
        _dkm.els++;
        strcat(result, "\n");
    }
    return result;
}
