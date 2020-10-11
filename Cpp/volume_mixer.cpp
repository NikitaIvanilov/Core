/*

  volume_mixer.cpp

  1. Takes two arguments: '+' and '-'.

     '+' give STEP to volume.
     '-' take STEP from volume.

  2. Create config file and write in path.

     string path = "/path/to/volume_mixer.cfg";

  3. Install ponymix:

     For Arch Linux: sudo pacman -S ponymix
     Other: https://github.com/falconindy/ponymix

     Ponymix needed for work.

*/

#include <iostream>
#include <string>

//  Size of step
#define STEP 10

//  Volume range
#define MIN 0
#define MAX 150

using namespace std;

//  Path to volume_mixer.cfg
string path = "/home/username/.config/volume_mixer.cfg";

int  volume;
char argument;
void get_volume(void);
void set_volume(void);
void ponymix_run(void);

int main(int argc,char *argv[]){

  if(argc == 2)  argument = *argv[argc - 1];
  else{

    cout << "Error: Can get only one argument!\n";
    exit(0);

  }

  get_volume();

  switch(argument){

    case '-':  if((volume - STEP) >= MIN)  volume -= STEP;
    break;

    case '+':  if((volume + STEP) <= MAX)  volume += STEP;
    break;

    default:  cout << "Error: Bad argument!\n";  exit(0);
    break;

  }

  set_volume();
  ponymix_run();
  return 0;

}

void ponymix_run(void){

  string ponymix = "ponymix --sink set-volume " + to_string(volume);
  system(ponymix.c_str());

}

void set_volume(void){

  FILE *volume_mixer = fopen(path.c_str(),"w");

  if(volume_mixer == 0){

    cout << "Error: " << path << ": Can not reading!\n";
    exit(0);

  }

  fprintf(volume_mixer,"%d",volume);
  fclose(volume_mixer);

}

void get_volume(void){

  FILE *volume_mixer = fopen(path.c_str(),"r");

  if(volume_mixer == 0){

    cout << "Error: " << path << ": Can not reading!\n";
    exit(0);

  }

  fscanf(volume_mixer,"%d",&volume);
  fclose(volume_mixer);

}
