/*

  Overloading methods and constructors.

*/

public class Main{

  public static void main(String[] args){

    Overload old_1 = new Overload( 1, 10, 100), // a, b, c
             old_2 = new Overload(10, 10);      // a, b

    System.out.printf("old_1: "); old_1.print();
    System.out.printf("old_2: "); old_2.print(); System.out.printf("\n");

    old_1.set(0, 100, 0); // a, b, c
    old_2.set(0, 0);      // a, b

    System.out.printf("old_1: "); old_1.print();
    System.out.printf("old_2: "); old_2.print(); System.out.printf("\n");

    old_1.set(5); // a
    old_2.set(5); // a

    System.out.printf("old_1: "); old_1.print();
    System.out.printf("old_2: "); old_2.print(); System.out.printf("\n");

  }

}

/*

  Note: -1 is untouched variable.

*/