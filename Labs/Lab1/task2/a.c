#include <stdio.h>

int main() {
    float num1, num2;

    scanf("%f", &num1);
    scanf("%f", &num2);

    if (num1 > num2) {
        printf("The first number is greater: %f \n", num1-num2);
    } else if (num1 < num2) {
        printf("The second number is greater: %f \n", num1+num2);
    } else {
        printf("The number is equal: %f \n", num1*num2);
    }
    return 0;
}
