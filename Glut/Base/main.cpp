#include <GL/glut.h>

/* g++ <file_name> -lGL -lGLU -lglut */

using namespace std;

void Draw(void);

#include "Data/Display.h"
#include "Data/Graphics.h"
#include "Data/Control.h"

int main(int argc, char *argv[]){

  glutInit(&argc, argv);
  DisplayInit("FreeGLUT");
  ControlInit();
  glutMainLoop();

  return 0;

}

void Draw(void){

}