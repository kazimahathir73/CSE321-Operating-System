#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t a;
	char *num[] = {"task4", "10", "97", "21", "30", NULL};
	a = fork();
	if (a == 0){
		execv("./sort", num);
	}
	else {
		wait(NULL);
		execv("./oddeven", num);
	}
	return 0;
}