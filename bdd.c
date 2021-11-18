#include <stdlib.h>
#include <stdio.h>

#include "bdd.h"
#include "debug.h"

/*
 * Macros that take a pointer to a BDD node and obtain pointers to its left
 * and right child nodes, taking into account the fact that a node N at level l
 * also implicitly represents nodes at levels l' > l whose left and right children
 * are equal (to N).
 *
 * You might find it useful to define macros to do other commonly occurring things;
 * such as converting between BDD node pointers and indices in the BDD node table.
 */
#define LEFT(np, l) ((l) > (np)->level ? (np) : bdd_nodes + (np)->left)
#define RIGHT(np, l) ((l) > (np)->level ? (np) : bdd_nodes + (np)->right)

/**
 * Look up, in the node table, a BDD node having the specified level and children,
 * inserting a new node if a matching node does not already exist.
 * The returned value is the index of the existing node or of the newly inserted node.
 *
 * The function aborts if the arguments passed are out-of-bounds.
 */
static int keygenerator (int *key);

int bdd_lookup(int level, int left, int right) {
    if(left == right){
        return left;
    }
    BDD_NODE test = {level,left,right};
    int key = test.level + test.right + test.left;
    int new = keygenerator(&key);
    if(test.left != test.right){
        if(*(bdd_hash_map + new) != NULL){
        if((*(bdd_hash_map + new))->right == test.right && (*(bdd_hash_map + new))->left == test.left && (*(bdd_hash_map + new))->level == test.level){
            for(int i =256; i < BDD_NODES_MAX ; i++){
                if((bdd_nodes + i)->left == test.left && (bdd_nodes + i)->right == test.right && (bdd_nodes +i)-> level == test.level){
                    return i; //same node
                }
            }
        }
        else{
            while(*(bdd_hash_map + new) != NULL)
            {
                new++;
            }

      for(int i =256; i<BDD_NODES_MAX;i++){
        if((bdd_nodes+i)->level == 0){
      *(bdd_nodes +  i) = test;
      *(bdd_hash_map+ new) = bdd_nodes + i;
      int savedkeep = i;
        return(savedkeep);
    }
    }


        }
    }

     else{
         for (int i = 256; i < BDD_NODES_MAX; i++){
            if((bdd_nodes + i)->level == 0){
      *(bdd_nodes +i) = test;
      *(bdd_hash_map+ new) = bdd_nodes + i;
      int savedkeep = i;
        return(savedkeep);
    }}
  }

}
return -1;
}



int keygenerator (int *key){
        return *key % BDD_HASH_SIZE;
    }

int bdd_min_level(int w, int h){
    int biggest = 0;
    if (w > h){
        biggest = w;
    }
    else{
        biggest = h;
    }

   int counter = 1;
   int result = 0;
   while (counter < biggest){
    counter = counter * 2;
    result = result + 1;
   }
   return result;
}

int calcpower(int power, int to){
    int result =1;
    for(int i = 0; i<to;i++){
        result *=  power;
    }

    return result;
}
BDD_NODE *bdd_from_raster(int w, int h, unsigned char *raster) {
return NULL;
}


void bdd_to_raster(BDD_NODE *node, int w, int h, unsigned char *raster) {
    for(int i = 0; i < h ; i++){
        for (int j =0; j < w ; j++){
            //printf("\nTHIS IS THE NODE LEFT VALUE BEFORE IT GOES IN: %d", node->left);
            //printf("\nTHIS IS THE NODE RIGHT VALUE BEFORE IT GOES IN: %d", node->right);
            int result = bdd_apply(node,i,j);
            //printf("%d, ",result);
            (*(raster + (i*w + j)) = result);
        }
        //printf("\n");
    }
    }

int serializerec(int *pointer,int child,FILE*out);
int bdd_serialize(BDD_NODE *node, FILE *out) {

     return -1;
}





int serializerec(int *pointer,int child,FILE*out){
  int testing;
    if(child < 256){ // base case if leaf
        if(*(bdd_index_map + child) == 0){// if at specific child mapping is not there
            (*(bdd_index_map  + child)) = *pointer;
            fputc(64,out); // print @
            fputc(child,out);
            *pointer =- *pointer + 1;
            }
          else{
            return *(bdd_index_map + child);
          }// increment pointer once done
    }
    else{
    int leftvalue = (bdd_nodes+child)-> left;
    int continueleft = serializerec(pointer,leftvalue,out);
    int rightvalue = (bdd_nodes+child)-> right;
    int continueright = serializerec(pointer,rightvalue,out);
     testing = *pointer;
    *(bdd_index_map + child) = testing;
    *pointer = *pointer +1;
    fwrite(&(bdd_nodes + child)->level,4,4,out);
    fwrite(&continueleft,4,4,out);
    fwrite(&continueright,4,4,out);
  }
      return (testing);

}

BDD_NODE *bdd_deserialize(FILE *in) {
    int reader;
    int level;
    int leftserial;
    int rightserial;
    int pixelvalue;
    int  serialcounter = 1;
    int index;

    // CREATE for loop to clear out inddex map bddindexmap + index = 0;
    while(( reader=  fgetc(in)) != EOF){
       // printf("this is the serial counter %d\n",serialcounter);
        if(reader == 64){ //leaf
            if( (pixelvalue = fgetc(in)) > 255){
               //printf("invalid pixel");
                return NULL;
            }

            else{
                //printf("Found a pixel %d\n",pixelvalue);
            //printf("This is the counter value for a pixel %d\n",serialcounter);
                *(bdd_index_map + serialcounter) = pixelvalue;
               // int *test6 = (bdd_index_map + serialcounter);
                //printf("test6 %d\n",*test6);
                serialcounter++;



            }
        }
        else if( reader  < 97){
            level = reader - 64;
            //printf("\nFound a level, %d",level);
            fread(&leftserial,4,1,in);
            int leftvalue = *(bdd_index_map + leftserial);
           //printf("THIS IS THE LS,%d\n",leftserial);
            fread(&rightserial,4,1,in);
            int rightvalue = *(bdd_index_map + rightserial);

           // printf("\nFound a rightserial");;
            //printf("THIS IS THE rs,%d\n",rightserial);

            index =bdd_lookup(level,leftvalue,rightvalue);
            //printf("\nTHIS IS THE INDEX,%d\n%d\n%d\n",index,leftvalue,rightvalue);
           // printf("\nTHIS IS just THE INDEX: ,%d\n",index);
           // printf("\nBDD LOOKUP COMPLETED");
            *(bdd_index_map + serialcounter) = index;
            //printf("this is test 7 after the lookup, %d",*test7);
             //*test7 = index;
             //printf("\nthis is test 7 after setting equal the index, %d",);
            // printf("\nbdd map + serial, %d",(*(bdd_index_map+serialcounter)));
              serialcounter++;

                //return node if last
            }


    }
            index = *(bdd_index_map + serialcounter -1);
                //printf("RETURNED");
                return bdd_nodes + index;

}

int getbit(int number, int position); //(3,6)
int getrow(BDD_NODE *node, int r, int c);
int evenorodd(int number);
int getcolumn(BDD_NODE *node,int r, int c);
unsigned char bdd_apply(BDD_NODE *node, int r, int c) {
    //printf("\nthis is the r and c %d,%d",r,c);
   BDD_NODE *currentnode = node;
   int result;
  // printf("\nTHIS IS R AND C %d%d",r,c);
   while(currentnode->level != 0 ){
   int level = currentnode->level;
   // int left = currentnode ->left;
   //int right = currentnode->right;
    //printf("\n CURRENT NODE LEVEL VALUE AT THE BEGINNING %d", level);
    //printf("\n CURRENT NODE LEFT VALUE AT THE BEGINNING %d", left);
//printf("\n CURRENT NODE RIGHT VALUE AT THE BEGINNING %d", right);
    if(evenorodd(level)){
     // printf("\n THIS IS THE level in first TO SEE %d",level);
      int numtosee = level - 2;
       numtosee = numtosee /2;
       numtosee++;
     // printf("\n THIS IS THE NUM TO SEE %d",numtosee);
        result = getbit(r,numtosee);
      // printf("\n CURRENT RESULT LEVEL VALUE AT THE ROW %d", result);


    }
    else if (evenorodd(currentnode->level) == 0){
      int numtosee = level-1;
       numtosee = numtosee /2;
       numtosee++;
    //  printf("\n CURRENT RESULT NUMTOSEE VALUE AT THE COLUMN %d", numtosee);
        result = getbit(c,numtosee);
      //  printf("\n CURRENT RESULT LEVEL VALUE AT THE COLUMN %d", result);

        if(numtosee == 1 && result == 0){
          return currentnode->left;
        }
         if(numtosee == 1 && result == 1){
          return currentnode->right;
        }

    }
    //printf("\n this is the result : %d", result);
    if(result == 0){
      if(currentnode->left < 256){
        return currentnode->left;
      }
    //printf("\n EXECUTING IF RESULT == 0");
    BDD_NODE *leftchild = LEFT(currentnode,level);
    currentnode = leftchild;
    //printf("\n THIS IS THE LEFT CHILD: %d",currentnode->level);
    }
    else if(result ==1){
      if(currentnode->right < 256){
        return currentnode->right;
      }
    //printf("\n EXECUTING IF RESULT == 1");
    BDD_NODE *rightchild = RIGHT(currentnode,level);
    currentnode = rightchild;

   }



  //printf("\n CURRENT NODE LEVEL VALUE AT THE END %d", level);

     }
if(evenorodd(currentnode->level) == 1){
  int numtosee = currentnode->level - 2;
       numtosee = numtosee /2;
       numtosee++;
       result = getbit(r,numtosee);
}
else if(evenorodd(currentnode->level) == 0){
  int numtosee = currentnode->level - 1;
       numtosee = numtosee /2;
       numtosee++;
       result = getbit(c,numtosee);
}

if(result == 0){
  return currentnode->left;
}
else{
  return currentnode->right;

}
}




int getbit(int number, int position){
    return  ((number >> (position-1)) & 1);
}

 int evenorodd(int number){
     if(number % 2 == 0)
        return 1;
    else
        return 0;
}



BDD_NODE *bdd_map(BDD_NODE *node, unsigned char (*func)(unsigned char)) {
    // TO BE IMPLEMENTED
    return NULL;
}

BDD_NODE *bdd_rotate(BDD_NODE *node, int level) {
    // TO BE IMPLEMENTED
    return NULL;
}

BDD_NODE *bdd_zoom(BDD_NODE *node, int level, int factor) {
    // TO BE IMPLEMENTED
    return NULL;
}
