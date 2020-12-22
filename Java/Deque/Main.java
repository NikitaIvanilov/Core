import java.util.ArrayDeque;

public class Main{

  public static void main(String[] args){

    ArrayDeque<Integer> test = new ArrayDeque<Integer>();

    // add //

    test.add(1);

    test.addFirst(10);
    test.addLast (10);

    test.addFirst(100);
    test.addLast (100);

    // poll //

    test.pollFirst();
    test.pollLast ();

    // offer //

    test.offerFirst(1000);
    test.offerLast (1000);

    // output //

    while(test.size() > 0)

      System.out.printf("%d\n", test.poll());

  }

}