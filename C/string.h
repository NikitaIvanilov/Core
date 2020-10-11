
/*

  Tools for work with strings and characters in C.

*/

int string_get_size            (char *string);
int string_compare             (char *string, char *target);

int string_find_char           (char *string, char target);
int string_find_char_on_count  (char *string, char target, int count);

int string_find_string         (char *string, char *target);
int string_find_string_on_count(char *string, char *target, int count);

int string_find_string_after   (char *string, char *target, char *after);
int string_find_string_before  (char *string, char *target, char *before);

/* ### */

int string_find_string_before(char *string, char *target, char *before){

  int point_before = string_find_string(string, before),
      point_target = string_find_string(string, target);

  if(point_before == -1)

    return -2; else

  if(point_target == -1 || point_target >= point_before)

    return -1;

  return point_target;

}

int string_find_string_after(char *string, char *target, char *after){

  int iteration    = 0,
      point_after  = string_find_string(string, after),
      point_target = string_find_string_on_count(string, target, iteration);

  if(point_after == -1) return -2;

  while(point_target <= point_after){

    if(point_target == -1) return -1;

    ++iteration,
    point_target = string_find_string_on_count(string, target, iteration);

  }

  return point_target;

}

int string_find_string_on_count(char *string, char *target, int count){

  int target_index = 0,
      target_size  = string_get_size(target),

      string_index = 0,
      string_size  = string_get_size(string);

  while(count >= 0){

    while(string_index < string_size && target_index < target_size){

      if(string[string_index] == target[target_index]) ++target_index;
      else
      if(string[string_index] != target[target_index] && target_index > 0){ target_index = 0; continue; }

      ++string_index;

    }

    if(target_index == target_size)

      if(count > 0){

        --count; target_index = 0;

      }
      else return string_index - target_size;

    else return -1;

  }

}

int string_find_string(char *string, char *target){

  return string_find_string_on_count(string, target, 0);

}

int string_find_char_on_count(char *string, char target, int count){

  int out;

  for(out = 0; string[out] != '\0'; ++out)

    if(string[out] == target)

      if(count > 0) --count; else return out;

  return -1;

}

int string_find_char(char *string, char target){

  return string_find_char_on_count(string, target, 0);

}

int string_compare(char *string, char *target){

  int string_size = string_get_size(string),
      target_size = string_get_size(string);

  if(string_size - target_size != 0) return -2;

  for(int i = 0; i < string_size; ++i)

    if(string[i] != target[i]) return -1;

  return 1;

}

int string_get_size(char *string){

  int out;

  for(out = 0; string[out] != '\0'; ++out){}

  return out;

}