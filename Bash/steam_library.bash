#!/bin/bash

installdir=( $(cat appmanifest/* | grep -e "installdir" | cut -d \" -f 4 | tr " " "#") )
     appid=( $(cat appmanifest/* | grep -e "appid"      | cut -d \" -f 4) )
      name=( $(cat appmanifest/* | grep -e "name"       | cut -d \" -f 4 | tr " " "#") )

function strip {

  for (( i = 0; i < 113; ++i )); do

    if   (( i ==   0 )); then printf "+"
    elif (( i ==  48 )); then printf "+"
    elif (( i ==  61 )); then printf "+"
    elif (( i == 112 )); then printf "+"
    else                      printf "-"; fi

  done

  printf "\n"

}

strip

for (( i = 0; i < "${#installdir[@]}"; ++i )); do

  printf "| %-45.45s | %-10.10s | %-45.45s\t|\n" ${installdir[$i]} ${appid[$i]} ${name[$i]} | tr "#" " "

done

strip