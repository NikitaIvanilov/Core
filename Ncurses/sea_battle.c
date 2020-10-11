/*

  sea_battle - is a guessing game for two players.

  It is played on ruled grids (paper or board) on which each players fleet of ships (including battleships) are
  marked. The locations of the fleets are concealed from the other player. Players alternate turns calling
  "shots" at the other player's ships, and the objective of the game is to destroy the opposing player's fleet.

  Battleship is known worldwide as a pencil and paper game which dates from World War I. It was published by
  various companies as a pad-and-pencil game in the 1930s, and was released as a plastic board game by Milton
  Bradley in 1967. The game has spawned electronic versions, video games, smart device apps and a film.

  In the version of this game you are fighting against a computer player.

  How to play:

    1. Select ships.
    2. Locate ships.

    3. Find and destroy enemy ships.

  How to control the cursor:

    wasd - walking on the map
    e    - put ship and attack

  Compilation:

    gcc -o sea_battle sea_battle.c -lncurses

  Note:

    You can configure game in Sizes, Hotkeys, Oject chars blocks.

*/

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

/* #################### */
/*     Do not change    */

#define INFINITY        1
#define SENDING_TO_SEA  0

#define VERTICAL       'v'
#define HORIZONTAL     'h'

/* #################### */
/*      Oject chars     */

#define WALL           '#'
#define SPACE          ' '
#define PLAYER         'P'
#define ENEMY          'E'

/* #################### */
/*        Hotkeys       */

#define MOVE_FORWARD   'w'
#define MOVE_BACK      's'
#define MOVE_LEFT      'a'
#define MOVE_RIGHT     'd'

#define CONTEXT_ACTION 'e'

/* #################### */
/*         Sizes        */

#define MAX_SHIPS       3

#define SHORT_SHIP      1
#define MEDIUM_SHIP     3
#define LONG_SHIP       5

#define MAX_X           20
#define MAX_Y           20

/* #################### */

int ships_pack[MAX_SHIPS];

int ships_pack_health_player = 0;
int ships_pack_health_enemy  = 0;

char map[MAX_X][MAX_Y];

int player[3] = {MAX_X/2,MAX_Y/2,0};

  int *player_x = &player[0];
  int *player_y = &player[1];

  int *player_current_ship = &player[2];

int enemy[3] = {MAX_X/2,MAX_Y/2,0};

  int *enemy_x            = &enemy[0];
  int *enemy_y            = &enemy[1];

  int *enemy_current_ship = &enemy[2];

int turn              = ENEMY;
int ship_arrange_mode = 1;
int ships_selected    = 0;

void ship_list   (void);
void ship_select (void);
void map_build   (void);

void ship_arrange_for         (char player_or_enemy);
void map_view_for             (char player_or_enemy);
void control_for              (char player_or_enemy,char move_direction);

int  make_vertical_ship_for   (char player_of_enemy,int  number_from_the_ships_pack);
int  make_horizontal_ship_for (char player_of_enemy,int  number_from_the_ships_pack);

int  random_number (int begin,int end, int keynumber);
char random_action (void);

int main(void){

srand(time(0));

map_build();
initscr();

int i;

ship_select();

/*  count health based on type ships, the more cells in ships the more health  */
for(i = 0; i < MAX_SHIPS;++i){

  ships_pack_health_player += ships_pack[i];
  ships_pack_health_enemy  += ships_pack[i];

}

/*  your turn to locate ships  */
while(ship_arrange_mode){

  clear();

  map_view_for(PLAYER);
  control_for(PLAYER,getch());

  if(*player_current_ship == MAX_SHIPS)  break;

}

/*  enemy turn to locate ships  */
while(ship_arrange_mode)  control_for(ENEMY,random_action());

/*  game run, while you are alive  */
while(ships_pack_health_player > 0 && ships_pack_health_enemy > 0){

  clear();

  map_view_for(PLAYER);

  if(turn == PLAYER)
    control_for(PLAYER,getch());
  else
    control_for(ENEMY,random_action());

}

clear();
map_view_for(PLAYER);

/*  result  */
if(ships_pack_health_player == 0)  printw("\nYou are destroyed.\n");
else  printw("\nYou won.\n");
getch();

endwin();

return 0;
}

/*
    arrange ships for one of you

    if you are arranger, you will manual locate ship
    else
    if arrange is enemy, arranging will automatical.

*/
void ship_arrange_for(char who){

  int i;

  int num_ship;
  int num_location;

  if(who == PLAYER){

    clear();
    ship_list();

    num_ship = *player_current_ship;

    printw("\n How locate your ship?\n");
    printw(" 1: Vertical 2: Horizontal 0: Exit\n\n");

    scanw("%d",&num_location);

    switch(num_location){

      case 0:  return;

      case 1:

        make_vertical_ship_for(PLAYER,num_ship);

      break;

      case 2:

        make_horizontal_ship_for(PLAYER,num_ship);

      break;

      default:  ship_arrange_for(who);  break;

    };

  }
  else
  if(who == ENEMY){

    if(ship_arrange_mode){

      i = random_number(0,10,40);

      if(i != 0 && i < 3 && i != 10){
        if(make_vertical_ship_for(ENEMY,*enemy_current_ship) == 1)  ++(*enemy_current_ship);
        if(*enemy_current_ship >= MAX_SHIPS)  ship_arrange_mode = 0;
      }
      else
      if(i != 0 && i > 7 && i != 10){
        if(make_horizontal_ship_for(ENEMY,*enemy_current_ship) == 1) ++(*enemy_current_ship);
        if(*enemy_current_ship >= MAX_SHIPS)  ship_arrange_mode = 0;
      }
    }
    else
    if(map[*enemy_y][*enemy_x] == PLAYER){

      --ships_pack_health_player;
      map[*enemy_y][*enemy_x] = '+';
      turn = PLAYER;

    }
  }
}

/*  if needed space for the ship is free, then locate it vertical  */
int make_vertical_ship_for(char who,int num_ship){

  if(ships_pack[num_ship] == 0)  return 0;

  int clear = 1;
  int i;

  int *user_y;
  int *user_x;

  if(who == PLAYER){

    user_x = player_x;
    user_y = player_y;

  }
  else
  if(who == ENEMY){

    user_x = enemy_x;
    user_y = enemy_y;

  }

  int point_A = ((*user_y) - (ships_pack[num_ship]-1)/2);
  int point_B = ((*user_y) + (ships_pack[num_ship]-1)/2);

  for(i = point_A-1;i <= point_B+1;++i){

    if(map[i][*user_x+1] != SPACE){

      clear = 0;
      break;

    }

    if(map[i][*user_x] != SPACE){

      clear = 0;
      break;

    }

    if(map[i][*user_x-1] != SPACE){

      clear = 0;
      break;

    }

  }

  if(clear == 1){

  for(i = point_A;i <= point_B;++i)  map[i][*user_x] = who;
  if(who == PLAYER)  ++(*player_current_ship);

  }

  return clear;

}

/*  if needed space for the ship is free, then locate it horizontal  */
int make_horizontal_ship_for(char who,int num_ship){

  if(ships_pack[num_ship] == 0)  return 0;

  int clear = 1;
  int i;

  int *user_y;
  int *user_x;

  if(who == PLAYER){

    user_x = player_x;
    user_y = player_y;

  }
  else
  if(who == ENEMY){

    user_x = enemy_x;
    user_y = enemy_y;

  }

  int point_A = ((*user_x) - (ships_pack[num_ship]-1)/2);
  int point_B = ((*user_x) + (ships_pack[num_ship]-1)/2);

  for(i = point_A-1;i <= point_B+1;++i){

    if(map[*user_y+1][i] != SPACE){

      clear = 0;
      break;

    }

    if(map[*user_y][i] != SPACE){

      clear = 0;
      break;

    }

    if(map[*user_y-1][i] != SPACE){

      clear = 0;
      break;

    }

  }

  if(clear == 1){

  for(i = point_A;i <= point_B;++i)  map[*user_y][i] = who;
  if(who == PLAYER)  ++(*player_current_ship);

  }

  return clear;

}

/*  function for ship selection  */
void ship_select(void){

  int current_ship = 0;
  int i;

while(current_ship < MAX_SHIPS){

  clear();

  addch('\n');

  printw(" Select your ships, which you want to use.\n");
  printw(" You can select - %d ships\n",MAX_SHIPS - current_ship);

  addch('\n');

  printw(" 1: Long ship\n");
  printw(" 2: Medium ship\n");
  printw(" 3: Short ships\n");

  addch('\n');

  scanw("%d",&i);

  switch(i){

    case 1:  ships_pack[current_ship] = LONG_SHIP;    break;

    case 2:  ships_pack[current_ship] = MEDIUM_SHIP;  break;

    case 3:  ships_pack[current_ship] = SHORT_SHIP;   break;

    default: --current_ship;                          break;

  };

  ++current_ship;

}

  ships_selected = 1;

}

/*  print list of ships  */
void ship_list(void){

  int i;

  printw("\n Your ship list\n\n");

  for(i = 0;i < MAX_SHIPS;++i){

    switch(ships_pack[i]){

      case LONG_SHIP:    printw(" %d: Long ship"  ,i+1);  break;

      case MEDIUM_SHIP:  printw(" %d: Medium ship",i+1);  break;

      case SHORT_SHIP:   printw(" %d: Short ship" ,i+1);  break;

      default:           printw(" Empty");                break;

    };

    if(i == *player_current_ship)  printw("\t <- current ship\n");
    else  addch('\n');

  }

  addch('\n');

}

/*  who use this function and where he want to go  */
void control_for(char who,char direction){

  switch(direction){

    case MOVE_FORWARD:

      if(who == PLAYER && map[*player_y-1][*player_x] != WALL)  *player_y -= 1;
      else
      if(who == ENEMY  && map[*enemy_y-1][*enemy_x]   != WALL)  *enemy_y -= 1;

    break;

    case MOVE_BACK:

      if(who == PLAYER && map[*player_y+1][*player_x] != WALL)  *player_y += 1;
      else
      if(who == ENEMY  && map[*enemy_y+1][*enemy_x]   != WALL)  *enemy_y += 1;

    break;

    case MOVE_RIGHT:

      if(who == PLAYER && map[*player_y][*player_x+1] != WALL)  *player_x += 1;
      else
      if(who == ENEMY  && map[*enemy_y][*enemy_x+1]   != WALL)  *enemy_x += 1;

    break;

    case MOVE_LEFT:

      if(who == PLAYER && map[*player_y][*player_x-1] != WALL)  *player_x -= 1;
      else
      if(who == ENEMY  && map[*enemy_y][*enemy_x-1]   != WALL)  *enemy_x -= 1;

    break;

    case CONTEXT_ACTION:

      if(who == PLAYER){

        if(ships_selected == 0)     ship_select();
        else
        if(ship_arrange_mode == 1)  ship_arrange_for(PLAYER);
        else{

          if(map[*player_y][*player_x] == ENEMY){

            map[*player_y][*player_x] = '+';
            --ships_pack_health_enemy;

          }
          else
          if(map[*player_y][*player_x] == SPACE)
            map[*player_y][*player_x] = '-';

        }

      }
      else if(who == ENEMY){

        if(ship_arrange_mode == 1)  ship_arrange_for(ENEMY);
        else
        if(map[*enemy_y][*enemy_x] == PLAYER)  map[*enemy_y][*enemy_x] = '+';

      }

      if(who == PLAYER)  turn = ENEMY;
      else
      if(who == ENEMY)   turn = PLAYER;

    break;

    default:

    break;

  };

}

/*  if who is PLAYER then you can not see enemy ships  */
void map_view_for(char who){

  int x,y;
  char space = SPACE;

  for(x = y = 0;y < MAX_Y;++x){

    if(who == ENEMY){

      if(*enemy_x == x && *enemy_y == y)  space = '>';
      else
      if(space == '>')  space = '<';
      else
        space = SPACE;

      printw("%c%c",space,map[y][x]);

    }
    else
    if(who == PLAYER){

      if(*player_x == x && *player_y == y)  space = '>';
      else
      if(space == '>')  space = '<';
      else
        space = SPACE;

      if(map[y][x] == ENEMY)  printw("%c%c",space,space);
      else
        printw("%c%c",space,map[y][x]);

    }

    if(x == MAX_X - 1){

      x = -1;
      ++y;
      addch('\n');

    }

  }
  addch('\n');
}

/*  build walls around map  */
void map_build(void){

  int x,y;

  for(x = y = 0;y < MAX_Y;++x){

    if(x == 0 || y == 0 || x == MAX_X - 1 || y == MAX_Y - 1)
      map[y][x] = WALL;
    else
      map[y][x] = SPACE;

    if(x == MAX_X - 1){

      x = -1;
      ++y;

    }
  }

}

/*
    function for get random numbers
    it works in between begin and end number

    keynumber if coefficent, default for me - 40
    do not use so large number, like a 500,1000

*/

int random_number(int begin,int end,int keynumber){

  int i = rand();

  while(INFINITY){

    if(i > end)   i = i / keynumber;
    else
    if(i < begin) i = i * keynumber;
    else
      break;

  }

return i;

}

/*  function for enemy actions in game  */
char random_action(void){

  char c;

  if(map[*enemy_y][*enemy_x] == PLAYER && ship_arrange_mode == 0){

    --ships_pack_health_player;
    map[*enemy_y][*enemy_x] = '+';
    turn = PLAYER;

  }
  else
  switch(random_number(0,10,40)){

    case 1:  c = MOVE_FORWARD;    break;

    case 2:  c = MOVE_LEFT;       break;

    case 3:  c = MOVE_BACK;       break;

    case 4:  c = MOVE_RIGHT;      break;

    case 5:  c = CONTEXT_ACTION;  break;

    case 6:  c = MOVE_RIGHT;      break;

    case 7:  c = MOVE_BACK;       break;

    case 8:  c = MOVE_LEFT;       break;

    case 9:  c = MOVE_FORWARD;    break;

    default:

      c = random_action();

    break;

  };

  return c;

}
