/*
 * dkset.c
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dkset.h"

/*
 * Don't forget that if this dkset is a set, then it will have an array
 * of dkset's terminated by a NULL.
 */
dkset* parse_dkset(char* s, int index)
{
    printf("parse_dkset index:%d s:%s\n", index, s);
    dkset *result = malloc(sizeof(dkset));
    
    char *thisvalue = calloc(255, sizeof(char));
    int len = strlen(s);
    //int resultels_index = 0;
    int thisvalue_index = 0;
    index -= 1;
    
    while (index++ < len) {
        char c = *(s+index);
        printf("%d %c %s\n", index, c, thisvalue);
        if (c == ' ') {
            continue;
        } else if(c == '{') {
            result->is_set = true;
            result->els = parse_dkset(s, ++index);
            int closerstofind = 1;
            while (closerstofind > 0) {
                index++;
                c = *(s+index);
                if (c == '{') {
                    closerstofind++;
                } else if(c== '}') {
                    closerstofind--;
                }
                index++;
            }
        } else if(c == '}') {
            return result;
        } else if(c == ','){
            result->value = thisvalue;
            return result;
        } else {
            printf("else-pre:|%s|\n", thisvalue);
            *(thisvalue + thisvalue_index) = c;
            thisvalue_index++;
            printf("else-post:|%s|\n", thisvalue);
        }
    }
    return result;
}

char* dkset_tostr(dkset* d)
{
    if (d->is_set) {
        char *result = calloc(2048, sizeof(char));
        *result = '{';
        int i = 0;
        int len = d->size;

        while (1) {
            dkset el = *(d->els + i);
            char *eltostr = dkset_tostr(&el);
            strcat(result, eltostr);
            free(eltostr);

            i++;
            if (i >= len) {
                break;
            }
            strcat(result, ", ");
        }
        *(result + strlen(result)) = '}';
        return result;
    }
    char *copyofvalue = calloc(strlen(d->value), sizeof(char));
    strcpy(copyofvalue, d->value);
    return copyofvalue;
}

void free_dkset(dkset* d)
{
    if (d->is_set) {
        int i;
        int len = d->size;
        
        for(i = 0; i < len; i++) {
            free_dkset(d->els + i);
        }
    } else {
        free(d->value);
    }
    free(d);
}

/*
 * Where |S| is the cardinality of a set S,
 * and P(S) denotes the powerset of a set S,
 * |P(S)| = 2^(|S|)
 *
 * Of course we can use a bitwise trick for 2^n is:
 * 2^n = 1 << n
 */
int powerset_cardinality_dkset(dkset* d)
{
    return 1 << d->size;
}