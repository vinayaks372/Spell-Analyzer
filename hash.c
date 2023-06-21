

#include "hash.h"

void hash_init()
{
    for (int i = 0; i < H; i++)
    {
        HASH[i] = NULL;
    }
}

unsigned long hash_count = 0;
unsigned long hash_memory = 0;

hash_node *hash_new_node()
{
    hash_node *new_node = malloc(sizeof(hash_node));
    if (!new_node)
    {
        hash_unload();
        return NULL;
    }
    hash_memory += sizeof(hash_node);

    new_node->next = NULL;
    return new_node;
}


unsigned int hash_index(char *word)
{
    unsigned int hash = 0;
    for (int i = 0, n = (int)strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ word[i];
        // printf("Hash:%d word:%c\n",hash,word[i]);
    }
    return hash % H;
}

bool hash_load(char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        return false;
    }

    char word[MAX + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        hash_node *node = hash_new_node();
        if (!node)
        {
            hash_unload();
            return false;
        }
        strcpy(node->word, word);
        unsigned int hi = hash_index(word);
        if (!HASH[hi])
        {
            HASH[hi] = node;
        }
        else
        {
            node->next = HASH[hi];
            HASH[hi] = node;
        }
        hash_count += 1;
    }

    fclose(file);
    return true;
}

bool hash_check(char *word)
{
    unsigned int index = hash_index(word);
    hash_node *current_node = HASH[index];
    while (current_node)
    {
        if (!strcmp(current_node->word, word))
        {
            return true;
        }
        current_node = current_node->next;
    }
    return false;
}

void hash_unload()
{
    for (int i = 0; i < H; i++)
    {
        hash_node *current_node = HASH[i];
        if (!current_node)
        {
            continue;
        }
        while (current_node->next)
        {
            hash_node *tmp = current_node;
            current_node = current_node->next;
            free(tmp);
        }
        free(current_node);
    }
}

void hash_spell_check(char *input)
{
    unsigned int file_count = 0, misspelled_count = 0;
    clock_t start= clock();
    hash_init();
    hash_load("dict.txt");
    

        FILE *input_file = fopen(input, "r");
        FILE *output_file = fopen("../misspelled.txt", "w");
        if (!input_file || !output_file)
        {
            throw_error("File could not be opened!\n");
        }

        char word[MAX + 1];
        int index = 0, c;
        for (c = fgetc(input_file); c != EOF; c = fgetc(input_file))
        {
            if (isalnum(c) || c == '\'' || c == '.' || c == '\\' || c == '-')
            {
                word[index++] = (char)tolower(c);
            }
            else if ((c == ' ' && index) || (c == '\n' && index))
            {
                word[index] = '\0';
                file_count += 1;
                index = 0;

                clean(word);
                if (!hash_check(word))
                {
                    fprintf(output_file, "%s\n", word);
                    // printf("%s ",word);
                    misspelled_count += 1;
                }
            }
            if (index > MAX)
            {
                for (c = fgetc(input_file); c != EOF; c = fgetc(input_file))
                    ;
            }
        }

        fclose(input_file);
        fclose(output_file);
    
   
    hash_unload();
   
    clock_t end= clock();
    printf("Time :%ld\nWords in dictionary:%d \nNumber of Misspelled words: %d \n",end-start, file_count, misspelled_count);
   
}