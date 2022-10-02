#include <stdio.h>

// Define structure record
struct record{
    char name[40];
    short int age;
    float height;
};
// Implement print_record_ptr() function
void print_record_ptr(struct record *rec){
    printf("Name  : %s\n", rec -> name);
    printf("Age   : %d\n", rec -> age);
    printf("Height: %.2f", rec -> height);
}

int main(void)
{
    struct record rec;

    scanf("%s %d %f", rec.name, &rec.age, &rec.height);
    print_record_ptr(&rec);
    return 0;
}
