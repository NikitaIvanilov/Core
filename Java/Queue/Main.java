import java.util.PriorityQueue;

public class Main{

  public static void main(String[] args){

    PriorityQueue<Integer> test = new PriorityQueue<Integer>();

    test.add(0);
    test.add(2);
    test.add(4);
    test.add(6);

    test.offer(22); // add to end

    test.remove(); // remove head element, currently 0

    while(test.size() > 0)

      System.out.printf("%d\n", test.poll());

    /* poll and remove - get first element and remove it.
       peek and element - get first element only. */

  }

}