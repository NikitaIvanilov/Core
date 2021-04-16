import java.util.Random;

public class MyThread extends Thread{

  private       boolean Running;
  private       int     Complexity;
  private final int     ThreadSecondOfSleep = 1000;

  MyThread(String name){

    super(name);
    Running = true;
    createComplexity(5);

  }

  public void run(){

    printStartedThread();
    checkComplexity();

    if(Running == true)

      work();

    printResult();

  }

  private void printStartedThread(){

    System.out.printf("%s ->\n", Thread.currentThread().getName());

  }

  private void printResult(){

    if(Running == true)

      System.out.printf( "%s <- %.1f\n",

        Thread.currentThread().getName(),
        (float) Complexity / ThreadSecondOfSleep

      );

    else

      System.out.printf("%s <x\n", Thread.currentThread().getName());

  }

  private void threadTerminate(){

    Running = false;

  }

  private void checkComplexity(){ // Thread terminate example

    if(Complexity > 2000 && Complexity < 3000)

      threadTerminate();

  }

  private void createComplexity(int value){ // Abstract complexity for work imitation

    Complexity = new Random().nextInt(value * ThreadSecondOfSleep);

  }

  private void work(){ // Work imitation

    try{

      Thread.sleep(Complexity);

    }

    catch(Exception exception){

    }

  }

}