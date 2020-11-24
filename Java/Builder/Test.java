public class Test{

  private int alpha, beta, gamma, delta;

  public void print(){

    System.out.printf(

      "Alpha:\t%d\nBeta:\t%d\nGamma:\t%d\nDelta:\t%d\n",
       alpha, beta, gamma, delta

    );

  }

  public static class Builder{

    private Test test;

    public Builder(){

      test = new Test();

    }

    public Builder Alpha(int number){

      test.alpha = number;
      return this;

    }

    public Builder Beta(int number){

      test.beta = number;
      return this;

    }

    public Builder Gamma(int number){

      test.gamma = number;
      return this;

    }

    public Builder Delta(int number){

      test.delta = number;
      return this;

    }

    public Test build(){

      return test;

    }

  }

}