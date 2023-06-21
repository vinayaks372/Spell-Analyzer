Dictionary:main.o trie.o hash.o helpers.o
	gcc -o Dictionary main.o trie.o hash.o helpers.o
main.o:main.c trie.c hash.c helpers.c
	gcc -c main.c 
trie.o:main.c trie.c hash.c helpers.c
	gcc -c trie.c
hash.o:main.c trie.c hash.c helpers.c
	gcc -c hash.c
helpers.o:main.c trie.c hash.c helpers.c
	gcc -c helpers.c
clean:
	rm -f *.o *~


