public class Overload{

  private int a = -1,
              b = -1,
              c = -1;

  // Constructor

  Overload(int a, int b, int c){ set(a, b, c); }
  Overload(int a, int b)       { set(a, b); }
  Overload(int a)              { set(a); }

  // Method

  void set(int a, int b, int c){

    this.a = a;
    this.b = b;
    this.c = c;

  }

  void set(int a, int b){

    this.a = a;
    this.b = b;

  }

  void set(int a){

    this.a = a;

  }

  void print(){

    System.out.printf("a:%d\tb:%d\tc:%d\n", a, b, c);

  }

}