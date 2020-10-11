#!/bin/bash

data_path="/path/to/Steam/steamapps"
data=( $(ls $data_path | grep -e "app") )

echo "+-----------------------------------------------\
+--------+--------------------------------------------+"

printf '| %-45s\t| %-6s | %-42s |\n' "name" "appid" "installdir"

echo "+-----------------------------------------------\
+--------+--------------------------------------------+"

for i in "${data[@]}"; do

        name=$(cat $data_path/$i | grep -e "\"name\""       | cut -d \" -f 4)
       appid=$(cat $data_path/$i | grep -e "\"appid\""      | cut -d \" -f 4)
  installdir=$(cat $data_path/$i | grep -e "\"installdir\"" | cut -d \" -f 4)

  printf '| %-42s\t| %-6s | %-42s |\n' "$name" "$appid" "$installdir" >> /tmp/steam_list.txt

done

cat /tmp/steam_list.txt | sort
rm /tmp/steam_list.txt

echo "+-----------------------------------------------\
+--------+--------------------------------------------+"