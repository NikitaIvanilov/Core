import java.util.ArrayList;

public class FillWith<A extends ArrayList<Integer>, G extends RandomNumber>{

  private A addable;
  private G getable;

  FillWith(A addable, G getable){

    this.addable = addable;
    this.getable = getable;

  }

  public void run(int numberOfElements){

    for(int i = 0; i < numberOfElements; ++i)

      addable.add(getable.get());

  }

  public void run(int numberOfElements, int rangeOfValues){

    for(int i = 0; i < numberOfElements; ++i)

      addable.add(getable.get(rangeOfValues));

  }

}