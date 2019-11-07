default:
	flex main.l
	bison -d main.y
	gcc -o PL -O2 main.tab.c lex.yy.c linkedlist.c hashtable.c
