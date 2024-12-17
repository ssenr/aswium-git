CFLAGS = -Wall -Werror -Wpedantic

aswium-git: main.o server.o html.o
	gcc $(CFLAGS) server.o main.o html.o
	chmod +x aswium-git

main.o: ./src/main.c
	gcc $(CFLAGS) -c ./src/main.c 

server.o: ./src/server.c
	gcc $(CFLAGS) -c ./src/server.c

html.o: ./src/html.c
	gcc $(CFLAGS) -c ./src/html.c

clean:
	@rm main.o server.o lexer.o http.o utils.o aswium-git