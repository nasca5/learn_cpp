#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  double n, m;
  double pi = 3.1415926535;
  char szInput[256];
  printf("Enter degrees: ");
  scanf("%s", szInput);
  n = atof(szInput);
  m = sin(n * pi / 180);
  printf("The sine of %f degrees is %f\n", n, m);
  return 0;
}
