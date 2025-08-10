#include <stdio.h>

#define  MAX  1000

struct pass {
     int byr;
     int iyr;
     int eyr;
     char *hgt;
     char *hcl;
     char *ecl;
     int pid;
     int cid;
} passport[MAX];

int main(){
     int i;
     char *field[100];
     char efile;

     for (i = 0; i < 1; ){
          while ( (scanf("%s: ", field) != "\n")){
               printf("%s", field);
               if (field == "byr"){
                    scanf("%d", passport[i].byr);
               printf("%d", passport[i].byr);}
               printf("\n");
               else if (field == "iyr")
                    scanf("%d", passport[i].iyr);
               else if (field == "eyr")
                    scanf("%d", passport[i].eyr);
               else if (field == "hgt")
                    scanf("%s", passport[i].hgt);
               else if (field == "hcl")
                    scanf("%s", passport[i].hcl);
               else if (field == "ecl")
                    scanf("%s", passport[i].ecl);
               else if (field == "pid")
                    scanf("%d", passport[i].pid);
               else if (field == "cid")
                    scanf("%d", passport[i].cid);
          }
          i++;
     }
}
