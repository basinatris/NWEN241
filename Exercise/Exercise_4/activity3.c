#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    int sum = 0;
    for (int i = 1; i < argc; i++){
        int var = 0;
        char str[5];
        strncpy(str, argv[i], 5);
        //printf("[%s]\n", str);
        sscanf(str, "%d", &var);
        //printf("%d\n", var);
        sum += var;
    }
    printf("%d\n", sum);
    return 0;
}
