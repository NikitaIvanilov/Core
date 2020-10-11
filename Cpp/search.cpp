/*

  How it works:

    1. Get text file and arguments.
    2. Search arguments in every line
    3. Print lines, where arguments were found.

    Note: Print lines descending found arguments.

*/

#include <iostream>
#include <list>
#include <iterator>
#include <string>

using namespace std;

list<string> search_arguments;  //  Arguments, which be found in the line

list<string> v_line;  //  Verified_line
list<int>    v_value;  //  Verified_value

int  check_v_data(void);        //  Check verified data problems, 0 - good.
int  check_argc(int argc);       //  Check argc problems, 0 - good.
int  get_max_value(void);         //  Get max value of all lines
int  search_run(char *filename);   //  Opens text file and launch input lines to verification, 0 - good
void add_search_arguments(void);    //  Input search arguments
void print_search_arguments(void);   //  Output search arguments
void print_verified_data(int value);  //  Print verified lines to value of meets, like a key - value
void print_verified_data_full(void);   //  Print full verified lines
void verify_search_arguments(string);   //  Verify search arguments in the string and count them meets

int main(int argc,char *argv[]){

  if(check_argc(argc) == 1)  return 0;

  int current_argc = 1;
  add_search_arguments();

  while(1){

    search_run(argv[current_argc]);

    if(check_v_data() == 1)  return 0;

    print_verified_data_full();

    if(current_argc == (argc - 1))  break;
    else{

      ++current_argc;
      v_value.clear();
      v_line.clear();

    }

  }

  return 0;

}

void print_verified_data_full(void){

  //  Output lines of all verification levels
  for(int max = get_max_value(); max > 0; --max)  print_verified_data(max);

}

int check_argc(int argc){

  if(argc == 1){  //  Must be arguments

    cout << "Error: No arguments!\n";
    return 1;

  }

  return 0;

}

int check_v_data(void){

  //  v_value and v_line must be equal, else error
  if(v_value.size() != v_line.size()){

    cout << "Error: v_value and v_line are not equal!\n";
    return 1;

  }

  return 0;

}

int get_max_value(void){

  //  Declare iterator for lists, and take begin points
  list<int>::iterator it_value = v_value.begin();
  list<string>::iterator it_line = v_line.begin();

  int max_value = 0;

  //  Count max level of verification ...
  while(it_value != v_value.end() && it_line != v_line.end()){

    if(*it_value > max_value)  max_value = *it_value;

    ++it_value;
    ++it_line;

  }

  // ... and return it
  return max_value;

}

void print_verified_data(int needed_value){

  //  Declare iterator for lists, and take begin points
  list<int>::iterator it_value = v_value.begin();
  list<string>::iterator it_line = v_line.begin();

  //  Output line, who corresponds to needed level of verification
  while(it_value != v_value.end() && it_line != v_line.end()){

    if(*it_value == needed_value)  cout << *it_line << '\n';

    ++it_value;
    ++it_line;

  }

}

void verify_search_arguments(string line){

  int line_verify = 0;  //  Number of suitable arguments

  //  Declare iterator for list<string> and take begin point
  list<string>::iterator it = search_arguments.begin();

  while(it != search_arguments.end()){

    //  If argument is in line, line_verify level up ...
    if(0 <= line.find(*it) && line.find(*it) <= (line.size() - 1))  ++line_verify;

    ++it;  //  ... and switch to next argument

  }

  //  If line is suitable, save the line and line_verify
  if(line_verify > 0){

    v_line.push_back(line);
    v_value.push_back(line_verify);

  }

}

int search_run(char *filename){

  //  Create pointer and open file
  FILE *text = fopen(filename,"r");

  //  If file can not open, return 1
  if(text == 0)  return 1;

  string line;
  char c;

  while(1){

    c = getc(text);  //  Get char from text stream

    if(c == EOF)  break;  //  EOF break cycle
    else
    if(c == '\n'){  //  Send for verification

      verify_search_arguments(line);
      line = "";

    }
    else  //  Keep doing the line
      line += c;

  }

  //  Close file and return result
  fclose(text);
  return 0;

}

void print_search_arguments(void){

  //  Declare iterator for list<string> and take begin point
  list<string>::iterator it = search_arguments.begin();

  //  Output
  while(it != search_arguments.end()){

    cout << *it << '\n';
    ++it;

  }

}

void add_search_arguments(void){

  string line;
  char c;

  while(1){

    c = getchar();

    if(c == '\n'){

      search_arguments.push_back(line);
      break;

    }
    else
    if(c == ' '){

      search_arguments.push_back(line);
      line = "";

    }
    else
      line += c;

  }

}
