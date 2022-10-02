#include <stdio.h>

int main(void)
{
    int a = 1, b = 1;
    FILE *in; // use for handling input file
    FILE *out; // use for handling output file
    
    // Open raw.txt for reading
    in = fopen("raw.txt", "r");
    if (in == NULL)
        return -1;
    
    // Open processed.txt for writing
    out = fopen("processed.txt", "w");
    if (out == NULL)
        return -1;
    
    
    // Go thru raw.txt file and generate processed.txt file accordingly
    while (1){
        int ret = fscanf(in, "%d %d", &a, &b);
        if (ret == EOF)
            break;
        int sum = a + b;
        fprintf(out, "%d %d %d\n", a, b, sum);
        //printf("%d %d %d\n", a, b, sum);
    }
    
    fclose(in);
    fclose(out);
    return 0;
}
