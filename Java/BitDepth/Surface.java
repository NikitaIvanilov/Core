import java.util.Random;

public class Surface{

  private int[][] surface;

  private int width,
              height;

  Surface(int width, int height){

    surface = new int[height][width];

    this.width  = width;
    this.height = height;

  }

  // Movement

  public void move_top(){

    for(int y = 0; y < height; ++y)

      for(int x = width - 1; x >= 0; --x)

        if(surface[y][x] > 0 && (x - 1) >= 0)

          if(surface[y][x - 1] == 0 || surface[y][x - 1] == surface[y][x]){

            surface[y][x - 1] += surface[y][x];
            surface[y][x] = 0;
            x = width;

          }

  }

  public void move_bottom(){

    for(int y = 0; y < height; ++y)

      for(int x = 0; x < width; ++x)

        if(surface[y][x] > 0 && (x + 1) < width)

          if(surface[y][x + 1] == 0 || surface[y][x + 1] == surface[y][x]){

            surface[y][x + 1] += surface[y][x];
            surface[y][x] = 0;
            x = -1;

          }

  }

  public void move_right(){

    for(int x = 0; x < width; ++x)

      for(int y = 0; y < height; ++y)

        if(surface[y][x] > 0 && (y + 1) < height)

          if(surface[y + 1][x] == 0 || surface[y + 1][x] == surface[y][x]){

            surface[y + 1][x] += surface[y][x];
            surface[y][x] = 0;
            y = -1;

          }

  }

  public void move_left(){

    for(int x = 0; x < width; ++x)

      for(int y = height - 1; y >= 0; --y)

        if(surface[y][x] > 0 && (y - 1) >= 0)

          if(surface[y - 1][x] == 0 || surface[y - 1][x] == surface[y][x]){

            surface[y - 1][x] += surface[y][x];
            surface[y][x] = 0;
            y = height;

          }

  }

  // Logic

  public void random_point(){

    Random r = new Random();

    int x = r.nextInt(width),
        y = r.nextInt(height);

    if(surface[y][x] == 0)

      surface[y][x] = 2;

  }

  public int check_null_point(){

    for(int x = 0; x < width; ++x)

      for(int y = 0; y < height; ++y)

        if(surface[y][x] == 0) return 1;

    return 0;

  }

  public int get_sum_points(){

    int out = 0;

    for(int x = 0; x < width; ++x)

      for(int y = 0; y < height; ++y)

        out += surface[y][x];

    return out;

  }

  // Output

  public void print(){

    // Clear screen
    System.out.print("\033[H\033[2J");
    System.out.flush();

    for(int x = 0; x < width; ++x){

      for(int y = 0; y < height; ++y)

        System.out.printf("%d\t", surface[y][x]);

      System.out.print("\n");

    }

  }

}