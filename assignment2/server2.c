// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/wait.h>
#define PORT 8080 
#define BUF_SIZE 100
int main(int argc, char const *argv[])
{
    //int server_fd, new_socket, valread; 
    int new_socket = atoi(argv[0]);
    char buffer[1024] = {0};
    char *hello = "Hello from server";

        int valread = read( new_socket , buffer, 1024);
        printf("%s\n",buffer );
        send(new_socket , hello , strlen(hello) , 0 );
        printf("Hello message sent\n");


    return 0;
}
