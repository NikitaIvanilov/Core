package commandExecute;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.InputStream;

public class CommandExecuteEcho extends CommandExecute{

  public void execute(String command) throws Exception{

    try{

      Process        process = getProcess       (command);
      BufferedReader reader  = getBufferedReader(process);
      String         output  = getCommandOutput (reader);

      reader.close();

      System.out.print(output);

    }

    catch(Exception exception){}

  }

  private String getCommandOutput(BufferedReader bufferedReader) throws Exception{

    String stringList = "";

    for(

      String string  = bufferedReader.readLine();
             string != null;
             string  = bufferedReader.readLine()

    )  stringList += string + "\n";

    return stringList;

  }

}