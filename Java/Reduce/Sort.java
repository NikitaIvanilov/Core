import java.util.List;
import java.util.Arrays;

public class Sort{

  public static void main(String[] args){

    List<Integer> l = Arrays.asList(2, 5, 8, 0, 1, 10, 5, 3);

    Integer out = l

      .stream()
      .reduce(0, (current, next) -> current < next ? next : current);

    System.out.printf("%d\n", out);

  }

}