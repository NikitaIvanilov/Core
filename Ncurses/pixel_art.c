/*

  pixel_art.c - 8-bit ncurses painter.

  Compile:

    gcc -o pixel_art pixel_art.c -lncurses

*/

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

/* Map size */
#define MAP_MAX_Y 20
#define MAP_MAX_X 20 * 2

/* User memory size */
#define USER_MAX 2

/* Color indexes */
#define RED     1
#define CYAN    2
#define BLUE    3
#define BLACK   4
#define WHITE   5
#define GREEN   6
#define YELLOW  7
#define MAGENTA 8

/* Map colors */
#define FRAME WHITE
#define SPACE BLACK

/* Control settings */
#define ARROW_UP    'A'
#define ARROW_DOWN  'B'
#define ARROW_LEFT  'D'
#define ARROW_RIGHT 'C'

#define PALETTE     'q'
#define AUTOPAINT   'a'
#define HIDE_FRAME  'h'
#define SAVE_MAP    's'
#define LOAD_MAP    'l'
#define ENTER       '\n'

char cursor[2] = "<>";  /* Your cursor */
char *filename = "picture.pxrt";  /* Filename to save and load */

char map[MAP_MAX_Y][MAP_MAX_X];  /* Work surface */

void map_save(void);  /* Save your picture to picture.pxrt */
void map_load(void);  /* Load your picture from picture.pxrt */
void map_view(void);  /* Print map */
void map_build(void);  /* Fill map with space and wall */

void hide_frame(void);       /* Hide frame and color poiners */
void install_colors(void);    /* Install init_pairs of colors */
void color_switcher(void);     /* Print color palette and select needed color */
void autopaint_switcher(void);  /* Enable autopaint and disable it */
void set_color_mode(int color);  /* Set color mode for output chars */
void print_colors(int selected);  /* Print color palette with selected color */

int current_color = SPACE;  /* Your default color */

/* Logical variables, can be 1 or 0 */
int pointers  = 1;
int autopaint = 0;

int user[USER_MAX] = {MAP_MAX_Y/2,MAP_MAX_X/2};  /* User axis */

int *user_y = &user[0];  /* Y axis */
int *user_x = &user[1];  /* X axis */

void control(void);  /* Cursor control */

int main(void){

  /* Preparation */
  initscr();
  noecho();
  install_colors();
  map_build();

  /* Work in 3 steps */
  while(1){

    clear();    /* Clear work surface */
    map_view(); /* Print paint surface */
    control();  /* Draw */

  }

  /* End */
  endwin();
  return 0;
}

void map_load(void){

  /* Open load file for reading */
  FILE *file = fopen(filename,"r");

  if(file == 0)  return;

  int i;

  /* Load user data */
  for(i = 0; i < USER_MAX; ++i)  fscanf(file,"|%d|",&user[i]);

  int x,y;

  /* Load map cells */
  for(y = x = 0; y < MAP_MAX_Y; ++x){

    fscanf(file,"|%d|",&map[y][x]);

    if(x < MAP_MAX_X - 1){}
    else{

      x = -1;
      ++y;

    }
  }

  fclose(file);

  /* Reset frame */
  hide_frame();
  hide_frame();

}

void map_save(void){

  /* Open save file for writing */
  FILE *file = fopen(filename,"w");

  if(file == 0)  return;

  int i;

  /* Save user data */
  for(i = 0; i < USER_MAX; ++i)  fprintf(file,"|%d|",user[i]);

  int x,y;

  /* Save map cells */
  for(y = x = 0; y < MAP_MAX_Y; ++x){

    fprintf(file,"|%d|",map[y][x]);

    if(x < MAP_MAX_X - 1){}
    else{

      x = -1;
      ++y;

    }
  }

  fclose(file);

}

void autopaint_switcher(void){

  if(autopaint == 0)  autopaint = 1;
  else
    autopaint = 0;

}

void hide_frame(void){

  int y,x;

  /* Switch pointers */
  if(pointers == 1)  pointers = 0;
  else
    pointers = 1;

  /* Repaint wall chars to space */
  for(y = x = 0; y < MAP_MAX_Y; ++x){

    if(x == 0 || y == 0 || x == MAP_MAX_X - 1 || y == MAP_MAX_Y - 1){

      if(pointers == 1)  map[y][x] = FRAME;
      else
        map[y][x] = SPACE;

    }

    if(x < MAP_MAX_X - 1){}
    else{

      x = -1;
      ++y;

    }

  }

}

void print_colors(int selected){

  int i;

  for(i = 1; i < 9; ++i){

    set_color_mode(i);  /* Enable mode of current color */

    /* If selected color has been finded, put on X char */
    if(i == selected)  printw(" X ");
    else  printw("   ");  /* Else put regular color */

    refresh();

  }

}

void color_switcher(void){

  char c;
  int i = current_color;

  while(1){

    /* Clear and print needed content */
    clear();
    map_view();
    addch('\n');
    print_colors(i);

    /* Press a key */
    c = getch();

    /* Switcher control */
    if(c == ARROW_LEFT  && i > 1)  --i;
    else
    if(c == ARROW_RIGHT && i < 8)  ++i;
    else
    if(c == ENTER)  break;

  }

  /* Set selected color to default */
  current_color = i;

}

void control(void){

  /* Key switcher */
  switch(getch()){

    case ARROW_UP:     if(*user_y > 1)            --(*user_y);  break;

    case ARROW_DOWN:   if(*user_y < MAP_MAX_Y-2)  ++(*user_y);  break;

    case ARROW_LEFT:   if(*user_x > 1)            --(*user_x);  break;

    case ARROW_RIGHT:  if(*user_x < MAP_MAX_X-2)  ++(*user_x);  break;

    case ENTER:        map[*user_y][*user_x] = current_color;   break;

    case HIDE_FRAME:   hide_frame();          break;

    case AUTOPAINT:    autopaint_switcher();  break;

    case PALETTE:      color_switcher();      break;

    case SAVE_MAP:     map_save();            break;

    case LOAD_MAP:     map_load();            break;

    default:  break;

  };

  /* If autopaint enabled, your path will be painted current color */
  if(autopaint == 1)  map[*user_y][*user_x] = current_color;

}

void set_color_mode(int color){

  attron(COLOR_PAIR(color));  /* Set selected color */

}

void install_colors(void){

  /* Start colors and create color pairs */
  start_color();

  init_pair(RED,COLOR_GREEN,COLOR_RED);
  init_pair(CYAN,COLOR_RED,COLOR_CYAN);
  init_pair(BLUE,COLOR_YELLOW,COLOR_BLUE);
  init_pair(BLACK,COLOR_WHITE,COLOR_BLACK);
  init_pair(WHITE,COLOR_BLACK,COLOR_WHITE);
  init_pair(GREEN,COLOR_RED,COLOR_GREEN);
  init_pair(YELLOW,COLOR_BLUE,COLOR_YELLOW);
  init_pair(MAGENTA,COLOR_GREEN,COLOR_MAGENTA);

}

void map_view(void){

  int y,x;

  for(y = x = 0; y < MAP_MAX_Y; ++x){

    /* If current point of map is user point ... */
    if(x == *user_x && y == *user_y){

      /* ... Turn on User color mode and print cursor */
      set_color_mode(map[*user_y][*user_x]);
      addch(cursor[0]);
      addch(cursor[1]);

    }
    else{

      /* If pointers is enable and coordinates meet the condition, print color pointers */
      if(pointers == 1 && x == *user_x && (y == 0 || y == MAP_MAX_Y-1))  set_color_mode(current_color);
      else
      if(pointers == 1 && y == *user_y && (x == 0 || x == MAP_MAX_X-1))  set_color_mode(current_color);
      else  set_color_mode(map[y][x]);  /* Else print default color */

      /* Width of one map cell */
      addch(' ');
      addch(' ');

    }

    if(x < MAP_MAX_X - 1){}
    else{

      x = -1;
      ++y;
      addch('\n');

    }

  }

}

void map_build(void){

  int y,x;

  for(y = x = 0; y < MAP_MAX_Y; ++x){

    /* Draw walls */
    if(x == 0 || y == 0 || x == MAP_MAX_X - 1 || y == MAP_MAX_Y - 1)
      map[y][x] = FRAME;
    else
      map[y][x] = SPACE;  /* Else draw space */

    if(x < MAP_MAX_X - 1){}
    else{

      x = -1;
      ++y;

    }

  }

}

