
#include "helpers.h"
#define MAX 45
bool check_file(char *file_name) {
    return access(file_name, F_OK) == -1 ? false : true;
}



void print_block(char *block_name) {
    printf("\n");
    printf("+===========+\n");
    printf("|   %s    |\n", block_name);
    printf("+===========+\n");
    printf("\n");
}

void throw_error(char *error_message) {
    print_block("ERR!");
    printf("%s\n\n", error_message);
    exit(1);
}

void help() {
    print_block("HELP");
    printf("<0> HELP        = Usage: ./Dictionary [-h/--help]\n");
    printf("<1> MEANINGS    = Usage: ./Dictionary\n");
    printf("<2> GUESS       = Usage: ./Dictionary -g [--TRIE] <word>\n");
    printf("<3> SPELL-CHECK = Usage: ./Dictionary -s [--HASH/--TRIE] [<word>/<file>]\n");
    printf("<4> COMPARE     = Usage: ./Dictionary -c [<word>/<file>]\n");
    printf("\n");
}

bool is_number(const char word[]) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (!isdigit(word[i])) {
            return false;
        }
    }
    return true;
}

void clean(char word[]) {
    int i, j;

    for (i = 0; word[i] != '\0'; i++) {
        word[i] = (char) tolower(word[i]);
    }

    char word_copy[MAX + 1];
    for (i = 0, j = 0; word[i] != '\0'; i++) {
        if (isalnum(word[i])) {
            word_copy[j++] = word[i];
        }
    }
    if (j == 0) {
        word_copy[j++] = 'a';
    }
    word_copy[j] = '\0';

    strcpy(word, word_copy);

    int length;
    for (length = 0; word[length] != '\0'; length++);

    if (is_number(word)) {
        word[0] = word[length - 1];
        word[1] = '\0';
        return;
    }

    if (length >= 3) {
        char th_word_copy[MAX - 1];
        for (i = 0; i < length - 2; i++) {
            th_word_copy[i] = word[i];
        }
        th_word_copy[i] = '\0';
        if (is_number(th_word_copy)) {
            word[0] = word[length - 3];
            word[1] = word[length - 2];
            word[2] = word[length - 1];
            word[3] = '\0';
            return;
        }
    }
}

void meaning(char *argv, char *word) {
    unsigned long length = 8 + strlen(argv) - 10 + 14 + strlen(word) + 1;
    char command[length];
    memset(command, '\0', length * sizeof(char));

    strcat(command, "python ");
    argv[strlen(argv) - 10] = '\0';
    strcat(command, argv);
    strcat(command, "../meaning.py ");
    strcat(command, word);

    printf("\n");
    system(command);
}

