#define DISPLAY_FPS  60

GLint

  DisplayWidth     = 400,
  DisplayHeight    = 400,
  DisplayPixelSize = 8;

void Draw(void);

void DisplayPrint(void){

  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3ub(255,0,0);

  Draw();

  glFinish();
  glutSwapBuffers();

}

void DisplayFPS(int value){

  glutPostRedisplay();
  glutTimerFunc(DISPLAY_FPS, DisplayFPS, 0);

}

void DisplayReshape(int width, int height){

  DisplayWidth  = width;
  DisplayHeight = height;

  glViewport(0, 0, DisplayWidth, DisplayHeight);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(0, DisplayWidth, 0, DisplayHeight, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

}

void DisplayInit(const char *WindowName){

  glutInitWindowSize(DisplayWidth, DisplayHeight);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  glutCreateWindow(WindowName);

  glutTimerFunc(DISPLAY_FPS, DisplayFPS, 0);
  glutReshapeFunc(DisplayReshape);
  glutDisplayFunc(DisplayPrint);

}