package commandExecute;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.InputStream;

public abstract class CommandExecute{

  protected BufferedReader getBufferedReader(Process process){

    InputStream       inputStream       = process.getInputStream();
    InputStreamReader inputStreamReader = new InputStreamReader(inputStream);
    BufferedReader    bufferedReader    = new BufferedReader(inputStreamReader);

    return bufferedReader;

  }

  protected Process getProcess(String command) throws Exception{

    return Runtime.getRuntime().exec(command);

  }

}