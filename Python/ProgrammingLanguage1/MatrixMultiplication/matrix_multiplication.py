# Author        : Anju K. James
# Date          : 09-17-2019
# Purpose       : Perform matrix multiplication on square matrices
# Assumption    : Nil
# Description   : This program multiplies two NxN floating point Matrices.
#                 The memory is allocated dynamically based on the size of matrix.
#                 A random number generator is used to populate the Matrices,

import sys
import random


def main () :

    # Read the size of squre matrix
    size = input ( "Enter the size of matrix( 250, 500, 1000, 1500, 2000 ):" )

    # Check for size. Exit if it doesnt match the requirement.
    if size == 250 or size == 500 or size == 1000 or size == 1500 or size == 2000 :

        # Declare 3 two dimensional matrices.
        matrix1 = []
        matrix2 = []
        result = []

        # Assign random float values in matrix1 and matrix2
        for i in range ( size ) :
            matrix1.append ( list () )
            matrix2.append ( list () )
            result.append ( list () )
            for j in range ( size ) :
                matrix1[i].append ( random.random () )
                matrix2[i].append ( random.random () )
                result[i].append ( 0 )

        #print matrix1
        #print matrix2

        # Matrix multiplication
        for i in range( size ): 
            for j in range( size ): 
                for k in range( size ): 
                    # resulted matrix 
                    result[i][j] += matrix1[i][k] * matrix2[k][j] 

        #print result

    else :
        print ( "Incorrect size!!. Please enter a value from ( 250, 500, 1000, 1500, 2000 )" )
        sys.exit ()

if __name__ == "__main__" :
    main ()
