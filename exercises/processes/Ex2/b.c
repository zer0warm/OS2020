#include <stdio.h>

int Bcompute1()
{
    return 54321;
}

void Bcompute2(int resA)
{
    printf("Res A = %d\n", resA);
}

int main(int argc, char *argv[])
{
    int resA, resB;
    resB = Bcompute1();
    printf("%d\n", resB);
    scanf("%d", &resA);
    Bcompute2(resA);
    
    return 0;
}