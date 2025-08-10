#include <stdio.h>

int main(){
     int i, id;

     for (i=99; i < 974; i++){
          scanf("%d", &id );
          printf("%d, %d\n", i, id);
          if (i != id && ++i == id){
               printf("[!] Not found = %d\n\n", i);
               printf("%d, %d...\n", i, id);
               break;
          }
     }
}
