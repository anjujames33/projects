public class Assignment02{
    
    static boolean Test()
    {
        System.out.println("I have been evaluated\n");
        return true;
    }
    
    
    public static void main(String []args){
         
        int i = 1;
    
        if ( (i == 0) && (Test()) )
        {
            System.out.println("True\n");
        }
        else
        {
            System.out.println("False\n");
        }
    
    }
}

//$javac Assignment02.java
//$java -Xmx128M -Xms16M Assignment02
//False
