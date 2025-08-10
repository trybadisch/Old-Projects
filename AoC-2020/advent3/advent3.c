#include <stdio.h>

#define  MAXLN  322
#define  MAXCH  100
#define  MAGIC  84.0*228.0*89.0*100.0*40.0

int check(char *, int);
int check2(char *, int);

int slope(char *, int);
int drift;
int trees;

int main(){
     int i;
     char c, *slope[MAXLN], *garbage[MAXCH];

     scanf("%s", garbage);

     i = 0;
     while (i < MAXLN){
          // scanf("%s", garbage);
          // printf("%s\n", garbage);
          scanf("%s", slope);
          printf("%s\n", slope);

          check(&slope, i);
          i++;
     }
     printf("%.0f\n", MAGIC);
}

int check(char *slope, int i){
     drift +=3;
     if (drift > 30)
          drift -= 31;
     if (slope[drift] == '#')
          trees++;
     printf("%d -> %c\t%d\n", drift, slope[drift], trees );
}
