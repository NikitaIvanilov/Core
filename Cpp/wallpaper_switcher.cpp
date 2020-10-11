#include <iostream>
#include <string>
#include <vector>

//  Type 1, if you want to see how it will work
#define DEBUG 0

using namespace std;

string path_folder = "/etc/xdg/openbox/wallpapers/";
string path_temp   = "/tmp/wallpaper_switcher";
string wallpaper_loader = "feh --bg-center --no-fehbg";

vector<string> wallpaper_storage;

  void wallpaper_storage_load(void);
  void wallpaper_storage_print(void);

int main(void){

  srand(time(0));

  wallpaper_storage_load();
  if(DEBUG == 1){

    cout << "Wallpapers:\n";
    wallpaper_storage_print();

  }

  int random_wallpaper = (rand() % (wallpaper_storage.size())) + 1;
  --random_wallpaper;

  if(DEBUG == 1)
    cout << "Run:\n" << (wallpaper_loader + " " + path_folder + wallpaper_storage[random_wallpaper]) << '\n';
  else
    system((wallpaper_loader + " " + path_folder + wallpaper_storage[random_wallpaper]).c_str());

  return 0;

}

void wallpaper_storage_print(void){

  for(int i = 0; i < wallpaper_storage.size(); ++i){

    cout << wallpaper_storage[i] << '\n';

  }

}

void wallpaper_storage_load(void){

  system(("ls " + path_folder + " > " + path_temp).c_str());

  FILE *file = fopen(path_temp.c_str(),"r");
  if(file == 0)  return;

  char c;
  string line = "";

  while(1){

    c = getc(file);

    if(c == EOF)  break;
    else
    if(c == '\n'){

      wallpaper_storage.push_back(line);
      line = "";

    }
    else
      line += c;

  }

  fclose(file);
  system(("rm " + path_temp).c_str());

}
