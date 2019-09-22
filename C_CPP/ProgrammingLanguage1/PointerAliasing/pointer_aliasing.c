#include <stdio.h>

main()
{
    int i;
    float *f;

    // i=1092616192;
    i=1097859072;
    f=(float *)&i;

    printf("i address and f address are %ul and %ul\n",&i,f);

    printf("i is %d and f is %f\n",i,*f);

    printf("int length float length %d %d\n",sizeof(int), sizeof(float));

}
