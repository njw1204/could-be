default:
	flex main.l
	bison -dv main.y
	gcc -o PL -O2 main.tab.c lex.yy.c linkedlist.c hashtable.c
