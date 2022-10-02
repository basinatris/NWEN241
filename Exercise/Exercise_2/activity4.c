#include <stdio.h>

#define MAX	100

// Implement find_max() function using pointer
int *find_max(int *a, int alen) {
    // These variables should be enough. Do not declare any other variable.
    int *max = a, *p = a;
    while (p < a + alen){
        if (*max < *p) max = p;
        p++;
        //printf("work\n");
    }
    // Use pointer p to iterate over arrays and access arrays elements
    // Use max to point to the latest maximum value found
    // Use either while-loop or for-loop to iterate
        
    
    // max should point to the maximum
    return max;
}

int main(void)
{
    int n, array[MAX];
    scanf("%d", &n);
    for(int i=0; i<n; i++)
        scanf("%d", array+i);
    int *max = find_max(array, n);
    printf("%d", *max);
    return 0;
}
