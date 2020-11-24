public class Main{

  public static void main(String[] args){

    Interface Plus  = (x, y) -> x + y,
              Minus = (x, y) -> x - y;

    System.out.printf("Plus: %d\nMinus: %d\n",

      Plus.operation(128, 128), // 128 + 128 = 256
      Minus.operation(64, 32)   // 64 - 32 = 32

    );

  }

}

interface Interface{

  int operation(int x, int y);

}