import java.util.Random;

public class Main{

  public static void main(String[] args){

    Random r = new Random();

    int n = r.nextInt(50); // [0 - 49]

    System.out.printf("%d\n", n);

  }

}