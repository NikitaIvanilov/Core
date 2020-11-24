#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#define MAP_SIZE   4

#define MAX_VALUE  1000  /* Value of map cell, when game ending */

#define BUTTON_FORWARD 'w'
#define BUTTON_BACK    's'
#define BUTTON_LEFT    'a'
#define BUTTON_RIGHT   'd'
#define BUTTON_INFO    'i'
#define BUTTON_QUIT    'q'

int map[MAP_SIZE][MAP_SIZE];

void map_clear(void);
void map_print(void);
void map_random(void);
void map_print_cell(int map_cell);

int game_over = 0;

int statistic_steps = 0;
int statistic_max_number = 0;
int statistic_tns = 0;  /* Total Number Sum */

void print_statistic(void);
void print_info(void);

void wave_down(void);
void wave_up(void);
void wave_right(void);
void wave_left(void);
void wave_control(void);

int random_number(int from, int to);

int main(void){

  srand(time(0));
  map_clear();

  initscr();  /* ncurses start */

  while(1){

    map_print();

    if(game_over == 1)  break;

    wave_control();
    map_random();

  }

  print_statistic();

  endwin();  /* ncurses stop */
  return 0;

}

void print_info(void){

  printw("\n\n");

  printw(" > Forward: %c\n", BUTTON_FORWARD);
  printw(" > Back:    %c\n", BUTTON_BACK);
  printw(" > Left:    %c\n", BUTTON_LEFT);
  printw(" > Right:   %c\n", BUTTON_RIGHT);
  printw(" > Quit:    %c\n", BUTTON_QUIT);
  printw(" > Info:    %c\n", BUTTON_INFO);

  printw("\nPress any key to continue ...\n\n");

  getch();

}

void print_statistic(void){

  map_print();

  printw("\nGame Over!\n\n");

  printw(" > Max number - %d\n", statistic_max_number);
  printw(" > Steps      - %d\n", statistic_steps);
  printw(" > TNS        - %d\n", statistic_tns);

  printw("\nPress Enter to exit ...\n\n");

  while(getch() != '\n'){}

}

void map_random(void){

  int x = random_number(0,MAP_SIZE);
  int y = random_number(0,MAP_SIZE);

  if(map[y][x] == 0)  map[y][x] = random_number(0,MAP_SIZE);

}

int random_number(int min, int max){

  int k = max - min;

  while((k % 2) != 0)  --k;

  int i = rand();  /* Get random number */

  while(1){

    if(i > max)  i /= k;
    else
    if(i < min)  i *= k;
    else
      break;

  };

  return i;

}

void wave_control(void){

  int i;

  switch(getch()){

    case BUTTON_FORWARD:  for(i = 0; i < MAP_SIZE; ++i)  wave_up();
    break;

    case BUTTON_BACK:     for(i = 0; i < MAP_SIZE; ++i)  wave_down();
    break;

    case BUTTON_LEFT:     for(i = 0; i < MAP_SIZE; ++i)  wave_left();
    break;

    case BUTTON_RIGHT:    for(i = 0; i < MAP_SIZE; ++i)  wave_right();
    break;

    case BUTTON_INFO:     print_info();
    break;

    case BUTTON_QUIT:     game_over = 1;
    break;

    default:  break;

  };

  /*  Statistic block -> start  */

  ++statistic_steps;

  /*  Statistic block -> end  */

}

void wave_left(void){

  int x,y;

  for(y = 0; y < MAP_SIZE; ++y){

    for(x = (MAP_SIZE - 1); x > 0; --x){

      if(map[y][x - 1] == 0){

        map[y][x - 1] = map[y][x];
        map[y][x] = 0;

      }
      else if(map[y][x - 1] == map[y][x]){  /* Action - left - 1 */

        map[y][x - 1] = map[y][x] + 1;
        map[y][x] = 0;

      }

    }  /* x - cucle */

  }  /* y - cucle */

}

void wave_right(void){

  int x,y;

  for(y = 0; y < MAP_SIZE; ++y){

    for(x = 0; x < (MAP_SIZE - 1); ++x){

      if(map[y][x + 1] == 0){

        map[y][x + 1] = map[y][x];
        map[y][x] = 0;

      }
      else if(map[y][x + 1] == map[y][x]){  /* Action - right - 2 */

        map[y][x + 1] = map[y][x] + 1;
        map[y][x] = 0;

      }

    }  /* x - cucle */

  }  /* y - cucle */

}

void wave_up(void){

  int x,y;

  for(x = 0; x < MAP_SIZE; ++x){

    for(y = (MAP_SIZE - 1); y > 0; --y){

      if(map[y - 1][x] == 0){

        map[y - 1][x] = map[y][x];
        map[y][x] = 0;

      }
      else if(map[y - 1][x] == map[y][x]){  /* Action - up - 3 */

        map[y - 1][x] = map[y][x] + 1;
        map[y][x] = 0;

      }

    }  /* y - cucle */

  }  /* x - cycle*/

}

void wave_down(void){

  int x,y;

  for(x = 0; x < MAP_SIZE; ++x){

    for(y = 0; y < (MAP_SIZE - 1); ++y){

      if(map[y + 1][x] == 0){

        map[y + 1][x] = map[y][x];
        map[y][x] = 0;

      }
      else if(map[y + 1][x] == map[y][x]){  /* Action - down - 4 */

        map[y + 1][x] = map[y][x] + 1;
        map[y][x] = 0;

      }

    }  /* y - cucle */

  }  /* x - cycle*/

}

void map_clear(void){

  int x,y;

  for(x = 0; x < MAP_SIZE; ++x){

    for(y = 0; y < MAP_SIZE; ++y)  map[y][x] = 0;

  }

}

void map_print(void){

  clear();
  printw("\n\n");

  int x,y;

  /* Statistic block -> start */

  statistic_tns = 0;

  /* Statistic block -> start */

  for(y = 0; y < MAP_SIZE; ++y){

    for(x = 0; x < MAP_SIZE; ++x)  map_print_cell(map[y][x]);
    addch('\n');

  }

}

void map_print_cell(int map_cell){

  int separator;

  if(map_cell > MAX_VALUE)  game_over = 1;

  if(map_cell < 10)         separator = 6;
  else
  if(map_cell < 100)        separator = 5;
  else
  if(map_cell < 1000)       separator = 4;

  while(separator > 0){

    addch(' ');
    --separator;

  }

  printw("%d",map_cell);

  /*  Statistic block -> start  */

  if(statistic_max_number < map_cell)  statistic_max_number = map_cell;

  statistic_tns += map_cell;

  /*  Statistic block -> end  */

}
