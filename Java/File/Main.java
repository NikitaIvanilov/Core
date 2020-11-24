import java.io.FileWriter;

import java.io.FileReader;
import java.io.BufferedReader;

public class Main{

  public static void main(String[] args) throws Exception{

    // Write

    FileWriter output = new FileWriter("File.txt");

    output.write("Thrall, Son of Durotan.\n");

    output.close();

    // Read

    FileReader     input  = new FileReader("File.txt");
    BufferedReader buffer = new BufferedReader(input);
    String         print  = new String(buffer.readLine());

    System.out.printf("%s", print);

    input.close();
    buffer.close();

  }

}