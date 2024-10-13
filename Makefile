all: aswium-git

aswium-git: main.o client.o
	gcc main.o client.o -o aswium-git
	chmod +x aswium-git

main.o: ./src/main.c
	gcc -c ./src/main.c 

client.o: ./src/client.c 
	gcc -c ./src/client.c
