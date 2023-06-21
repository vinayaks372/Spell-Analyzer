#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>


#define Size 26



typedef struct trie{
    int *arr[Size];
    bool end;
}trie;
trie head;

trie* createnode(){
    trie* nn=(trie*)malloc(sizeof(trie));
    nn->end=false;
    for(int i=0;i<Size;i++){
        nn->arr[i]=NULL;
    }
    return nn;
}
void insert(){
    
}