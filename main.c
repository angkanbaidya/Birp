#include <stdio.h>
#include <stdlib.h>

#include "const.h"
#include "debug.h"

#ifdef _STRING_H
#error "Do not #include <string.h>. You will get a ZERO."
#endif

#ifdef _STRINGS_H
#error "Do not #include <strings.h>. You will get a ZERO."
#endif

#ifdef _CTYPE_H
#error "Do not #include <ctype.h>. You will get a ZERO."
#endif

int main(int argc, char **argv)
{
    int a;
    int b;
    if(validargs(argc, argv) == -1)
        USAGE(*argv, EXIT_FAILURE);
    if(validargs(argc,argv) == 0){
        if(global_options & HELP_OPTION){
        USAGE(*argv, EXIT_SUCCESS);
    }
    if(global_options == 49){
        pgm_to_ascii(stdin,stdout);

}
   if (global_options == 33){
        pgm_to_birp(stdin,stdout);
    }

    if(global_options == 18){
        birp_to_pgm(stdin,stdout);
    }
    if(global_options == 34){
        birp_to_birp(stdin,stdout);
    }
    if(global_options == 50){
        birp_to_ascii(stdin,stdout);
   }

        return EXIT_SUCCESS;
    }
    if(global_options & HELP_OPTION){
        USAGE(*argv, EXIT_SUCCESS);
    }
    // TO BE IMPLEMENTED


    return EXIT_FAILURE;

}

/*
 * Just a reminder: All non-main functions should
 * be in another file not named main.c
 */
