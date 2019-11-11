// Server side C/C++ program to dseemonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <sys/wait.h>
#include <pwd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
//#define PORT 8080 
#define BUF_SIZE 100
int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 
    int PORT;
    
    errno=0;
    /* Assignment3 - use argv for PORT and file */
    int file = open(argv[2], O_RDONLY);
    if(argc==0){
       printf("There are no arguments");
       return 1;
    }
    if(file == -1) {
	printf("\n open() failed with error [%s]\n", strerror(errno));
	return 1;
    }
    if(argc == 0) {
        PORT=8080;
    }
    PORT = atoi(argv[1]);

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
        /* Assignment3 - get file name from argv */ 
        char* execbuff[3];
        char fdbuff[30];
	    char fdbuff2[30];	
        sprintf(fdbuff, "%d", new_socket);
	    //printf("%s\n",fdbuff);

	    sprintf(fdbuff2, "%d", file);
    	//printf("%s\n", fdbuff2);
        
        execbuff[0] = "./server2";
        execbuff[1] = fdbuff;
	    execbuff[2] = fdbuff2;
        execbuff[3] = NULL;
        execvp(execbuff[0], execbuff);

        printf("*** Child process is done ***\n");
    }
   else{//Parent Process
       while ((pid = wait(&status)) > 0);
      printf("*** Parent process is done ***\n");
    }
      

    return 0; 
} 

