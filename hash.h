
#define MAX 45
#include "helpers.h"

#define H 1000

typedef struct hash_node {
    char word[MAX + 1];
    struct hash_node *next;
} hash_node;

hash_node *HASH[H];

void hash_init();
hash_node *hash_new_node();

unsigned int hash_index(char *);

bool hash_load(char *);
bool hash_check(char *);
void hash_unload();

void hash_spell_check(char *);
