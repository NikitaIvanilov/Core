public class RandomNumber{

  private int defaultRange = 10;

  public void setRange(int defaultRange){

    this.defaultRange = defaultRange;

  }

  public int get(){

    return (int) (Math.random() * defaultRange);

  }

  public int get(int customRange){

    return (int) (Math.random() * customRange);

  }

}