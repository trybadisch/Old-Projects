#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  MAX  643

int main(){
     int i, value, accum;
     char instruct[10], sign;
     char *string[MAX+1];
     int check[MAX+1];

     for (i=0; i<MAX; i++)
          string[i] = malloc(15 * sizeof(char));

     for (i=0; i<MAX; i++)
          check[i]=0;

     for (i=0; i<MAX; i++){
          scanf("%[^'\n']s", string[i]);
          getchar();
     }

     i=0;
     while (1){
          if (check[i] == 1){
               printf("[!] Found = %d / Accumulator = %d\n", i, accum);
               break;
          }
          check[i]=1;
          sscanf(string[i], "%s %d", instruct, &value);
          printf("%s %d\n", instruct, value);
          if (strcmp(instruct, "acc") == 0){
               accum += value;
               i++;
          }
          if (strcmp(instruct, "nop") == 0){
               i++;
          }
          if (strcmp(instruct, "jmp") == 0){
               i += value;
          }
     }
}
