#include <stdio.h>
#include <stdlib.h>

int main()
{
	int x = 12;
	char a = 'a';
	char string[] = "Hello, world!";
	printf("Size: %d\n", sizeof(x));
	printf("Size: %d\n", sizeof(a));
	printf("String: %s\n", string);
	printf("String: %d\n", string);
}
