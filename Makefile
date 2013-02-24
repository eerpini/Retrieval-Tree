PROGS:=src/strutils.c src/dictionary.c src/linkedlist.c src/trie.c src/cmdutils.c

all:compile
compile:
	$(CC) -g $(PROGS) -o Dictionary -I./include/

clean:
	rm -r Dictionary Dictionary.dSYM
	
