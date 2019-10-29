// Server side C/C++ program to dseemonstrate Socket programming 
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
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";


    int i;
    char buf[BUF_SIZE];
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    int status =0;
    if(pid ==-1)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    if(pid == 0)//child process
    {

        //99 is a super user(root) 
        if(setuid(99)==-1){ //setuid returns -1 when failure
        perror("failed to set id   ");
        printf("The user ID is %d not 99 \n", getuid());

        char* execbuff[2];
        char fdbuff[30];
        sprintf(fdbuff, "%d", new_socket);
        execbuff[0] = "./server2";
        execbuff[1] = fdbuff;
        execbuff[2] = NULL;
        execvp(execbuff[0], execbuff);

        exit(EXIT_FAILURE);
        }
        else{

        printf("The user ID is %d\n", getuid());
        printf("*** Child process is done ***\n");
        }

    }
    else{//Parent Process
        while ((pid = wait(&status)) > 0);
        printf("*** Parent process is done ***\n");
    }


    return 0;
}
