/*

  PaintGLUT - Pixel painter based on FreeGLUT.

  Dependencies: OpenGL(GL,GLU), FreeGLUT(glut).

  Compile: g++ PaintGLUT.cpp -lGL -lGLU -lglut

*/

#include <iostream>
#include <GL/glut.h>

#define SYSTEM_FRAME_RATE  60
#define SYSTEM_CURSOR_DATA 7
#define SYSTEM_COLORSTEP   10

//  ASCII
#define BUTTON_ESC   27
#define BUTTON_ENTER 13

#define BUTTON_SPACE      ' '
#define BUTTON_SAVEMAP    's'
#define BUTTON_LOADMAP    'l'
#define BUTTON_COLORMODE  'c'
#define BUTTON_AUTOPAINT  'a'
#define BUTTON_TAKECOLOR  't'
#define BUTTON_FILLCOLOR  'f'

#define BUTTON_RED_UP     'q'
#define BUTTON_RED_DOWN   'Q'
#define BUTTON_GREEN_UP   'w'
#define BUTTON_GREEN_DOWN 'W'
#define BUTTON_BLUE_UP    'e'
#define BUTTON_BLUE_DOWN  'E'

#define MAP_WIDTH     40
#define MAP_HEIGHT    40
#define MAP_SEPARATOR 10

using namespace std;

string

  filename = ("PaintGLUT_" + to_string(MAP_WIDTH) + "x" + to_string(MAP_HEIGHT));

void Keyboard(unsigned char key, int x, int y);
void KeyboardSpecial(int key, int x, int y);
void Reshape(int width, int height);
void DrawPixel(int x, int y);
void RedrawFrame(int value);
void Draw(void);

GLint

  Width = MAP_WIDTH * 10,
  Height = MAP_HEIGHT * 10,
  PixelSize = MAP_SEPARATOR;

class Color{

  public:

  int r, g, b;

  Color(){

    r = g = b = 255;

  }

  Color(int input_r, int input_g, int input_b){

    r = input_r;
    g = input_g;
    b = input_b;

  }

  int ReturnColorSum(void){

    return (r + g + b);

  }

};

Color Map[MAP_HEIGHT][MAP_WIDTH];

  void MapSave(void);
  void MapLoad(void);
  void MapPrint(void);
  void MapCellPrint(int x, int y);

int Cursor[SYSTEM_CURSOR_DATA] = {1,1,0,0,0,0,0};

  int *CursorX = &Cursor[0];
  int *CursorY = &Cursor[1];
  int *CursorR = &Cursor[2];
  int *CursorG = &Cursor[3];
  int *CursorB = &Cursor[4];
  int *CursorColorMode     = &Cursor[5];
  int *CursorAutoPaintMode = &Cursor[6];

  void CursorPaint(void);
  void CursorColor(void);
  void TakeColor(void);
  void FillColor(void);

int main(int argc, char *argv[]){

  glutInit(&argc, argv);
  glutInitWindowSize(Width, Height);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutCreateWindow("FreeGLUT");

  glutTimerFunc(SYSTEM_FRAME_RATE, RedrawFrame, 0);
  glutKeyboardFunc(Keyboard);
  glutSpecialFunc(KeyboardSpecial);
  glutReshapeFunc(Reshape);
  glutDisplayFunc(Draw);

  glutMainLoop();
  return 0;

}

void MapLoad(void){

  FILE *Save = fopen(filename.c_str(),"r");
  if(Save == 0)  return;

  int SaveHeight, SaveWidth;

  fscanf(Save,"Map[H:%d][W:%d]\n", &SaveHeight, &SaveWidth);  //  Save Map

  if(SaveHeight != MAP_HEIGHT || SaveWidth != MAP_WIDTH){  //  Check Map Compatibility

    fclose(Save);
    return;

  }

  for(int x = 1; x < MAP_WIDTH; ++x){

    for(int y = 1; y < MAP_HEIGHT; ++y)

      fscanf(Save,"[R:%d][G:%d][B:%d][X:%d][Y:%d]\n",
      &Map[y][x].r, &Map[y][x].g, &Map[y][x].b, &x, &y);

  }

  fscanf(Save,"Cursor\n");  //  Save Cursor

  for(int i = 0; i < SYSTEM_CURSOR_DATA; ++i)

    fscanf(Save,"[Cell:%d][Value:%d]\n",&i,&Cursor[i]);

  fclose(Save);

}

void MapSave(void){

  FILE *Save = fopen(filename.c_str(),"w");
  if(Save == 0)  return;

  fprintf(Save,"Map[H:%d][W:%d]\n", MAP_HEIGHT, MAP_WIDTH);  //  Save Map

  for(int x = 1; x < MAP_WIDTH; ++x){

    for(int y = 1; y < MAP_HEIGHT; ++y)

      fprintf(Save,"[R:%d][G:%d][B:%d][X:%d][Y:%d]\n",
      Map[y][x].r, Map[y][x].g, Map[y][x].b, x, y);

  }

  fprintf(Save,"Cursor\n");  //  Save Cursor

  for(int i = 0; i < SYSTEM_CURSOR_DATA; ++i)

    fprintf(Save,"[Cell:%d][Value:%d]\n",i,Cursor[i]);

  fclose(Save);

}

void FillColor(void){

  Color

    NeededColor = Map[*CursorY][*CursorX],
    MyColor(*CursorR, *CursorG, *CursorB);

  for(int x = 1; x < MAP_WIDTH; ++x){

    for(int y = 1; y < MAP_HEIGHT; ++y)

      if(NeededColor.ReturnColorSum() == Map[y][x].ReturnColorSum())

        Map[y][x] = MyColor;

  }

}

void TakeColor(void){

  *CursorR = Map[*CursorY][*CursorX].r;
  *CursorG = Map[*CursorY][*CursorX].g;
  *CursorB = Map[*CursorY][*CursorX].b;

}

void KeyboardSpecial(int key, int x, int y){

  if((*CursorAutoPaintMode) == 1)  CursorPaint();

  if((*CursorColorMode) == 1)  return;

  switch(key){

    case GLUT_KEY_UP:  if((*CursorY) < (MAP_HEIGHT - 1))  ++(*CursorY);
    break;

    case GLUT_KEY_DOWN:  if((*CursorY) > 1)  --(*CursorY);
    break;

    case GLUT_KEY_RIGHT:  if((*CursorX) < (MAP_WIDTH - 1))   ++(*CursorX);
    break;

    case GLUT_KEY_LEFT:  if((*CursorX) > 1)  --(*CursorX);
    break;

  };

}

void CursorColor(void){

  int left, right, top, bottom;

  left   = (Width  / 2) - (Width  / 4);
  right  = (Width  / 2) + (Width  / 4);
  bottom = (Height / 2) - (Height / 4);
  top    = (Height / 2) + (Height / 4);

  glColor3ub(*CursorR, *CursorG, *CursorB);

  glBegin(GL_QUADS);

    glVertex2f(left,bottom);
    glVertex2f(left,top);
    glVertex2f(right,top);
    glVertex2f(right,bottom);

  glEnd();

}

void CursorPaint(void){

  Map[*CursorY][*CursorX].r = *CursorR;
  Map[*CursorY][*CursorX].g = *CursorG;
  Map[*CursorY][*CursorX].b = *CursorB;

}

void MapCellPrint(int x, int y){

  int

    red   = Map[y / MAP_SEPARATOR][x / MAP_SEPARATOR].r,
    green = Map[y / MAP_SEPARATOR][x / MAP_SEPARATOR].g,
    blue  = Map[y / MAP_SEPARATOR][x / MAP_SEPARATOR].b;

  if((x / MAP_SEPARATOR) == (*CursorX) && (y / MAP_SEPARATOR) == (*CursorY)){

    red   = 255 - red;
    green = 255 - green;
    blue  = 255 - blue;

  }

  glColor3ub(red, green, blue);
  DrawPixel(x, y);

}

void MapPrint(void){

  int x,y;

  for(x = MAP_SEPARATOR; x < ((MAP_WIDTH - 1) * MAP_SEPARATOR) + MAP_SEPARATOR; x += MAP_SEPARATOR){

    for(y = MAP_SEPARATOR; y < ((MAP_HEIGHT - 1) * MAP_SEPARATOR) + MAP_SEPARATOR; y += MAP_SEPARATOR)
      MapCellPrint(x, y);

  }

}

void RedrawFrame(int value){

  glutPostRedisplay();
  glutTimerFunc(SYSTEM_FRAME_RATE, RedrawFrame, 0);

}

void Keyboard(unsigned char key, int x, int y){

  switch(key){

    case BUTTON_ESC:  exit(0);
    break;

    case BUTTON_SPACE:  CursorPaint();
    break;

    case BUTTON_SAVEMAP:  MapSave();
    break;

    case BUTTON_LOADMAP:  MapLoad();
    break;

    case BUTTON_TAKECOLOR:  TakeColor();
    break;

    case BUTTON_FILLCOLOR:  FillColor();
    break;

    case BUTTON_COLORMODE:

      if((*CursorColorMode) == 0)  (*CursorColorMode) = 1;
      else
        (*CursorColorMode) = 0;

    break;

    case BUTTON_AUTOPAINT:

      if((*CursorAutoPaintMode) == 0)  (*CursorAutoPaintMode) = 1;
      else
        (*CursorAutoPaintMode) = 0;

    break;

    case BUTTON_RED_UP:

      if(((*CursorR) + SYSTEM_COLORSTEP) <= 255)  *CursorR += SYSTEM_COLORSTEP;

    break;

    case BUTTON_GREEN_UP:

      if(((*CursorG) + SYSTEM_COLORSTEP) <= 255)  *CursorG += SYSTEM_COLORSTEP;

    break;

    case BUTTON_BLUE_UP:

      if(((*CursorB) + SYSTEM_COLORSTEP) <= 255)  *CursorB += SYSTEM_COLORSTEP;

    break;

    case BUTTON_RED_DOWN:

      if(((*CursorR) - SYSTEM_COLORSTEP) >= 0)  *CursorR -= SYSTEM_COLORSTEP;

    break;

    case BUTTON_GREEN_DOWN:

      if(((*CursorG) - SYSTEM_COLORSTEP) >= 0)  *CursorG -= SYSTEM_COLORSTEP;

    break;

    case BUTTON_BLUE_DOWN:

      if(((*CursorB) - SYSTEM_COLORSTEP) >= 0)  *CursorB -= SYSTEM_COLORSTEP;

    break;

  };

}

void DrawPixel(int x, int y){

  int left, right, top, bottom;
  int PixelSizeHalf = PixelSize / 2;

  left   = x - PixelSizeHalf;
  right  = x + PixelSizeHalf;
  bottom = y - PixelSizeHalf;
  top    = y + PixelSizeHalf;

  glBegin(GL_QUADS);

    glVertex2f(left,bottom);
    glVertex2f(left,top);
    glVertex2f(right,top);
    glVertex2f(right,bottom);

  glEnd();

}

void Reshape(GLint width, GLint height){

  Width  = width;
  Height = height;

  glViewport(0, 0, Width, Height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(0, Width, 0, Height, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

}

void Draw(void){

  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3ub(255,0,0);

  if((*CursorAutoPaintMode) == 1)  CursorPaint();

  if(*CursorColorMode)  CursorColor();
  else
    MapPrint();

  glFinish();
  glutSwapBuffers();

}
