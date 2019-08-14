#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>

int gcd(int a, int b)
{
    int remainder;
    while (b != 0)
    {
        remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int number = rand(), loop = 1, count;
    int x_fixed = 2, x = 2, size = 2, factor;
    printf("%d\n", number);
    do
    {
        printf("----   loop %4i   ----\n", loop);
        count = size;
        do
        {
            x = (x * x + 1) % number;
            factor = gcd(abs(x - x_fixed), number);
            printf("count = %4i  x = %6i  factor = %i\n", size - count + 1, x, factor);
        } while (--count && (factor == 1));
        size *= 2;
        x_fixed = x;
        loop = loop + 1;
    } while (factor == 1);
    printf("factor is %i\n", factor);
    return factor == number ? EXIT_FAILURE : EXIT_SUCCESS;
}