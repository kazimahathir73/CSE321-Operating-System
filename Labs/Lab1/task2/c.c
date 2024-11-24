#include <stdio.h>
#include <string.h>

int main() {
    char pass[100];
    char mess[100]= "";
    scanf("%s", pass);
    
    int u=0;
    int l=0;
    int d=0;
    int s=0;
    
    for(int i=0; i<strlen(pass); i++){
        if(isdigit(pass[i])) {
            d++;
        } else if (isupper(pass[i])) {
            u++;
        } else if (islower(pass[i])) {
            l++;
        } else if (pass[i] == '_' || pass[i] == '$' || pass[i] == '#' || pass[i] == '@') {
            s++;
        }
    }
    
    if(u>0 && l>0 && d>0 && s>0){
        printf("OK");
    }
    else{
        
        if(u==0){
            strcat(mess,"Uppercase character missing, ");
        }
        if(l==0){
            strcat(mess,"Lower character missing, ");
        }
        if(d==0){
            strcat(mess,"Digit character missing, ");
        }
        if(s==0){
            strcat(mess,"Special character missing, ");
        }
        printf("%s",mess);
    }
    return 0;
}