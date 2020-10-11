void TextPrint(string text, Point point, Color color){

  glPushMatrix();

  glColor3d(

    color.get_red(),
    color.get_green(),
    color.get_blue()

  );

  glRasterPos2d(

    point.get_x(),
    point.get_y()

  );

  for(int i = 0; i < text.size(); ++i)

    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);

  glPopMatrix();

}