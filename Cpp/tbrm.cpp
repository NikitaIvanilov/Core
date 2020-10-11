/*

  Terminal book reader manager

  Rules of work this program:

    1. TBRM print books from requirement directory.
    2. Your select need book.
    3. Open book if it possibly.

  Manual:

    Create Books/ in your directory
    and put your books in this directory.

    Install needs packages:

      zathura
      zathura-djvu
      zathura-pdf-poppler
      fbreader

    Compile this code:

      g++ -o tbrm tbrm.cpp

    And launch ./tbrm

  Notes:

    If you use another book readers,
    you can rewrite variable reader in function select_book(void);
    on your reader name.

    If you need change book-directory,
    you can rewrite variable string path;

    This program work only under Linux-based systems,
    but you can port this code on another systems.

*/

#include <iostream>
#include <vector>

using namespace std;

void create_bookshelf(void);
void print_bookshelf(void);
int  select_book(void);
void system_input(void);

FILE *booklist;

int  max_books = 0;
int  i = 0;

string path = "Books/";
string command_line = "ls " + path + " > .booklist";
string reader;

vector<string> bookshelf;

const char *start_command = command_line.c_str();

int main(void){

create_bookshelf();

for(;;){

  print_bookshelf();

  if(select_book() == 1)  break;
  else
    system_input();

}

return 0;
}

void create_bookshelf(void){

char current_char = 0;
int current_shelf = 0;

system(start_command);

booklist = fopen(".booklist","r");

for(;;){  // count books

  current_char = getc(booklist);

  if(current_char == EOF)  break;
  else
  if(current_char == '\n')  ++max_books;

}

fclose(booklist);

bookshelf.resize(max_books);

booklist = fopen(".booklist","r");

for(;;){  // put books on bookshelf

  current_char = getc(booklist);

  if(current_char == EOF)  break;
  else
  if(current_char == '\n')  ++current_shelf;
  else
    bookshelf[current_shelf] += current_char;

}

fclose(booklist);

system("rm .booklist");

}

void print_bookshelf(void){

system("clear");

putchar('\n');

for(i = 0;i < max_books;++i)

  cout << ' ' << i+1 << ' ' << bookshelf[i] << '\n';

putchar('\n');
putchar(' ');

}

int select_book(void){

cin >> i;  --i;

// bad number error
if(i > max_books-1 || i < 0)  return 1;

// read extension and select needed reader
if(bookshelf[i].find("pdf") - bookshelf[i].find(".pdf"))

  reader = "zathura ";

else
if(bookshelf[i].find("djvu") - bookshelf[i].find(".djvu"))

  reader = "zathura ";

else
if(bookshelf[i].find("fb2") - bookshelf[i].find(".fb2"))

  reader = "FBReader ";

else  return 1;  // extension error

return 0;
}

void system_input(void){

  command_line = reader + "'" + path + bookshelf[i] + "'";
  system(command_line.c_str());

}
