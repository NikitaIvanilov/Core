class Color{

  private:

  int red, green, blue;

  public:

  void set_color(Color color){

    this->red   = color.red;
    this->green = color.green;
    this->blue  = color.blue;

  }

  void set_red  (int value){ this->red   = value; }
  void set_green(int value){ this->green = value; }
  void set_blue (int value){ this->blue  = value; }

  int get_red  (void){ return red;   }
  int get_green(void){ return green; }
  int get_blue (void){ return blue;  }

  Color(int r, int g, int b){

    set_red  (r);
    set_green(g);
    set_blue (b);

  }

  Color(){

    set_red  (0);
    set_green(0);
    set_blue (0);

  }

};