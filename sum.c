#include <stdio.h>
#include <stdlib.h>

/**
 * main - prints the sum of the multiples of 5 and 8 below 1024
 *
 * Return: 0 on success
 */

int main(void)
{
  int q, sum;

  sum = 0;
  for (q = 0; q < 1024; q++)
    {
      if (q % 5 == 0 || q % 8 == 0)
	{
	  sum += q;
	}
    }
  printf("%d\n", sum);
  return (0);
}
