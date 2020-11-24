public class Main{

  public static void main(String[] args){

    Test test = new Test.Builder()
      .Alpha(10)
      .Beta (20)
      .Gamma(30)
      .Delta(40)
      .build();

    test.print();

  }

}