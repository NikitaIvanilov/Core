#define BUTTON_ESC   27
#define BUTTON_ENTER 13

void ControlKeyboard(unsigned char key, int x, int y){

  switch(key){

    case GLUT_KEY_UP:
    break;

    case GLUT_KEY_DOWN:
    break;

    case GLUT_KEY_RIGHT:
    break;

    case GLUT_KEY_LEFT:
    break;

  };

}

void ControlSpecial(int key, int x, int y){

  switch(key){

    case BUTTON_ESC:  exit(0);
    break;

  };

}

void ControlInit(void){

  glutKeyboardFunc(ControlKeyboard);
  glutSpecialFunc (ControlSpecial);

}