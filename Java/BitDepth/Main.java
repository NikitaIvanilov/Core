/*

  Terminal game, like 2048.

  You must add the same numbers,
  by increasing their bit depth.

  Control:

    WASD - swipe Up, Left, Down, Right.
    Q    - Quit.

  How it works:

    [Pressed "D"] Right

    0 2 2    0 0 4    0 0 4
    8 0 0 -> 0 0 8 -> 0 0 8
    2 2 4    0 4 4    0 0 8

    [Pressed "W"] Up

    0 2 2    2 4 2
    0 0 0 -> 0 0 0
    2 2 0    0 0 0

*/

import java.io.IOException;

public class Main{

  public static void main(String[] args) throws IOException{

    Surface s = new Surface(4, 8);

    for(int c; (c = System.in.read()) != (int) 'q' && s.check_null_point() != 0; ){

      if(c == (int) '\n'){

        s.random_point();
        s.print();

      }

      switch(c){

        case (int) 'w': s.move_top();    break;
        case (int) 's': s.move_bottom(); break;
        case (int) 'a': s.move_left();   break;
        case (int) 'd': s.move_right();  break;

      };

    }

    System.out.printf("Sum: %d\n", s.get_sum_points());

  }

}