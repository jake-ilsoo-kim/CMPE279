// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
int main(int argc, char const *argv[]) 
{
        printf("server2 start\n");	
	int new_socket = atoi(argv[1]);
        int file = atoi(argv[2]);
	int status;
        uid_t id;
        struct passwd *pwd = getpwnam("nobody");
        uid_t UserId = pwd->pw_uid;

	/* Assignment3 - Chroot() */

	// check path before chroot()
   	char t_cwd[PATH_MAX];
    	getcwd(t_cwd, sizeof(t_cwd));
    	printf("Current dir before chroot(): %s\n", t_cwd);
   	// do chroot()
    	chdir("/tmp/chroot/");
    	if (chroot("/tmp/chroot/") != 0) {
        	perror("chroot /tmp/chroot/");
        	return 1;
    	}

    	// check path path after chroot()
    	char a_cwd[PATH_MAX];
    	getcwd(a_cwd, sizeof(a_cwd));
    	printf("Current dir after chroot(): %s\n", a_cwd);
    

	/* Assignment3 - for using Chroot(), setuid() moved from server.c to server2.c */
    	if(setuid(UserId)==-1){ //setuid returns -1 when failure
        	perror("failed to set id   ");
        	exit(EXIT_FAILURE);
        }
        else{
        	printf("The user ID is %d\n", getuid());
        }


        char buffer[1024] = {0}; 
        char buffer2[1024] = {0};
        char *hello = "Hello from server"; 

        int valread = read( new_socket , buffer, 1024);
        printf("%s\n", buffer);
	int valread2 = read( file, buffer2, 1024);
        printf("%s\n", buffer2);

        /* Assignment3 -  change hello to buffer2 */
        send(new_socket , buffer2, strlen(buffer2) , 0 );
        //printf("Hello message sent\n");
      
    return 0; 
} 

