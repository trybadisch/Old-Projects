#include <stdio.h>

#define  MAX  1000

void read();
void groupSum();
void reset();
void lineCheck();

int i, j, sum, group[MAX], check[26], total[26], group_total, group_sum;
char c, cust[26];

int main(){
     j = sum = group_total = group_sum = 0; group[j] = 0;

     for (i=0; i < 26; i++)
          check[i] = 0;            // check[] = 0

     for (i=0; i < 26; i++)
          cust[i] = ('a'+i);       // cust[] = a-z

     for ( ; (c = getchar()) && c != EOF; ){
          if (c == '\n')
               lineCheck();
               if ((c = getchar()) == '\n'){
                    groupSum();
                    reset();
                    continue;
               }
               else
                    ;
          read();
     }
     printf("\n[!] Total %d\n", sum);
     printf("\n[!] Same in Group %d\n", group_sum);
}
void read(){
     c -= 'a';
     check[c] = 1;
     printf("%d ", c);
}
void groupSum(){
     printf("\n");
     for(i=0; i < 26; i++){
          printf("%d ", check[i]);
          (check[i] == 1) ? group[j]++ : 0;
     }
     for(i=0; i < 26; i++){
          total[i] ? group_total++ : 0;
     }
     group_sum += group_total;
     sum += group[j];
     printf("\ngroup = %d", group[j]);
     printf("\nsame in group = %d, same in total = %d", group_total, group_sum);
}
void reset(){
     printf("\n");
     for (i=0; i < 26; i++)
          check[i] = 0;
     j++;
     group[j] = 0; group_total = 0;
}
void lineCheck(){
     check[c-'a'] ? total[c-'a'] = 1 : 0;
}
