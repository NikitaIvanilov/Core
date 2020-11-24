class Point{

  private:

  int x, y;

  public:

  void set_x(int x){ this->x = x; }
  void set_y(int y){ this->y = y; }

  int get_x(void){ return x; }
  int get_y(void){ return y; }

  Point(int x, int y){

    set_x(x);
    set_y(y);

  }

  Point(){

    set_x(0);
    set_y(0);

  }

};