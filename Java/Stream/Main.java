import java.util.*;
import java.util.stream.*;

public class Main{

  public static void main(String[] args){

    List<Integer> list = Arrays.asList(2, 8, 3, 9, 12, 75, 2, 804, 7, 9, -1, 69, -465);

    example_collect(list);
    example_map    (list);
    example_forEach(list);
    example_count  (list);

  }

  public static void example_collect(List<Integer> list){

    System.out.printf("collect:");

    List<Integer> out = list.stream ()
                            .filter ((current) -> current % 2 == 0)
                            .collect(Collectors.toList());

    out.stream()
       .forEach((current) -> System.out.printf(" %d", current));

    System.out.printf("\n");

  }

  public static void example_map(List<Integer> list){

    System.out.printf("map:");

    list.stream ()
        .filter ((current) -> current > 0)
        .map    ((current) -> current * -1)
        .forEach((current) -> System.out.printf(" %d", current));

    System.out.printf("\n");

  }

  public static void example_forEach(List<Integer> list){

    System.out.printf("forEach:");

    list.stream ()
        .filter ((current) -> current <  10)
        .filter ((current) -> current > -10)
        .forEach((current) -> System.out.printf(" %d", current));

    System.out.printf("\n");

  }

  public static void example_count(List<Integer> list){

    System.out.printf("count:");

    long out = list.stream()
                   .filter((current) -> current <  10)
                   .filter((current) -> current > -10)
                   .count();

    System.out.printf(" %d\n", out);

  }

}