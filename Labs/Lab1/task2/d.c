#include <stdio.h>
#include <string.h>

int main() {
    char mail[100];
    char domain[10] = "";
    int idx = 0;
    scanf("%s", mail);
    
    for (int i = 0; i < strlen(mail); i++) {
        if (mail[i] == '@') {
            for (int j = i + 1; j < strlen(mail); j++) {
                if (mail[j] == '.') {
                    break;
                }
                domain[idx] = mail[j];
                idx++;
            }
            break;
        }
    }

    if(strcmp(domain, "kaaj") == 0){
        printf("Email address is outdated");
    }
    else if(strcmp(domain, "sheba") == 0){
        printf("Email address is okay");
    }
    return 0;
}
