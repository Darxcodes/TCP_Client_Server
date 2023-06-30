#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
int main(void)
{
    	int sockdec;
    	struct sockaddr_in server_addr;
    	char sermsg[500], clmsg[500];
    
    	// Clean buffers:
   	bzero(clmsg,sizeof(clmsg));
   	bzero(sermsg,sizeof(clmsg));
    
    	// Create socket:
    	sockdec = socket(AF_INET, SOCK_STREAM, 0);
  
    	printf("Socket created successfully\n");
    
    	// Set port and IP the same as server-side:
    	server_addr.sin_family = AF_INET;
    	server_addr.sin_port = htons(1500);
    	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    	// Send connection request to server:
    	connect(sockdec, (struct sockaddr*)&server_addr, sizeof(server_addr));
    	printf("Connected with server successfully\n");
    
    	// Get input from the user:
    	printf("Enter message: ");
    	gets(clmsg);
    
    	// Send the message to server:
    	send(sockdec, clmsg, strlen(clmsg), 0);
        
    
   	 // Receive the server's response:
    	recv(sockdec, sermsg, sizeof(sermsg), 0);
       
    	printf("Server's response: %s\n",sermsg);
    
    	// Close the socket:
    	close(sockdec);
    
    	return 0;
}
