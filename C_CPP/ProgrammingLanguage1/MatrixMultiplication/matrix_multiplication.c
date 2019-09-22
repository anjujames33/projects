/* Author        : Anju K. James
** Date          : 09-17-2019
** Purpose       : Perform matrix multiplication on square matrices
** Assumption    : Nil
** Description   : This program multiplies two NxN floating point Matrices.
**                 The memory is allocated dynamically based on the size of matrix.
**                 A random number generator is used to populate the Matrices,
*/

#include <stdio.h>
#include <stdlib.h>


/* Function     : InitMatrix()
** Description  : Fill squre matrix of size 'size' with random float numbers.
** @param       : size - size of squre matrix
**              : matrix - matrix to be initialized.
** @return      : No return value. matrix will be modified since passing by reference.
*/
void InitMatrix( int size, float *matrix[] )
{
    int number;

    for ( int i = 0; i < size; i++ ) 
    {
        for ( int j = 0; j < size; j++ ) 
        {
            matrix[i][j] = ( float )rand() / RAND_MAX;
        }
    }
}


/* Function     : PrintMatrix()
** Description  : Display the values of matrix(debug purpose).
** @param       : size - size of squre matrix
**              : matrix - matrix to be printed.
** @return      : No return value.
*/
void PrintMatrix( int size, float *matrix[] )
{
    for ( int i = 0; i < size; i++ )
    {
        for ( int j = 0; j < size; j++ )
        {
            printf( "%f\t", matrix[i][j]  );
        }
        printf( "\n" );
    }
}


/* Function     : MultiplyMatrix()
** Description  : Multiply 2 matrices and assign value to result matrix.
** @param       : size - size of squre matrix
**              : matrix1 - matrix one.
**              : matrix2 - matrix two.
**              : result - matrix with multiplication result of matrix1 and matrix2.
** @return      : No return value. 'result' will be modified since passing by reference.
*/
void MultiplyMatrix( int size, float *matrix1[],float *matrix2[], float *result[] )
{
    for( int i = 0; i < size; i++ ) 
    { 
        for( int j = 0; j < size; j++ ) 
        { 
            for( int k = 0; k < size; k++ ) 
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j]; 
            } 
        } 
    } 
}


/* Function     : main()
** Description  : Execution starts here.
** @param       : Nil
** @return      : integer value 0.
*/
int main()
{
    int size = 0;

    //Read the size of squre matrix
    printf( "\nEnter the size of matrix( 250, 500, 1000, 1500, 2000 ):" );
    scanf( "%d", &size );

    //Check if the value entered matches with the requirement.Exit program otherwise.
    if( size == 250 || size == 500 || size == 1000 || size == 1500 || size == 2000 ) 
    {
        //Initialize and dynamically allocate memory for 3 float matrices. 
        float *matrix1[ size ]; 
        float *matrix2[ size ]; 
        float *result[ size ]; 
        for ( int i = 0; i < size; i++ )
        { 
            matrix1[ i ] = ( float * )malloc( size * sizeof( float ) ); 
            matrix2[ i ] = ( float * )malloc( size * sizeof( float ) ); 
            result[ i ] = ( float * )malloc( size * sizeof( float ) ); 
        }

        //Initialize and print first matrix
        InitMatrix( size, matrix1 );
        //printf( "\n========== Matrix 1 ===========\n" );
        //PrintMatrix( size, matrix1 );

        //Initialize and print second matrix
        InitMatrix( size, matrix2 );
        //printf( "\n========== Matrix 2 ===========\n" );
        //PrintMatrix( size, matrix2 );

        //Multiply matrix1, matrix2 and assign result to result matrix
        MultiplyMatrix( size, matrix1, matrix2, result );

        //Print the result matrix
        //printf( "\n========== Result ===========\n" );
        //PrintMatrix( size, result );

        //Free dynamically allocated memory
        //free( matrix1 );
        //free( matrix2 );
        //free( result );

    }
    else
    {
        printf( "\nIncorrect size!!. Please enter a value from ( 250, 500, 1000, 1500, 2000 )\n" );
        return 0;
    }

    return 0;
}
