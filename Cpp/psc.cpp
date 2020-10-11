/*

  psc - pacman simple commander for pacman users.

    SYNOPSIS

      psc <operation> [package1] [package2] ...

    OPERATIONS

      install      - find and install typed package
      remove       - remove your package
      full-remove  - remove your package with dependencies
      upgrade      - upgrade your system
      all-packages - print you system packsges
      find         - find package in your system
      help         - print operation list

*/

#include <iostream>

using namespace std;

void identify(string);

string command = "sudo pacman ";

int main(int argc,char *argv[]){

if((argc-1) == 0){

  printf("psc: missing file operand\n");
  printf("Look code of psc of try 'psc help' for more information.\n");

  return 0;

}

for(int i = 1;;++i){  // identify each argument as operand or package name

  if(i == argc)  break;

  identify(argv[i]);

}

command[command.size()-1] = 0; // remove last space in command line

const char *out = command.c_str();

system(out);

return 0;
}

void identify(string line){

if(line == "help"){

  printf("Install      - find and install typed package\n");
  printf("remove       - remove your package\n");
  printf("full-remove  - remove your package with dependencies\n");
  printf("upgrade      - upgrade your system\n");
  printf("all-packages - print you system packsges\n");
  printf("find         - find package in your system\n");

  command = "";

}
else{

  if(line == "install")      command += "-S ";  // find and install typed package
  else
  if(line == "remove")       command += "-R ";  // remove your package
  else
  if(line == "full-remove")   command += "-Rs "; // remove your package with dependencies
  else
  if(line == "upgrade")      command += "-Syu ";  // upgrade your system
  else
  if(line == "all-packages") command += "-Q";  // print you system packsges
  else
  if(line == "find")         command += "-Q --search ";  // find package in your system
  else
  command += line + ' ';  //  add you package in the end of you command line

  }
}
