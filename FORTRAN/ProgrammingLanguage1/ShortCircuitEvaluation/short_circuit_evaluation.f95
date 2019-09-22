!Author         : Anju K. James
!Date           : 09-09-2019
!Assumptions    : Nil
!Description    : This program is to test short circuit behaviour in FORTRAN


!Logical function Test() returns true
logical function Test()

    print*,"I have been evaluated"

    !Set the return value as true
    Test = .true.

!end of function
 end function Test


 ! main function
 program main

    !set the return type of function as logical. Else treated as 'Real' type
    logical :: Test

    !Declare integer i and assign value as 1
    integer :: i = 1

    !Condition to test the short circuit behaviour. If Fortran supports short circuit, second condition is ignored.
    if (i == 0 .and. Test()) then
        print*,"True"
    else
        print*,"False"
    end if

! End of main program.
 end program main

