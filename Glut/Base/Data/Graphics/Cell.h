class Cell : public Point, public Color{

  public:

  Cell()                                  : Point(0, 0), Color(255, 100, 0){}
  Cell(int x, int y)                      : Point(x, y), Color(255, 100, 0){}
  Cell(int x, int y, int r, int g, int b) : Point(x, y), Color(r, g, b){}

  void print(void){

    int

      PixelSizeHalf = DisplayPixelSize / 2,

      left   = get_x() - PixelSizeHalf,
      right  = get_x() + PixelSizeHalf,
      bottom = get_y() - PixelSizeHalf,
      top    = get_y() + PixelSizeHalf;

    glColor3ub(get_red(), get_green(), get_blue());

    glBegin(GL_QUADS);

      glVertex2f(left,bottom);
      glVertex2f(left,top);
      glVertex2f(right,top);
      glVertex2f(right,bottom);

    glEnd();

  }

};