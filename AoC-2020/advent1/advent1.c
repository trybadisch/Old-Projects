#include <stdio.h>

#define  MAX  200

int multiply(int *);
int multiply2(int *);

void main(){
     int input[MAX], i;

     for (i = 0; i < MAX; i++)
          scanf("%d", &input[i]);

     multiply(input);
     multiply2(input);
}

int multiply (int input[]){
     int i, j;

     for (i = 0; i < MAX; i++)
          for (j = 0; j < MAX; j++)
               if (input[i] + input[j] == 2020)
                    goto result;
     result:
          printf("[+] %d + %d\n", input[i], input[j]);
          printf(" [!] %d\n", input[i] * input[j]);
}

int multiply2 (int input[]){
     int i, j, h;

     for (i = 0; i < MAX; i++)
          for (j = 0; j < MAX; j++)
               for (h = 0; h < MAX; h++)
                    if (input[i] + input[j] + input[h] == 2020)
                         goto result;
     result:
          printf("[+2] %d + %d + %d\n", input[i], input[j], input[h]);
          printf(" [!2] %d\n", input[i] * input[j] * input[h]);
}
