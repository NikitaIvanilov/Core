import java.util.List;
import java.util.Arrays;

public class Sum{

  public static void main(String[] args){

    List<Integer> numbers = Arrays.asList(2, 4, 8, 16);

    Integer sum = numbers

      .stream()
      .reduce(0, (current, next) -> current + next);

    System.out.printf("%d\n", sum);

  }

}