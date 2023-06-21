
#include "trie.h"
#define MAX 45
void trie_init()
{
    TRIE = trie_new_node();
}

unsigned int trie_count = 0;
unsigned long int trie_memory = 0;

trie_node *trie_new_node()
{
    trie_node *new_node = (trie_node *)malloc(sizeof(trie_node));
    if (!new_node)
    {
        trie_unload(TRIE);
        return NULL;
    }
    trie_memory += sizeof(trie_node);

    new_node->end = false;
    for (int i = 0; i < T; i++)
    {
        new_node->children[i] = NULL;
    }
    return new_node;
}

bool trie_load(char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        return false;
    }

    char word[MAX + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        trie_node *current_node = TRIE, *new_node;
        for (int i = 0, index; word[i] != '\0'; i++)
        {
            index = (int)word[i];
            if (48 <= index && index <= 57)
            {
                index -= 48;
            }
            else if (97 <= index && index <= 122)
            {
                index -= 87;
            }
            else
            {
                continue;
            }

            if (!current_node->children[index])
            {
                new_node = trie_new_node();
                if (!new_node)
                {
                    trie_unload(TRIE);
                    return false;
                }
                current_node->children[index] = new_node;
            }
            current_node = current_node->children[index];
        }
        current_node->end = true;
        trie_count += 1;
    }

    fclose(file);
    return true;
}

bool trie_check(const char *word)
{
    trie_node *current_node = TRIE;
    for (int i = 0, index; word[i] != '\0'; i++)
    {
        index = (int)word[i];
        if (48 <= index && index <= 57)
        {
            index -= 48;
        }
        else if (97 <= index && index <= 122)
        {
            index -= 87;
        }
        else
        {
            return false;
        }

        if (!current_node->children[index])
        {
            return false;
        }
        current_node = current_node->children[index];
    }

    return (current_node && current_node->end);
}

void trie_unload(trie_node *node)
{
    for (int i = 0; i < T; i++)
    {
        if (node->children[i])
        {
            trie_unload(node->children[i]);
        }
    }
    free(node);
}

void trie_traversal(trie_node *head, const char *word)
{
    int length;
    char word_copy[MAX + 1];
    for (length = 0; word[length] != '\0'; length++)
    {
        word_copy[length] = word[length];
    }
    word_copy[length] = '\0';

    if (head->end)
    {
        printf("%s\n", word_copy);
    }

    char c;
    for (int i = 0; i < T; i++)
    {
        if (head->children[i])
        {
            if (i < 10)
            {
                c = (char)(48 + i);
            }
            else
            {
                c = (char)(87 + i);
            }
            word_copy[length] = c;
            word_copy[length + 1] = '\0';

            trie_traversal(head->children[i], word_copy);
            strcpy(word_copy, word);
        }
    }
}

void trie_guess(const char *word)
{
    trie_init();

    // if (!trie_load(DICTIONARY))
    if(!trie_load("large"))
    {
        throw_error("Dictionary could not be loaded!");
    }

    trie_node *prefix_head = TRIE;

    int i, index;
    char word_copy[MAX + 1];
    for (i = 0; word[i] != '\0'; i++)
    {
        index = (int)word[i];
        if (48 <= index && index <= 57)
        {
            index -= 48;
        }
        else if (97 <= index && index <= 122)
        {
            index -= 87;
        }

        if (prefix_head && prefix_head->children[index])
        {
            prefix_head = prefix_head->children[index];
            word_copy[i] = (char)word[i];
        }
        else
        {
            break;
        }
    }
    word_copy[i] = '\0';
    printf("\nVALID PREFIX: %s\n\n", word_copy);

    printf("DID YOU MEAN?\n\n");
    trie_traversal(prefix_head, word_copy);

    printf("\n");
    trie_unload(TRIE);
}

void trie_spell_check(char *input)
{
    unsigned int file_count = 0, misspelled_count = 0;

    clock_t  start= clock();
    trie_init();
    trie_load("dict.txt");
    
        FILE *input_file = fopen(input, "r");
        FILE *output_file = fopen("../misspelled.txt", "w");
        if (!input_file || !output_file)
        {
            throw_error("File could not be opened!");
        }

        int index = 0, c;
        char word[MAX + 1];
        for (c = fgetc(input_file); c != EOF; c = fgetc(input_file))
        {
            if (isalnum(c) || c == '\'' || c == '.' || c == '\\' || c == '-')
            {
                word[index++] = (char)tolower(c);
            }
            else if ((c == ' ' && index) || (c == '\n' && index))
            {
                word[index] = '\0';
                clean(word);
                if (!trie_check(word))
                {
                    fprintf(output_file, "%s\n", word);
                    misspelled_count += 1;
                }
                index = 0;
                file_count += 1;
            }
            if (index > MAX)
            {
                for (c = fgetc(input_file); c != EOF; c = fgetc(input_file));
            }
        }

        fclose(input_file);
        fclose(output_file);

    trie_unload(TRIE);
   
    clock_t  end= clock();
    
    printf("Time %ld \nfile_count:%d \n misspelled_count:%d\n",end-start,file_count, misspelled_count);

}
