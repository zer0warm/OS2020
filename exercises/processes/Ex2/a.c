#include <stdio.h>

int Acompute1()
{
    return 12345;
}

void Acompute2(int resB)
{
    printf("Res B = %d\n", resB);
}

int main(int agrc, char *argv[])
{
    int resA, resB;
    resA = Acompute1();
    printf("%d\n", resA);
    scanf("%d", &resB);
    Acompute2(resB);

    return 0;
}
