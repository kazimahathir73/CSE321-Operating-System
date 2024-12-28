#include <stdio.h>

int perfect_n(int num) {
    int sum = 0;

    for (int i = 1; i <= num / 2; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }
    
    if(sum == num){
        return num;
    }
    else{
        return 0;   
    }
}

void print_perfect(int s, int e) {
    for (int i = s; i <= e; i++) {
        if (perfect_n(i)!=0) {
            printf("%d\n", i);
        }
    }
}

int main() {
    int start, end;

    scanf("%d", &start);
    scanf("%d", &end);

    print_perfect(start, end);

    return 0;
}