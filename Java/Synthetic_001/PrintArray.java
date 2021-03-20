import java.util.ArrayList;

public class PrintArray<A extends ArrayList<Integer>>{

  private A      array;
  private String outputFormat = "%3d";

  PrintArray(A array){

    this.array = array;

  }

  // Output format

  public String getOutputFormat(){

    return outputFormat;

  }

  public void setOutputFormat(String outputFormat){

    this.outputFormat = outputFormat;

  }

  // Run

  public void run(){

    for(Integer current : array){

      System.out.printf("%d\n", current);

    }

  }

  public void run(final int stringSize){

    int stringSizeCounter = 0;

    for(Integer current : array){

      System.out.printf(outputFormat, current);

      if(stringSizeCounter == stringSize - 1){

        System.out.printf("\n");
        stringSizeCounter = 0;

      }

      else{

        ++stringSizeCounter;

      }

    }

  }

}