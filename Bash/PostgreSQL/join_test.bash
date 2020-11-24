#!/bin/bash
#
# JOIN Test:
#
#  Creates three databases
#  and select with JOIN.
#
# Usage:
#
#  --create
#  --select [ --ammo, --settings, --full]
#

database=weapon_db

table1=weapon
table2=weapon_ammo
table3=weapon_settings

function select_full {

psql -c "\connect $database;" \
\
     -c "SELECT weapon.name,              \
                weapon_settings.damage,   \
                weapon_settings.speed,    \
                weapon_settings.accuracy, \
                weapon_ammo.max,          \
                weapon_ammo.magazine      \
\
         FROM weapon                                            \
         JOIN weapon_settings ON weapon.id = weapon_settings.id \
         JOIN weapon_ammo     ON weapon.id = weapon_ammo.id;"   \
\

}

function select_settings {

psql -c "\connect $database;" \
\
     -c "SELECT weapon.name,             \
                weapon_settings.damage,  \
                weapon_settings.speed,   \
                weapon_settings.accuracy \
\
         FROM weapon                                              \
         JOIN weapon_settings ON weapon.id = weapon_settings.id;" \
\

}

function select_ammo {

psql -c "\connect $database;" \
\
     -c "SELECT weapon.name,         \
                weapon_ammo.max,     \
                weapon_ammo.magazine \

         FROM weapon                                      \
         JOIN weapon_ammo ON weapon.id = weapon_ammo.id;" \
\

}

function create {

psql \
\
    -c "DROP   DATABASE $database;" \
    -c "CREATE DATABASE $database;" \
    -c "\connect $database"         \
\
    -c "CREATE TABLE $table1(id   integer PRIMARY KEY, \
                             name text);"              \
\
    -c "CREATE TABLE $table2(id       integer REFERENCES weapon(id), \
                             max      integer,                       \
                             magazine integer);"                     \
\
    -c "CREATE TABLE $table3(id       integer REFERENCES weapon(id), \
                             damage   integer,                       \
                             speed    integer,                       \
                             accuracy integer);"                     \
\
    -c "INSERT INTO $table1(id, name) VALUES(0, 'Rifle'          ),  \
                                            (1, 'Sniper Rifle'   ),  \
                                            (2, 'Machine Gun'    ),  \
                                            (3, 'Shotgun'        ),  \
                                            (4, 'Pistol'         ),  \
                                            (5, 'Heavy Pistol'   ),  \
                                            (6, 'Rocket Launcher');" \
\
     -c "INSERT INTO $table2(id, max, magazine) VALUES(0, 120,  30),  \
                                                      (1,  30,  10),  \
                                                      (2, 300, 100),  \
                                                      (3,  30,   8),  \
                                                      (4,  45,   6),  \
                                                      (5,  16,   5),  \
                                                      (6,   8,   1);" \
\
     -c "INSERT INTO $table3(id, damage, speed, accuracy) VALUES(0,  25, 10,  70),  \
                                                                (1,  50,  2, 100),  \
                                                                (2,  35, 25,  45),  \
                                                                (3,  45,  5,  35),  \
                                                                (4,  15,  7,  50),  \
                                                                (5,  20,  5,  35),  \
                                                                (6, 100,  2,  80);" \
\

}

if   [[ $1 == "--create" ]]; then create
elif [[ $1 == "--select" ]]; then

  if   [[ $2 == "--ammo"     ]]; then select_ammo
  elif [[ $2 == "--settings" ]]; then select_settings
  elif [[ $2 == "--full"     ]]; then select_full
  fi

fi