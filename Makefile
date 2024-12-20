CFLAGS = -Wall -Werror -Wpedantic

aswium-git: main.o server.o html.o fanyi.o route.o
	gcc $(CFLAGS) server.o main.o html.o fanyi.o route.o

main.o: ./src/main.c
	gcc $(CFLAGS) -c ./src/main.c 

server.o: ./src/server.c
	gcc $(CFLAGS) -c ./src/server.c

html.o: ./src/html.c
	gcc $(CFLAGS) -c ./src/html.c

fanyi.o: ./src/fanyi.c 
	gcc $(CFLAGS) -c ./src/fanyi.c

route.o: ./src/route.c 
	gcc $(CFLAGS) -c ./src/route.c