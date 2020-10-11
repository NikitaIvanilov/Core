/*

NAME

  aur_install - download AUR package and install it.

SYNOPSIS

  aur_install [package1] [package2] ... [packageN]

*/

#include <iostream>
#include <string>

using namespace std;

const int    empty     = 3081;
const string address   = "https://aur.archlinux.org/cgit/aur.git/snapshot/";
const string transfer  = "curl -O";
const string extension = ".tar.gz";

string name    = "";
string command = "";

void get_package(void);      //  Download package archive from address
void install_package(void);  //  Extract archive and launch PKGBUILD
int  package_size(void);     //  Get package size

int main(int argc, char *argv[]){

  for(int i = 1; i < argc; ++i){

    //  Select name and download
    name = argv[i];
    get_package();

    //  Check size and install package
    if(package_size() == empty)  cout << "\nERROR: invalid package name!\n\n";
    else
      install_package();

    //  Remove package archive
    system(("rm " + name + extension).c_str());

    //  Notification
    cout << " <===> Done: " << name << '\n';

  }

  if((argc - 1) == 0)  cout << "aur_install: no input arguments!\n";

  return 0;

}

void install_package(void){

  //  Notification
  cout << " <===> Install: " << name << '\n';

  //  Extract package
  system(("tar -xf " + name + extension).c_str());

  //  Go to package folder and launch PKGBUILD
  system(("cd " + name + " && makepkg -si PKGBUILD").c_str());

  //  Remove package folder
  system(("rm -r " + name).c_str());

}

int package_size(void){

  //  Create name for file
  string name_size = name + ".size";

  //  Put size to file
  command = "du -b " + name + extension + " > " + name_size;
  system(command.c_str());

  //  Open file
  FILE *package = fopen(name_size.c_str(), "r");
  if(package == 0){

    cout << "\nERROR: Can not get package size!\n\n";
    exit(0);

  }

  //  Get size from file
  int size;
  fscanf(package,"%d\t%s",&size);

  //  Close file and remove it
  fclose(package);
  system(("rm " + name_size).c_str());

  //  Return package size
  return size;

}

void get_package(void){

  //  Notification
  cout << " <===> Download: " << name << '\n';

  //  Download package
  command = transfer + " " + address + name + extension;
  system(command.c_str());

}
