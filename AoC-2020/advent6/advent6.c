#include <stdio.h>

#define  MAX  1000

int main(){
     int i, j, sum, group[MAX], check[26];
     char c, cust[26];

     j = sum = 0; group[j] = 0;

     for (i=0; i < 26; i++)
          check[i] = 0;

     for (i=0; i < 26; i++){
          cust[i] = ('a'+i);
          printf("%c ", cust[i]);
     }
     printf("\n\n");

     for ( ; (c = getchar()) && c != EOF; ){
          if (c == '\n')
               if ((c = getchar()) == '\n'){
                    printf("\n");
                    for(i=0; i < 26; i++){
                         printf("%d ", check[i]);
                         (check[i] == 1) ? group[j]++ : 0;
                    }
                    sum += group[j];
                    printf("\ngroup = %d", group[j]);

                    printf("\n");
                    for (i=0; i < 26; i++)
                         check[i] = 0;
                    j++;
                    group[j] = 0;
                    continue;
               }
               else
                    ;

          c -= 'a';
          check[c] = 1;
          printf("%d ", c);
     }
     printf("\n[!] Total %d\n", sum);
}
