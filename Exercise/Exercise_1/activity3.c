#include <stdio.h>

int main(void){
    char str[100];
    printf("Enter a string: ");
    scanf("%[^\n]s", &str);
    printf("%s\n", str);
}
