import java.lang.Math;

public class Main{

  public static void main(String[] args){

    int max =  10,
        min = -10,

        out = (int) (Math.random() * (max - min + 1) + min);

    System.out.printf("%d\n", out);

  }

}