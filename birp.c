/*
 * BIRP: Binary decision diagram Image RePresentation
 */

#include "image.h"
#include "bdd.h"
#include "const.h"
#include "debug.h"

int pgm_to_birp(FILE *in, FILE *out) {
    // TO BE IMPLEMENTED
    return -1;
}

int birp_to_pgm(FILE *in, FILE *out) {
    int a;
    int b;
    BDD_NODE *test = img_read_birp(in,&a,&b);
    bdd_to_raster(test,a,b,raster_data);
    img_write_pgm(raster_data,a,b,out);
    return 0;
}

int birp_to_birp(FILE *in, FILE *out) {
    return -1;
}

int pgm_to_ascii(FILE *in, FILE *out) {
    int height;
    int width;
    int index;
    img_read_pgm(in,&width,&height,raster_data,RASTER_SIZE_MAX);
        for (int i = 0; i < height ; i++){
         index = i * width;
        for (int j = 0; j < width; j++){
           if(*(raster_data + (j+ index)) == 0 ){
                fputc(' ',stdout);

           }
            if (*(raster_data + (j+ index)) > 63 && (*(raster_data + (j+ index)))< 128){
                fputc('.',stdout);

            }
            if (*(raster_data + (j+ index)) > 127 && (*(raster_data + (j+ index))) < 192){
                fputc('*',stdout);

           }
             if (*(raster_data + (j+ index)) > 191 && (*(raster_data + (j+ index))) < 256){
               fputc('@',stdout);

           }

       }
                fputc('\n',stdout);

   }
return 0;
}

int birp_to_ascii(FILE *in, FILE *out) {
    int a;
    int b;
    int index;
    BDD_NODE *test = img_read_birp(in,&a,&b);
    bdd_to_raster(test,a,b,raster_data);
     for (int i = 0; i < a ; i++){
         index = i * b;
        for (int j = 0; j < b; j++){
           if(*(raster_data + (j+ index)) == 0 ){
                fputc(' ',stdout);

           }
            if (*(raster_data + (j+ index)) > 63 && (*(raster_data + (j+ index)))< 128){
                fputc('.',stdout);

            }
            if (*(raster_data + (j+ index)) > 127 && (*(raster_data + (j+ index))) < 192){
                fputc('*',stdout);

           }
             if (*(raster_data + (j+ index)) > 191 && (*(raster_data + (j+ index))) < 256){
               fputc('@',stdout);

           }
       }
        fputc('\n',stdout);

   }
return 0;
}




/**
 * @brief Validates command line arguments passed to the program.
 * @details This function will validate all the arguments passed to the
 * program, returning 0 if validation succeeds and -1 if validation fails.
 * Upon successful return, the various options that were specifed will be
 * encoded in the global variable 'global_options', where it will be
 * accessible elsewhere int the program.  For details of the required
 * encoding, see the assignment handout.
 *
 * @param argc The number of arguments passed to the program from the CLI.
 * @param argv The argument strings passed to the program from the CLI.
 * @return 0 if validation succeeds and -1 if validation fails.
 * @modifies global variable "global_options" to contain an encoded representation
 * of the selected program options.
 */
 int compare_info(char *first, char *second);
 int string_to_int(char *str);
int validargs(int argc, char **argv) {
 char** p;
    p = &*argv;
    char *pgm = "pgm";
    char *h = "-h";
    char *i = "-i";
    char *birp = "birp";
    char *o = "-o";
    char *ascii = "ascii";
    int extracheck = 0;
    int birpselected =0;
    char *n = "-n";
    char *r = "-r";
    char *t = "-t";
    char *z = "-z";
    char *z1 = "-Z";
    int icomplete =0;
    int ocomplete= 0;
    int asciicheck = 0;
    if(argc == 1){
        return -1;
    }

    if(compare_info(*(p+1),h)){
       global_options = HELP_OPTION;
        //printf("%x\n",global_options);
        return -1;
    }

    if(compare_info(*(p+1),i)){
       if(compare_info(*(p+2),pgm)){
            icomplete = 1;
       }
       if(compare_info(*(p+2),birp)){
           icomplete = 1;
           birpselected = 1;
       }
       if ((*(p+3) == 0 || compare_info(*(p+3),"NULL")) && icomplete == 1 ){
           if (birpselected == 1){
            //printf("\n1 complete");
            global_options = 0;
            global_options = global_options | 2;
            global_options = global_options | 32;
           // printf("%x\n",global_options);
            return 0;
           }
           else{
                       // printf("\n2 complete");

            global_options = 0;
            global_options = global_options | 1;
            global_options = global_options | 32;
          //  printf("%x\n",global_options);
            return 0;
           }
       }
       if(icomplete == 0){
                //    printf("\n3 complete");

        global_options = 0;
        return -1;
       }
       if((compare_info(*(p+3),o) && icomplete == 1)){ // in the case u put -i birip -o ...
           if(compare_info(*(p+4),pgm)){
                if(birpselected == 0){
                                //printf("\n4 complete");

                      global_options = 0;
                        global_options = global_options | 1;
                     global_options = global_options | 16;
                  //  printf("%x\n",global_options);
                }
                else{
                              //  printf("\n5 complete");

                     global_options = 0;
                        global_options = global_options | 2;
                        global_options = global_options |16;
                      //  printf("%x\n",global_options);
                        return 0;
                }
               birpselected = 0;

            }
            if(compare_info(*(p+4),birp)){
                if(birpselected == 0){
                               // printf("\n6 complete");

                    global_options = 0;
                    global_options = global_options | 1;
                    global_options = global_options | 32;
                  //  printf("%x\n",global_options);
                    return 0;
                }
            birpselected = 1;
            extracheck = 1;
           // printf("\n7 complete");

            global_options = 0;
            global_options = global_options | 2;
            global_options = global_options | 32;
           // printf("%x\n",global_options);
            return 0;
        }
            if(compare_info(*(p+4),ascii)){
                if(birpselected == 0){
                           //     printf("\n8 complete");

                    global_options = 0;
                    global_options = global_options | 1;
                    global_options = global_options | 16;
                    global_options = global_options | 32;
                    return 0;
                   // printf("set global options for pgm ascii");
                      }
                else{
                            //    printf("\n9 complete");

                     global_options = 0;
                    global_options = global_options | 2;
                    global_options = global_options | 16;
                    global_options = global_options | 32;
                  // printf("%x\n",global_options);
                   return 0;
                }
              birpselected = 0;
          }
            if(!*(p+5) == 0 && birpselected == 0){
                         //   printf("\n10 complete");

                global_options = 0;
                return -1; //failed
            }
            if( birpselected == 0){
                        //    printf("\n11 complete");

                global_options = 0;
                return  -1;
            }


       }

    }

    if(compare_info(*(p+1),o)){
        if(compare_info(*(p+2),pgm)){
            ocomplete = 1;
       }
        if(compare_info(*(p+2),birp)){
            birpselected = 1;
            ocomplete =1;
        }
         if(compare_info(*(p+2),ascii)){
             ocomplete = 1;
             asciicheck = 1;
         }
         if ((*(p+3) == 0 || compare_info(*(p+3),"NULL")) && ocomplete == 1 ){
            if (birpselected == 1){
                        //    printf("\n12 complete");

            global_options = 0;
            global_options = global_options | 2;
            global_options = global_options | 32;
            //printf("%x\n",global_options);
            return 0;
           }
           if(asciicheck == 1){
                     //   printf("\n13 complete");

              global_options = 0;
            global_options = global_options | 2;
            global_options = global_options | 16;
            global_options = global_options | 32;
            //printf("%x\n",global_options);
            return 0;
           }
           else{
                     //   printf("\n14 complete");

             global_options = 0;
            global_options = global_options | 2;
            global_options = global_options |16;
            //printf("%x\n",global_options);
            return 0;
           }
       }
       if (ocomplete == 0){
                //    printf("\n15 complete");

        global_options = 0;
        return -1;
       }
         if((compare_info(*(p+3),i) && ocomplete == 1)){ // in the case u put -i birip -o ...
           if(compare_info(*(p+4),pgm)){
               if (birpselected ==1){
                      //      printf("\n16 complete");

                 global_options = 0;
                global_options = global_options | 1;
                global_options = global_options | 32;
                //printf("%x\n",global_options);
               }
               if(asciicheck ==1){
                      //      printf("\n17 complete");

                global_options = 0;
                global_options = global_options | 1;
                global_options = global_options | 16;
                global_options = global_options | 32;
                //printf("%x\n",global_options);

               }
               else{
                       //     printf("\n18 complete");

                global_options = 0;
                global_options = global_options | 1;
                global_options = global_options | 16;
                //printf("%x\n",global_options);
               }

               birpselected = 0;
            }
            if(compare_info(*(p+4),birp)){
            if (birpselected == 1){
             int birp_birp = 0;
             birp_birp = birp_birp | 2;
            birp_birp = birp_birp | 32;
           // printf("%x\n",birp_birp);
        }
            if(asciicheck == 1){
                          //  printf("\n19 complete");

                global_options = 0;
                global_options = global_options | 2;
                global_options = global_options | 16;
                global_options = global_options | 32;
              //  printf("%x\n",global_options);
            }
            else{
                          //  printf("\n20 complete");

                 global_options = 0;
                 global_options = global_options | 2;
                global_options = global_options |16;
               // printf("%x\n",global_options);

            }
            birpselected = 1;
            extracheck = 1;
        }
            if(!*(p+5) == 0 && birpselected == 0){
                          //  printf("\n21 complete");

                global_options = 0;
                return -1; //failed
            }
            if(*(p+5) == 0 && birpselected == 0){
                           // printf("\n22 complete");

                global_options = 0;
                return  0;
            }

       }

    }


    if(compare_info(*(p+1),n)){
         if(!compare_info(*(p+2),"NULL")) {
             return -1;
         } // failed
         else{
                    //    printf("\n23 complete");

            global_options = 0;
            global_options = global_options | 2;
            global_options = global_options | 32;
            global_options = global_options | 256;
           // printf("%x\n",global_options);
            return 0;
         }
    }

    if(compare_info(*(p+1),r)){
         if(!compare_info(*(p+2),"NULL") ){
             return -1;

         }
         else{
                    //    printf("\n24 complete");

            global_options = 0;
            global_options = global_options | 2;
            global_options = global_options | 32;
            global_options = global_options | 1024;
            //printf("%x\n",global_options);
            return 0;
         } // failed
    }

    if(compare_info(*(p+1),t)){
        int int_from_string = string_to_int(*(p+2));
        if (int_from_string == -1){
            return -1;
        }
        if (int_from_string < 0 || int_from_string > 255 ){
            return -1;
        }
        else{
                      //  printf("\n25 complete");

              global_options = 0;
            global_options = global_options | 2;
            global_options = global_options | 32;
            global_options = global_options | 512;
            global_options |= int_from_string << 16;
            //printf("%x\n",global_options);
            return 0;
        }

    }

    if(compare_info(*(p+1),z1)){
        int int_from_string = string_to_int(*(p+2));
        if (int_from_string == -1){
            return -1;
        }
        if (int_from_string < 0 || int_from_string > 16 ){
            return -1;
        }
        else{
                       // printf("\n26 complete");

            global_options = 0;
            global_options = global_options | 2;
            global_options = global_options | 32;
            global_options = global_options | 256;
            global_options = global_options | 512;
            global_options |= int_from_string << 16;
            //printf("%x\n",global_options);
            return 0;
        }
    }

    if(compare_info(*(p+1),z)){
        int int_from_string = string_to_int(*(p+2));
        if (int_from_string == -1){
            return -1;
        }
        if (int_from_string < 0 || int_from_string > 16 ){
            return -1;
        }
        else{
                       // printf("\n27 complete");

            global_options = 0;
            int flipped = -int_from_string;
            global_options = global_options | 2;
             global_options = global_options | 32;
            global_options = global_options | 256;
        global_options = global_options | 512;
            global_options |= flipped << 16;
            int mask = 0xFF000000;
             global_options ^= mask;
           // printf("%x\n",global_options);
            return 0;
        }
    }



    if( extracheck == 1 && birpselected == 1 ){
         if(compare_info(*(p+5),n)){
         if(!compare_info(*(p+6),"NULL")) {
                      //  printf("\n28 complete");

            global_options = 0;
             return -1;
         }
         else{
                      //  printf("\n29 complete");

            global_options = 0;
            global_options = global_options | 2;
            global_options = global_options | 32;
            global_options = global_options | 256;
            //printf("%x\n",global_options);
            return 0;
         }} // failed
         if(compare_info(*(p+5),r)){
         if(!compare_info(*(p+6),"NULL") ){
                     //   printf("\n30 complete");

            global_options = 0;
             return -1;
            } // failed
        else{
             int birp_birp_r = 0;
            birp_birp_r = birp_birp_r | 2;
            birp_birp_r = birp_birp_r | 32;
            birp_birp_r = birp_birp_r | 1024;
           // printf("%x\n",birp_birp_r);
            return 0;
        }
    }
    if(compare_info(*(p+5),t)){

        int int_from_string = string_to_int(*(p+6));
        if (int_from_string == -1){
          //  printf("%s\n","failed");
            return -1;
        }
        if (int_from_string < 0 || int_from_string > 255 ){
           // printf("%s\n","failed");
            return -1;
        }
        else{
                      //  printf("\n31 complete");

            global_options = 0;
           // printf("%d\n",int_from_string);
            global_options = global_options | 2;
            global_options = global_options | 32;
         global_options = global_options | 512;
            global_options |= int_from_string << 16;

         //   printf("%x\n",global_options);
            return 0;;
        }
    }
    if(compare_info(*(p+5),z1)){
         int int_from_string = string_to_int(*(p+6));
        if (int_from_string == -1){
            return -1;
        }
        if (int_from_string < 0 || int_from_string > 16 ){

            return -1;
        }
        else{
           // printf("\n32 complete");

            global_options = 0;
            global_options = global_options | 2;
            global_options = global_options | 32;
            global_options = global_options | 256;
            global_options = global_options | 512;
            global_options |= int_from_string << 16;
           // printf("%x\n",global_options);
            return 0;
        }
    }
     if(compare_info(*(p+5),z)){
        int int_from_string = string_to_int(*(p+6));
        if (int_from_string == -1){

            return -1;
        }
        if (int_from_string < 0 || int_from_string > 16 ){
            return -1;
        }
        else{
                    //    printf("\n33 complete");

              global_options = 0;
            int flipped = -int_from_string;
            global_options = global_options | 2;
            global_options = global_options | 32;
            global_options = global_options | 256;
            global_options = global_options | 512;
            global_options |= flipped << 16;
            int mask = 0xFF000000;
            global_options ^= mask;
            //printf("%x\n",global_options);
            return 0;
        }
    }


}
return -1;
}


int compare_info(char *first, char *second)
{

    while ((*first != '\0') && (*second != '\0') && (*first == *second))
    {
        first++;
        second++;
    }
    if (*first == *second){
        return 1;
    }
    else{
        return 0;
    }return -1;

}

int string_to_int(char *str)
{
 int converted = 0;
 for (int i = 0; (*(str + i)) != '\0'; i++) {
     if( (*(str + i)) > '9' || (*(str + i)) < '0'){
     return -1;
     }
     converted = converted*10 + (*(str + i)) - '0';
 }
 return converted;
}
