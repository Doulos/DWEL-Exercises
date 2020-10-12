#include <stdio.h>
#include "sums.h"

int main(void)
{
	unsigned int x = 0;
	unsigned int y = 0;
	unsigned int answer = 0;

	printf("Type a number between 1 and 10:\n");
	scanf("%d", &x);

	printf("Type another number between 1 and 10:\n");
	scanf("%d", &y);

	answer = add(x,y);

	printf("\n %d add %d is %d\n", x, y, answer);

	answer = take(x,y);

	printf("\n %d take %d is %d\n", x, y, answer);

	return 0;
}

