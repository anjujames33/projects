/* Author       : Anju K. James
** Date         : 09-09-2019 
** Purpose      : This code tests the  short circuit behaviour in C.
** Assumptions  : Nil
** Description  :
*/

#include <stdio.h>

//Test function returns 1
int Test()
{
    printf("I have been evaluated\n");
    return 1;
}

//main function
int main()
{
    int i = 1;

    //if short circuit is supported, second condition is not executed.
    if ( i == 0 && Test() )
    {
        printf("True\n");
    }
    else
    {
        printf("False\n");
    }

    return 0;
}

