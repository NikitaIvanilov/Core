import java.io.IOException;

public class Main{

  public static void main(String[] args) throws IOException{

    String out = new String();

    for(int i; (i = System.in.read()) != (int) '\n'; )

      out += (char) i;

    System.out.printf("%s\n", out);

  }

}