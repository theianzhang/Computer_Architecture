#include <stdio.h>

void print_ascii(char *c, int i)
	{
		printf("Representations of char\n int: %d, char: %c\n", *c, *c);
		printf("Representations of int\n int: %d, char: %c\n", i, i);
	}

void main()
	{
		print_ascii("a", 'a' - 32);
		print_ascii("a", 'a' + 25);
		print_ascii("a", 'a' - 1);
		print_ascii("a", 115);
	}
