#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    scanf("%s", str);
    
    char result[50] = "Palindrome";
    
    int mid=0;
    int l_idx=0;
    int r_idx=strlen(str)-1;
    
    if(strlen(str)%2 == 0){
        mid = strlen(str)/2;
    }
    else{
        mid = (strlen(str)-1)/2;
    }
    
    for (int i = 0; i < mid; i++) {
        if (str[l_idx] != str[r_idx]){
            strcpy(result, "Not Palindrome");
            break;
        }
        l_idx++;
        r_idx--;
    }
    printf("%s", result);
    return 0;
}
