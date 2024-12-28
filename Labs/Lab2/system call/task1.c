#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>

int main(){
	int f;
	f = open("output.txt", O_WRONLY | O_APPEND | O_CREAT, 0642);

	while(true){
		char s[100]="";
		read(0, s, 100);
		size_t len = strlen(s);
		if (len > 0 && s[len-1] == '\n'){
			s[len-1] = '\0';
		}

		if (strcmp(s, "-1")!=0){
			write(f, s, strlen(s));
			write(f, "\n", 1);
		}
		else{
			break;
		}
	}

	close(f);
	return 0;

}