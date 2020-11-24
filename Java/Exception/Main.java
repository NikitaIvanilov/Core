import java.util.Scanner;

public class Main{

  public static void main(String[] args) throws Exception{

    Scanner scan = new Scanner(System.in);

    int bin = scan.nextInt();

    try{

      if(bin == 0) throw new Exception("Zero"); else
      if(bin == 1) throw new Exception("One");

    }
    catch(Exception ex){

      System.out.printf("Exception catched: %s\n", ex.getMessage());

    }
    finally{

      System.out.printf("Finally block\n");

    }

    scan.close();

  }

}