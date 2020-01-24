// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 
#define MAXLINE 1024 

// Driver code 
int main() { 
    //read file code starts
        int c[2];
        FILE *fptr;
        if ((fptr = fopen("text", "r")) == NULL) {
            printf("Error! opening file");
            // Program exits if file pointer returns NULL.
            exit(1);
        }
        // reads text until newline is encountered
        fscanf(fptr, "%d", c);

        printf("%d\n", *c);
        fclose(fptr);
    
    // read file code ends

	int sockfd; 
	char buffer[MAXLINE]; 
	char *hello = "Hello from server"; 
	struct sockaddr_in servaddr, cliaddr; 
	
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	
    pid_t pids[*c];
	int i;
    for ( i= 0; i < *c; i++)
    {

	  if ((pids[i] = fork()) < 0) {
	    perror("fork");
	    abort();
	  } else if (pids[i] == 0) 
	  {
	  	//printf(" child process with id  %d\n", getpid());

	    exit(0);
	  }
    	//printf("total number of processes: %d\n", i);
    }
    for (int j=0; j< *c; j++)
    {
    	printf("pids %d\n", pids[j]);
	}

	int len, n; 
	len = sizeof(cliaddr); //len is value/resuslt 

	n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
				MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
				&len); 
	buffer[n] = '\0'; 
	printf("Client : %s\n", buffer); 
	sendto(sockfd, (const char *)hello, strlen(hello), 
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
			len); 
	printf("Hello message sent.\n"); 
	
	return 0; 
} 
