PROGS:=src/strutils.c src/dictionary.c src/linkedlist.c src/trie.c src/cmdutils.c src/commonutils.c src/main.c

all:compile
compile:
	$(CC) -g $(PROGS) -o Dictionary -I./include/

debug:
	$(CC) -g $(PROGS) -o Dictionary -I./include/ -DDEBUG

clean:
	rm -f Dictionary Dictionary.dSYM
	
test:
	./Dictionary < test_input
