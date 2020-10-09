// Johnny Batista da Silva
// 11371350

#include <stdio.h>
#include <stdlib.h>

int Recorrencia(int x, int y)
{
    int primo = 1; // a

    if(y > 1) //caso base f(1) = 1
    {
        if (x % y == 0) //c 
        {
            primo = 0;
        }
        else //pior caso
        {
            primo = Recorrencia(x, y-1); //a + f(x-1)
        }
    }
    return primo;
}

int main(void)
{
    int n, x;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) // n (a + c)
    {
        scanf("%d", &x);
        int p = Recorrencia(x, x-1); // n+a(f(x-1))
        if (p) 
            printf("%d Primo\n", x);
        else 
            printf("%d Nao primo\n", x);
    }

    return 0;
}

//JBMolotov