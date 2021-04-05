package commandExecute;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.InputStream;
import java.util.ArrayList;

public class CommandExecuteArrayList extends CommandExecute{

  public ArrayList<String> execute(String command) throws Exception{

    try{

      Process           process = getProcess       (command);
      BufferedReader    reader  = getBufferedReader(process);
      ArrayList<String> output  = getCommandOutput (reader);

      reader.close();

      return output;

    }

    catch(Exception exception){

      return null;

    }

  }

  private ArrayList<String> getCommandOutput(BufferedReader bufferedReader) throws Exception{

    ArrayList<String> stringList = new ArrayList<>();

    for(

      String string  = bufferedReader.readLine();
             string != null;
             string  = bufferedReader.readLine()

    )  stringList.add(string);

    return stringList;

  }

}