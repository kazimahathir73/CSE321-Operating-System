#include <stdio.h>
#include <stdlib.h>

int main(int argc, int *argv[]){
	for (int i = 1; i < argc; i++){
		if (atoi(argv[i])%2!=0){

			printf("%d is ODD\n", atoi(argv[i]));
		}
		else{
			printf("%d is EVEN\n", atoi(argv[i]));
		}
	}
	return 0;
}