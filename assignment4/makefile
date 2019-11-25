all : server2 server client

server: server.c
	gcc -o server server.c -lseccomp

server2: server2.c
	gcc -o server2 server2.c

client: client.c
	gcc -o client client.c -lseccomp

clean :
	rm server2 server client
