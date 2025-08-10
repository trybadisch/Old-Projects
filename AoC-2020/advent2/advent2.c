#include <stdio.h>

#define  MAX  1000

int check(int, int, char, char *);
int check2(int, int, char, char *);

int sum, valid, validxor;

int main(){
     int min, max, sum, i, j;
     char chara, c;
     char *pwd;
     valid = validxor = sum = 0;

     for (i = 0; i < MAX; i++){
          scanf("%d-%d %c: %s", &min, &max, &chara, pwd);

          check2(min, max, chara, pwd);
          check(min, max, chara, pwd);
     }
     printf("[!] Valid Pwds: %d\n", valid);
     printf("[!] Valid XOR Pwds: %d\n", validxor);
}

int check(int min, int max, char chara, char *pwd){
     int count, i;
     count = 0;
     for (i = 0; pwd[i] != '\0'; i++)
          if (pwd[i] == chara)
               count++;
     printf("%d %d\n", i, count);
     if (count >= min && count <= max)
          valid++;
}

int check2(int min, int max, char chara, char *pwd){
     int i, xor;
     xor = 0;
     for (i = 0; pwd[i] != '\0'; i++)
          if ((pwd[min-1] == chara && pwd[max-1] != chara) || (pwd[max-1] == chara && pwd[min-1] != chara))
               xor = 1;
          (xor == 1) ? validxor++ : 0 ;
     printf("%d[%c]:%d[%c]:%c:%s\n", min, pwd[min-1], max, pwd[max-1], chara, pwd);
     printf("XOR = %d / XOR++ = %d\n", xor, validxor);
}
