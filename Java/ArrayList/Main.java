import java.util.ArrayList;

public class Main{

  public static void main(String[] args){

    ArrayList<String> blocks = new ArrayList<>();

    blocks.add("Grass");
    blocks.add("Stone");
    blocks.add("Water");

    for(String current : blocks)

      System.out.printf("%s ", current);

    System.out.printf("<- Foreach\n");

    for(int i = 0; i < blocks.size(); ++i)

      System.out.printf("%s ", blocks.get(i));

    System.out.printf("<- Default\n");

  }

}