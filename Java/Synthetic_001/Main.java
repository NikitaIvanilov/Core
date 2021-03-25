import java.util.ArrayList;

public class Main{

  public static void main(String[] args){

    // Declaration
    RandomNumber                                    randomNumber;
    ArrayList    <Integer>                          arrayList;
    FillWith     <ArrayList<Integer>, RandomNumber> fill;
    PrintArray   <ArrayList<Integer>  >             print;
    Search       <ArrayList<Integer>  >             search;
    Sort         <ArrayList<Integer>  >             sort;

    // Initialization
    randomNumber = new RandomNumber   ();
    arrayList    = new ArrayList    <>();
    fill         = new FillWith     <>(arrayList, randomNumber);
    print        = new PrintArray   <>(arrayList);
    search       = new Search       <>(arrayList);
    sort         = new Sort         <>(arrayList);

    // Run

    fill.run(10, 100); // (array size, random range)

    System.out.printf("Raw output:\n");
    print.run(3); // End of line per 3 numbers

    sort.quickSorting();

    System.out.printf("\n\nSorted:\n");
    print.run(3);

    System.out.printf("\n\nPrime numbers:\n ");

    System.out.print(search.getPrimeNumber());

    System.out.printf("\n\n Minimum: %d\n Medium: %d\n Maximum: %d\n\n",

      search.getMinimum(),
      search.getMedium (),
      search.getMaximum()

    );

  }

}