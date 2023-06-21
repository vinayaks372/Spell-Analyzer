#include <stdio.h>
#include "trie.h"
#include "hash.h"
#include"helpers.h"

int main(int argc, char **argv)
{
    printf("%s", argv[1]);
    if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h"))
    {
        help();
    }
    else if (!strcmp(argv[1], "-s"))
    {
        if (!strcmp(argv[2], "--TRIE"))
        {
            trie_init();
            trie_load("large");
            if (trie_check(argv[3]))
            {
                printf("Valid word \n");
            }
            else
            {
                printf("Invalid word\n");
            }
        }
        else if (!strcmp(argv[2], "--HASH"))
        {
            hash_init();
            hash_load("large");
            if (hash_check(argv[3]))
            {
                printf("Valid word\n");
            }
            else
            {
                printf("Invalid word\n");
            }
        }
        else{
            printf("HELP: ./Dictionary [-h/--help]\n");
        }
    }
    else if(!strcmp(argv[1],"-g")){
        if (!strcmp(argv[2], "--TRIE")){
            trie_guess(argv[3]);
        }
        else{
            printf("HELP: ./Dictionary [-h/--help]\n");
        }
    }

    else if(!strcmp(argv[1],"-c")){
        if(!strcmp(argv[2],"--TRIE")){
            trie_spell_check(argv[3]);
        }
        else if(!strcmp(argv[2],"--HASH")){
            hash_spell_check(argv[3]);
        }
        else{
            printf("HELP: ./Dictionary [-h/--help]\n");
        }
    }
    else
    {
        printf("HELP: ./Dictionary [-h/--help]\n");
    }
    
}