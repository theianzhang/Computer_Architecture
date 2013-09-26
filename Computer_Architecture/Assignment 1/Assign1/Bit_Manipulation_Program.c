#include <stdio.h>
#include <stdlib.h>

int first_question()
{
	//declare variables to input
	int x;
	int y;

	printf("Enter first number to reverse:");
	scanf("%x", &x);

	printf("Enter second number to interleave:");
	scanf("%x", &y);

	//shift bits
	int first_byte = x << 24;
	int second_byte = x<< 8;
	int third_byte = x>>8;
	int fourth_byte = x>>24;

	//mask to isolate the values wanted 
	first_byte = first_byte & 0xFF000000; 
	second_byte = second_byte & 0x00FF0000;
	third_byte = third_byte & 0x0000FF00;
	fourth_byte = fourth_byte & 0x000000FF;

	int reversed = first_byte | second_byte | third_byte | fourth_byte;
	int fifth_byte = reversed & 0xFFFF0000;
	int sixth_byte = reversed << 16;
	sixth_byte = sixth_byte & 0xFFFF0000;

	int seventh_byte = y & 0x0000FFFF;

	int eighth_byte = y>>16;
	eighth_byte = eighth_byte & 0x0000FFFF;

	int output1 = fifth_byte | eighth_byte;
	int output2 = sixth_byte | seventh_byte;

	printf("Your interleaved outputs are %x and %x\n", output1, output2);
}

int main()
{ first_question(); }
