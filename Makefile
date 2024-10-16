CFLAGS = -Wall -Werror -Wpedantic

all: aswium-git

aswium-git: main.o server.o lexer.o http.o utils.o
	gcc $(CFLAGS) server.o main.o lexer.o http.o utils.o -o aswium-git
	chmod +x aswium-git

main.o: ./src/main.c
	gcc $(CFLAGS) -c ./src/main.c 

server.o: ./src/server.c
	gcc $(CFLAGS) -c ./src/server.c

lexer.o: ./src/lexer.c
	gcc $(CFLAGS) -c ./src/lexer.c

http.o: ./src/http.c
	gcc $(CFLAGS) -c ./src/http.c

utils.o: ./src/utils.c
	gcc $(CFLAGS) -c ./src/utils.c

clean:
	@rm main.o server.o lexer.o http.o utils.o aswium-git
