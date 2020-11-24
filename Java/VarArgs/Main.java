public class Main{

  public static void main(String[] args){

    System.out.printf("%d\n", sum(2, 4, 8, 16, 32, 64, 128, 256)); // 510

  }

  private static int sum(int ... numbers){

    int out = 0;

    for(int i = 0; i < numbers.length; ++i)

      out += numbers[i];

    return out;

  }

}