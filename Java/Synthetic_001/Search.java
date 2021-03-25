import java.util.ArrayList;

public class Search<A extends ArrayList<Integer>>{

  private A array;

  Search(A array){

    this.array = array;

  }

  public ArrayList<Integer> getPrimeNumber(){

    ArrayList<Integer> arrayOutput = new ArrayList<>();
    boolean primeNumber;

    for(Integer current : array){

      if(current < 2)

        continue;

      primeNumber = true;

      for(Integer check = 2; check < current; ++check){

        if(current % check == 0){

          primeNumber = false;
          break;

        }

      }

      if(primeNumber)

        arrayOutput.add(current);

    }

    return arrayOutput;

  }

  public int getMaximum(){

    Integer maximum = 0;

    for(Integer current : array)

      if(current > maximum)

        maximum = current;

    return maximum;

  }

  public int getMinimum(){

    Integer minimum = array.get(0);

    for(Integer current : array)

      if(current < minimum)

        minimum = current;

    return minimum;

  }

  public int getMedium(){

    int pivot = (getMaximum() + getMinimum()) / 2,

        left  = pivot,
        right = pivot;

    while(array.indexOf(left)  == -1 && left  > getMinimum()) --left;
    while(array.indexOf(right) == -1 && right < getMaximum()) ++right;

    int leftDifference  = Math.abs(pivot - left),
        rightDifference = Math.abs(pivot - right);

    if(leftDifference < rightDifference)

      return left;

    else

      return right;

  }

}