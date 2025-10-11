#include <stdio.h>
#define max(x, y) (x > y) ? (x) : (y)
#define min(x, y) (x < y) ? (x) : (y)
#define sommeEntier(n) (n * (n + 1) / 2)

int sommeEntieurSansMultplede10(int N)
{
   int i, total = 0;
   for (i = 1; i <= N; i++)
   {
      if (i % 10 != 0)
         total += i;
   }
   return ((int)total);
}

int main()
{
   int val1, val2;
   printf("entrer 2 valeur : ");
   scanf("%d %d", &val1, &val2);
   printf("\nle max est %d \n le min est %d ", max(val1, val2), min(val1, val2));
   int n = 20;
   printf("\nla somme du 1 jusqua %d est : %d", n, sommeEntier(n));
   printf("\nla somme du 1 jusqua %d en ignorant les multiples de 10 (10 20 30 ...) est : %d", n, sommeEntieurSansMultplede10(n));
}
