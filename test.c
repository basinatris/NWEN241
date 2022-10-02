#include <stdio.h>
#include <string.h>

int main()
{
	char foo[100] = "foobar\n";
	char bar[10] = "foobar\n";
	printf("strcmp: %d", strcmp(foo, bar));
}
