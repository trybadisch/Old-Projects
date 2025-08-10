#include <stdio.h>

#define  MAX  875
#define  mid(U,D)  ((U-D)/2)

int main(){
	int c, i, j, IDmax, ID[MAX];
		float row, column, rD, rU, cD, cU;
	rD = cD = 0; rU = 127; cU = 7;
	j = IDmax = 0;

	for (i=0; (c = getchar()) != EOF; i++){
			switch(c){
			case 'F': rU = row = rU-mid(rU,rD)-0.5;
				printf("F-%.0f,%.0f ", rD,rU); break;

			case 'B': rD = row = mid(rU,rD)+rD+0.5;
				printf("B-%.0f,%.0f ", rD,rU); break;

			case 'L': cU = column = cU-mid(cU,cD)-0.5;
				printf("L-%.0f,%.0f ", cD,cU); break;

			case 'R': cD = column = mid(cU,cD)+cD+0.5;
				printf("R-%.0f,%.0f ", cD,cU); break;

			case '\n':
				printf("\nrow= %.0f, column= %.0f", row, column);
				ID[j] = ((int)row*8)+(int)column; rD = 0; rU = 127; cD = 0; cU = 7;
				printf("\nID = %d\n", ID[j]);
				j++;
				break;
			}
	}
	for (j=0; j < MAX; j++)
		ID[j] > IDmax ? IDmax = ID[j] : 0 ;

	printf("\n[!] Highest ID = %d\n\n", IDmax);

	for (j=0; j < MAX; j++)
		printf("%d\n", ID[j]);
}
