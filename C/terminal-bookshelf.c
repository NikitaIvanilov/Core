/*

  Terminal Bookshelf

  How it works:

    1. Get list of books, from path.
    2. Print this list.
    3. You choose the needed book.
    4. Program calls the reader and gives it book.

  Edit next strings:

    Path to place, when stored you books:

      char *path_books = "/home/username/Books";

    Write reader name:

      char *pdf_reader  = "pdf_reader";
      char *djvu_reader = "djvu_reader";

  If you add new formats:

    1. Add reader and extension strings in "Reader & Extension".
    2. Add condition statements in function "void book_open(char *name)".

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Path */
char *path_books = "/home/username/Books";
char *path_temp  = "/tmp/booklist.tmp";

/* Reader & Extension */
char *pdf_reader    = "pdf_reader";
char *pdf_extension = "pdf";

char *djvu_reader    = "djvu_reader";
char *djvu_extension = "djvu";

/* Tool */
void booklist_show(void);
void booklist_make(void);
int  booklist_count(void);
void booklist_remove(void);

void book_take(int needed_book);
void book_open(char *name);

int main(void){

  booklist_make();
  booklist_show();

  int number;
  scanf("%d", &number);

  if(number >= 1 && number <= booklist_count())
    book_take(number);

  booklist_remove();
  return 0;

}

void booklist_remove(void){

  char command[(strlen("rm ") + strlen(path_temp))];

  strcpy(command, "rm ");
  strcat(command, path_temp);

  system(command);

}

int booklist_count(void){

  FILE *booklist = fopen(path_temp,"r");
  if(booklist == 0)  return -1;

  int  out = 0;
  char c;

  while(1){

    c = getc(booklist);

    if(c == EOF)  break;
    else
    if(c == '\n')  ++out;

  }

  fclose(booklist);
  return out;

}

void booklist_show(void){

  FILE *booklist = fopen(path_temp,"r");
  if(booklist == 0)  return;

  char c, temp;
  int  i = 1;

  printf("%d <=> ", i++);

  while(1){

    c = getc(booklist);

    if(c == EOF)  break;
    if(temp == '\n')  printf("%d <=> ", i++);
    putchar(c);

    temp = c;

  }

  fclose(booklist);

}

void book_open(char *name){

  char *reader;

  if(strstr(name, pdf_extension) != 0)  reader = pdf_reader;
  else
  if(strstr(name, djvu_extension) != 0)  reader = djvu_reader;

  char command[(strlen(reader) + strlen(" '") + strlen(path_books) + strlen("/") + strlen(name))];

  strcpy(command, reader);
  strcat(command, " '");
  strcat(command, path_books);
  strcat(command, "/");
  strcat(command, name);

  int i;

  for(i = 0; i < sizeof(command); ++i)  if(command[i] == '\n')  command[i] = '\'';

  system(command);

}

void book_take(int needed_book){

  FILE *booklist = fopen(path_temp,"r");
  if(booklist == 0)  return;

  int  current_book;
  char string[512];

  for(current_book = 0; current_book < needed_book; ++current_book){

    memset(&string, '\0', sizeof(string));
    fgets(string, sizeof(string), booklist);

  }

  fclose(booklist);
  book_open(string);

}

void booklist_make(void){

  char command[(strlen("ls ") + strlen(path_books) + strlen(" > ") + strlen(path_temp))];

  strcpy(command, "ls ");
  strcat(command, path_books);
  strcat(command, " > ");
  strcat(command, path_temp);

  system(command);

}
