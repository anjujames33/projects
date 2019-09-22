# Author:
# Date :
# Purpose:
# Assumption:
# Description

def Test () :
    print ( 'I have been evaluated' )
    return 1


def main () :
    i = 1;

    if i == 0 and Test () :
        print ( 'True' )
    else :
        print ( 'False' )


if __name__ == "__main__" :
    main ()
