
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>



void throw_error(char *error_message) ;
void clean(char word[]);
bool check_file(char *file_name);
void help();
