all: aswium-git

aswium-git: main.o server.o lexer.o
	gcc main.o server.o lexer.o -o aswium-git
	chmod +x aswium-git

main.o: ./src/main.c
	gcc -c ./src/main.c 

server.o: ./src/server.c
	gcc -c ./src/server.c

lexer.o: ./src/lexer.c
	gcc -c ./src/lexer.c
