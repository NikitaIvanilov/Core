/*

  Cave Runner

    Walk around the cave, collect money, pickaxes and fight for your life.

  Default controls:

    w - move forward
    a - move left
    s - move back
    d - move right

    e - context action
    1 - save game
    2 - load game

    Note: After pressing e, you must select direction with wasd.

  Requirements: Ncurses.

  Compile:

    gcc -o cave_runner cave_runner.c -lncurses

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>  /* -lncurses */

/* Service */

#define INFINITY 1
#define USER_MAX 7

/* You can change this */

#define CLEAR_MAP 0           /* 1 */
#define CREATOR_MODE 0        /* 2 */

#define TIME_TO_DIE_CYCLE 10  /* 3 */

#define MAP_MAX_X 20          /* 4 */
#define MAP_MAX_Y 20          /* 5 */

/*

  1. CLEAR_MAP [0 - 1] - If set 1 then fill map only free space without other objects.
  2. CREATOR_MODE [0 - 1] - If set 1 then you can place any char symbols on map, else set 0 you can interact with environment.

  3. TIME_TO_DIE_CYCLE [0 - ...] - This is period of time, whem you lose 1 health point.

  4. MAP_MAX_X [0 - ...] - Set map size by axis X.
  5. MAP_MAX_Y [0 - ...] - Set map size by axis Y.

  Even number for map size is better.

  How to count map cells.

    MAP_MAX_X * MAP_MAX_Y = Square

    Square / 4 = Free cells

    Square / 2 = Full map with walls

*/

/* Chars */

#define WALL   '#'  /* Unbreakable wall */
#define STONE  '@'  /* Breakable wall */
#define SPACE  ' '  /* Free space when you can walk */
#define PLAYER 'P'  /* Your play char */

#define LEVER_ON  '+'  /* Level is turning on */
#define LEVER_OFF '-'  /* Level is turning off */

#define MONEY     '$'  /* Shopping resource */
#define HEALTH    'o'  /* Support your heartbeat */
#define PICKAXE   '^'  /* Tool for STONE breaking */

/* Costs */

#define HEALTH_COST  10
#define PICKAXE_COST 5

/* Buttons */

#define BUTTON_BUY 'b'  /* Buy any items */

#define BUTTON_SAVE '1'  /* Save game in file */
#define BUTTON_LOAD '2'  /* Load game from file */

#define BUTTON_FORWARD 'w'  /* Button for move forward */
#define BUTTON_BACK    's'  /* Button for move back */
#define BUTTON_LEFT    'a'  /* Button for move left */
#define BUTTON_RIGHT   'd'  /* Button for move right */

#define BUTTON_CONTEXT_ACTION 'e'  /* Button for context action */

/* Map */

  char map[MAP_MAX_Y][MAP_MAX_X];

  void map_view(void);  /* Print map */
  void map_build(void);  /* Build field and fence */
  void map_build_inside(char *object);  /* Fill map objects of environment */

  void map_save(void);  /* Save current map */
  void map_load(void);  /* Load saved map */

  char map_name[128] = "Default";

/* User */

  int user[USER_MAX] = {2,2,0,1,0,0,0};

  int *user_x = &user[0];
  int *user_y = &user[1];

  int *user_money   = &user[2];
  int *user_health  = &user[3];
  int *user_pickaxe = &user[4];

  void user_control(void); /* Control */
  void user_title(void);  /* Top title with useful numbers */

  void context_action_tab(char *object);  /* Table of all object, you can interact with */
  void context_action(void);  /* Direction of you action */

  char direction;

/* Time */

  int *time_global = &user[5];
  int *time_to_die = &user[6];

/* Item */

  char item_select(void);
  void item_buy(char item);

int main(void){

  srand(time(0));
  map_build();
  initscr();

  while(*user_health > 0){

    clear();
    user_title();
    map_view();

    user_control();

  }

  endwin();

  printf("\n Game Over!\n\n");

return 0;
}

char item_select(void){

  int i;

  addch('\n'); /* Print menu */

  printw(" 1.Health  - %d\n", HEALTH_COST);
  printw(" 2.Pickaxe - %d\n", PICKAXE_COST);

  addch('\n');

  scanw("%d",&i);  /* Select object */

  if(i == 1)  return HEALTH;
  else
  if(i == 2)  return PICKAXE;

return 0;
}

void item_buy(char item){

  switch(item){

    case HEALTH:

      if((*user_money - HEALTH_COST) >= 0){

        ++(*user_health);
        *user_money -= HEALTH_COST;

      }

    break;

    case PICKAXE:

      if((*user_money - PICKAXE_COST) >= 0){

        ++(*user_pickaxe);
        *user_money -= PICKAXE_COST;

      }

    break;

    default:  break;

  };

}

void map_build_inside(char *object){

  int random_number = rand();

  while(INFINITY){

    if(random_number > 7)  random_number /= 3;
    else
    if(random_number < 0)  random_number *= 3;
    else
      break;

  }

  switch(random_number){

    case 0:  *object = WALL;  break;

    case 1:  *object = SPACE;  break;

    case 2:  *object = STONE;  break;

    case 3:  *object = MONEY;  break;

    case 4:  *object = WALL;  break;

    case 5:  *object = PICKAXE;  break;

    case 6:  *object = SPACE;  break;

    case 7:  *object = HEALTH;  break;

  };

}

void map_load(void){

  char input_line[16];
  int i;

  printw(" Write File name to load.\n > ");

  for(i = 0; i < 16; ++i){

    input_line[i] = getch();

    if(input_line[i] == ERR) --i;  /* halfdelay deactivator */
    else
    if(input_line[i] == '\n'){

      input_line[i] = 0;
      break;

    }
  }

  if(input_line[0] == 0){  /* Press enter in empty line to canceled operation */

    printw(" Canceled.\n");
    getch();

    return;

  }

  char *name      = input_line;
  FILE *file_name = fopen(name,"r");

  if(file_name == 0){

    printw(" File not found.\n");
    getch();

    return;

  }

  for(i = 0; i < USER_MAX; ++i)  fscanf(file_name,"%d|",&user[i]);

  int x,y;

  for(x = y = 1; y < MAP_MAX_Y; ++x){

    fscanf(file_name,"%d|",&map[y][x]);

    if(x == MAP_MAX_X-1){

      ++y;
      x = 0;

    }
  }

  strcpy(map_name,input_line);

  fclose(file_name);

}

void map_save(void){

  char input_line[16];
  int i;

  printw(" Write File name to save.\n > ");

  for(i = 0; i < 16; ++i){

    input_line[i] = getch();

    if(input_line[i] == ERR) --i;  /* halfdelay deactivator */
    else
    if(input_line[i] == '\n'){

      input_line[i] = 0;
      break;

    }
  }

  if(input_line[0] == 0){  /* Press enter in empty line to canceled operation */

    printw(" Canceled.\n");
    getch();

    return;

  }

  char *name       = input_line;
  char command[64] = "echo > ";

  strcat(command,name);
  system(command);

  FILE *file_name = fopen(name,"w");

  if(file_name == 0){

    printw(" Can not write in file.\n");
    return;

  }

  for(i = 0; i < USER_MAX; ++i)  fprintf(file_name,"%d|",user[i]);

  int x,y;

  for(x = y = 1; y < MAP_MAX_Y; ++x){

    fprintf(file_name,"%d|",map[y][x]);

    if(x == MAP_MAX_X-1){

      ++y;
      x = 0;

    }
  }

  fclose(file_name);

}

void user_title(void){

  addch('\n');

  printw(" %d - time |",*time_global);
  printw(" %s",map_name);

  addch('\n');
  addch('\n');

  printw(" %d - health |",*user_health);
  printw(" %d - money |",*user_money);
  printw(" %d - pickaxe",*user_pickaxe);

  addch('\n');
  addch('\n');

}

void context_action_tab(char *object){

  if(CREATOR_MODE == 1){

    clear();

    user_title();
    map_view();

    addch('\n');

    printw(" Put any char.");

    addch('\n');
    addch('\n');

    *object = getch();

    return;

  }

  switch(*object){  /* Object use */

    case LEVER_ON:   *object = LEVER_OFF;  break;

    case LEVER_OFF:  *object = LEVER_ON;   break;

    case MONEY:    ++(*user_money);    *object = SPACE;  break;

    case HEALTH:   ++(*user_health);   *object = SPACE;  break;

    case PICKAXE:  ++(*user_pickaxe);  *object = SPACE;  break;

    case STONE:

      if(*user_pickaxe > 0){

        --(*user_pickaxe);
        *object = SPACE;

      }

    break;

    default:  break;

  };

}

void user_control(void){

  halfdelay(10);

  direction = getch();

  switch(direction){  /* User control */

    case BUTTON_BUY:  item_buy(item_select());  break;

    case BUTTON_SAVE:  map_save();  break;

    case BUTTON_LOAD:  map_load();  break;

    case BUTTON_FORWARD:  if(map[*user_y-1][*user_x] == SPACE) --(*user_y);  break;

    case BUTTON_BACK:     if(map[*user_y+1][*user_x] == SPACE) ++(*user_y);  break;

    case BUTTON_LEFT:     if(map[*user_y][*user_x-1] == SPACE) --(*user_x);  break;

    case BUTTON_RIGHT:    if(map[*user_y][*user_x+1] == SPACE) ++(*user_x);  break;

    case BUTTON_CONTEXT_ACTION:  context_action();  break;

  };

  ++(*time_global);

  ++(*time_to_die);

  if(*time_to_die == TIME_TO_DIE_CYCLE && CREATOR_MODE == 0){

    --(*user_health);  /* Value of subtracting, default -1 in die cycle */
    *time_to_die = 0;

  }

}

void context_action(void){

  halfdelay(100);

  direction = getch();

  switch(direction){  /* Send object to context_action_tab and work with it */

    case BUTTON_FORWARD:  context_action_tab(&map[*user_y-1][*user_x]);  break;

    case BUTTON_BACK:     context_action_tab(&map[*user_y+1][*user_x]);  break;

    case BUTTON_LEFT:     context_action_tab(&map[*user_y][*user_x-1]);  break;

    case BUTTON_RIGHT:    context_action_tab(&map[*user_y][*user_x+1]);  break;

    case BUTTON_CONTEXT_ACTION:

      clear();
      user_title();
      map_view();

      addch('\n');
      printw(" Select object.");
      addch('\n');

      context_action();

    break;

  };

}

void map_view(void){

  int x,y;

  for(x = y = 1; y < MAP_MAX_Y; ++x){

    if(x == *user_x && y == *user_y)  printw(" %c",PLAYER);
    else
      printw(" %c",map[y][x]);

    if(x == MAP_MAX_X-1){

      ++y;
      x = 0;

      printw("\n");

    }
  }
}

void map_build(void){

  int x,y;

  for(x = y = 1; y < MAP_MAX_Y; ++x){

    if(x == 1 || y == 1 || x == MAP_MAX_X-1 || y == MAP_MAX_Y-1)
      map[y][x] = WALL;
    else{

      if(CLEAR_MAP == 1)  map[y][x] = SPACE;
      else
        map_build_inside(&map[y][x]);

    }

    if(x == MAP_MAX_X-1){

      ++y;
      x = 0;

    }
  }
}

