#include <stdio.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void *cal_ascii(void *a){
	int ascii = 0;
	char *b = (char *)a;
	for(int i=0; i<strlen(a); i++){
		ascii+=b[i];
	}
	return (void *)ascii;
}

void *compare(void *arr){
	int *input_arr= (int *)arr;
	if(input_arr[0]==input_arr[1] && input_arr[1]==input_arr[2]){
		printf("Youreka\n");
	}
	else if(input_arr[0]==input_arr[2] || input_arr[0]==input_arr[1] || input_arr[2]==input_arr[1]){
		printf("Miracle\n");
	}
	else if(input_arr[0]!=input_arr[2] && input_arr[0]!=input_arr[1] && input_arr[1]!=input_arr[2]){
		printf("Hasta la vista\n");
	}
	return NULL;
}

int main(){
	char a[200];
	int arr[3];
	for(int i=0; i<3; i++){ 
		scanf("%s", &a);
		pthread_t thread;
		pthread_create(&thread, NULL, cal_ascii, &a);
		pthread_join(thread, &arr[i]);	
	}

	pthread_t thread4;
	pthread_create(&thread4, NULL, compare, arr);
	pthread_join(thread4, NULL);
	return 0;
}